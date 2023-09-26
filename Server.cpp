#include "Server.hpp"

/////////////////////////////////////////////////
//                 CONSTRUCTORS                //
/////////////////////////////////////////////////

Server::Server()
{}

Server::Server(char **argv)
{
    sockaddr_in serverAddr;
    int reuse = 1;

    EntrySocket = socket(AF_INET, SOCK_STREAM, 0);
    if (EntrySocket == -1)
        throw (Xception("Error: entry socket not created"));
    
    setsockopt(EntrySocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[1]));
    if (bind(EntrySocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
        throw (Xception("Error: binding entry socket"));

    password = argv[2];
    
    std::cout << "\n================================\n"
              <<   "|       SERVER ACTIVE          |\n" 
              <<   "================================\n" 
              << std::endl;
}

Server::~Server()
{
    close (EntrySocket);
}



////////////////////////////////////////////////
///             GETTERS                       //
////////////////////////////////////////////////

int     Server::getFdMax()
{
    int Max = EntrySocket;

    for (int i = 0; i < (int)clientList.size(); i++)
        if (clientList[i]->getFd() > Max)
            Max = clientList[i]->getFd();
    return (Max);
}

int     Server::getEntrySocket()
{
    return (EntrySocket);
}



//////////////////////////////////////////////////////
//                  METHODS                         //
//////////////////////////////////////////////////////


void    Server::servEmpty()
{
    int             newClient;
    sockaddr_in     clientAddr;
    socklen_t       clientSize = sizeof(clientAddr);

    listen(EntrySocket, 10);
    newClient = accept(EntrySocket, (struct sockaddr *)&clientAddr, &clientSize);
    if (newClient == -1)
        throw (Xception("Error: accept()"));
    clientList.push_back(new Client);
    clientList[clientList.size() - 1]->setFd(newClient);
    clientList[clientList.size() - 1]->setNb(0);
    send(newClient, "password: ", 10, 0);
}

void    Server::servCheckSockets(fd_set &sockets)
{
    if (FD_ISSET(EntrySocket, &sockets))
        servNewConnection();
    for (unsigned int i = 0; i < clientList.size(); i++)
        if (FD_ISSET(clientList[i]->getFd(), &sockets))
            servTreatClient(clientList[i]);
}

void    Server::servNewConnection()
{
    int             newClient;
    sockaddr_in     clientAddr;
    socklen_t       clientSize = sizeof(clientAddr);

    newClient = accept(EntrySocket, (struct sockaddr *)&clientAddr, &clientSize);
    if (newClient == -1)
        throw (Xception("Error: accept()"));
    clientList.push_back(new Client);
    clientList[clientList.size() - 1]->setFd(newClient);
    clientList[clientList.size() - 1]->setNb(clientList.size() - 1);
    send(newClient, "password: ", 10, 0);
}

void    Server::servTreatClient(Client *client)
{
    if (client->getLoggedIn() == 0)
        servAuthentification(client);
    else if (client->getIdentification() == 0)
        servIdentification(client);
    else
        servReceive(client);
}

void    Server::servAuthentification(Client *client)
{
    String  entry;
    char    buffer[BUFFER_SIZE];
    int     size;

    size = recv(client->getFd(), buffer, BUFFER_SIZE, 0);
    if (size == -1)
        return ;
    buffer[size] = '\0';
    client->buffer += buffer;

    if (client->buffer.find('\n') != NPOS)
    {
        entry = client->buffer.substr(0, client->buffer.find('\n'));
        client->buffer.erase(0, client->buffer.find('\n') + 1);
        if (entry == password)
        {    
            client->setLoggedIn(1);
            send (client->getFd(), "Nickname: ", 11, 1);
        }
        else
        {
            send(client->getFd(), "wrong password\n", 16, 0);
            close (clientList[client->getNb()]->getFd());
            clientList.erase(clientList.begin() + client->getNb());
            delete client; 
        }
    }

}

void    Server::servIdentification(Client *client)
{
    String  entry;
    char    buffer[BUFFER_SIZE];
    int     size;

    size = recv(client->getFd(), buffer, BUFFER_SIZE, 0);
    if (size == -1)
        return ;
    buffer[size] = '\0';
    client->buffer += buffer;

    if (client->buffer.find('\n') != NPOS)
    {
        entry = client->buffer.substr(0, client->buffer.find('\n'));
        client->buffer.erase(0, client->buffer.find('\n') + 1);
        
        if (client->getNickname().size() == 0)
        {    
            client->setNickname(entry);
            send(client->getFd(), "Username: ", 11, 0);
        }
        else
        {
            client->setUsername(entry);
            client->setIdentification(1);
        }
    }
}

void    Server::servReceive(Client *client)
{
    String  entry;
    char    buffer[BUFFER_SIZE];
    int     size;

    size = recv(client->getFd(), buffer, BUFFER_SIZE, 0);
    if (size == -1)
        return ;
    buffer[size] = '\0';
    client->buffer += buffer;

    if (client->buffer.find('\n') != NPOS)
    {
        entry = client->buffer.substr(0, client->buffer.find('\n'));
        client->buffer.erase(0, client->buffer.find('\n') + 1);
        if (entry[0] != '\0')
            std::cout << client->getNickname() << ": " << entry << std::endl;
    }
}