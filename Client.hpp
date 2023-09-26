#pragma once

#include "Server.hpp"

class Client
{
        public:
                Client();
                Client(int in_fd);
                Client(const Client &ref);
                ~Client();

                Client &operator=(const Client &ref);

                int     getFd() const;
                int     getNb() const;
                int     getLoggedIn() const;
                int     getIdentification() const;
                String  getNickname() const;
                String  getUsername() const;

                void    setFd(int val);
                void    setNb(int val);
                void    setLoggedIn(int val);
                void    setIdentification(int val);
                void    setNickname(String nick);
                void    setUsername(String user);

                String  buffer;

        private:
                int     nb;
                int     fd;
                int     loggedIn;
                int     identified;
                String  nickname;
                String  username;
};