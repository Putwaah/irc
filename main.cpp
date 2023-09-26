#include "Server.hpp"

int main(int argc, char **argv)
{
    (void)argc;
    try
    {
        Server          server(argv);
        fd_set          sockets;

        while (1)
        {
            if (server.clientList.size() == 0)
                server.servEmpty();
            FD_ZERO(&sockets);
            FD_SET(server.getEntrySocket(), &sockets);
            for (int i = 0; i < (int)server.clientList.size(); i++)
                FD_SET(server.clientList[i]->getFd(), &sockets);
            
            if (select(server.getFdMax() + 1, &sockets, NULL, NULL, NULL) == -1)
            {    
                perror("perror: ");
                throw (Xception("\nError: select() problemo"));
            }
            server.servCheckSockets(sockets);
        }
    }

    catch (Xception &e)
    {
        std::cout << e.what() << std::endl;
    }
    return (69);
}