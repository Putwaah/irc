#include "Client.hpp"

//////////////////////////////////////////
//            BUILDERS                  //
//////////////////////////////////////////


Client::Client()
: fd(-1), loggedIn(0), identified(0)
{}

Client::Client(int in_fd)
: fd(in_fd), loggedIn(0), identified(0)
{}

Client::Client(const Client &ref)
{
    if (this != &ref)
        *this = ref;
}

Client::~Client()
{
    //if (fd != -1)
    //    close (fd);
}




///////////////////////////////////////////
//           OPERATORS                   //
///////////////////////////////////////////

Client &Client::operator=(const Client &ref)
{
    this->nb = ref.nb;
    this->fd = ref.fd;
    this->loggedIn = ref.loggedIn;
    this->identified = 0;
    return (*this);
}




///////////////////////////////////////////
//             GETTERS                   //
///////////////////////////////////////////

int     Client::getFd() const
{
    return (fd);
}

int     Client::getLoggedIn() const
{
    return (loggedIn);
}

int     Client::getNb() const
{
    return (nb);
}

int    Client::getIdentification() const
{
    return (identified);
}

String  Client::getNickname() const
{
    return (nickname);
}

String  Client::getUsername() const
{
    return (username);
}

//////////////////////////////////////////
//              SETTERS                 //
//////////////////////////////////////////

void Client::setFd(int val)
{
    fd = val;
}

void    Client::setLoggedIn(int val)
{
    loggedIn = val;
}

void    Client::setNb(int val)
{
    nb = val;
}

void    Client::setIdentification(int val)
{
    identified = val;
}

void    Client::setNickname(String nick)
{
    nickname = nick;
}

void    Client::setUsername(String user)
{
    username = user;
}