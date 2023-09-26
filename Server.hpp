#pragma once

#include <iostream>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include <fcntl.h>
#include <cstdlib>
#include <cstdio> 

#include "libX.hpp"
#include "Client.hpp"

#define vector          std::vector
#define BUFFER_SIZE     100

class Client;

class Server
{
        public:
                Server();
                Server(char **argv);
                ~Server();

                void    servEmpty();
                void    servCheckSockets(fd_set &sockets);
                void    servNewConnection();
                void    servTreatClient(Client *client);
                void    servAuthentification(Client *client);
                void    servIdentification(Client *client);
                void    servReceive(Client *client);

                int     getFdMax();
                int     getEntrySocket();
                
                vector<Client *>  clientList;
                //vector<Channel *> channelList; 

        private:
                int             EntrySocket;
                String          password;
};