//  Created by Gusakov Nikita on 11/04/14.
//  Copyright (c) 2014 nkt. All rights reserved.

#ifndef __chat__Socket__
#define __chat__Socket__

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>

class Socket
{    
protected:
    int handler;
    
    Socket(const int _handler, const sockaddr &address);
    static inline sockaddr *getAddressByHostname(const char *host, const int port);
public:
    Socket(const int domain = AF_INET, const int type = SOCK_STREAM, const int protocol = IPPROTO_TCP);
    ~Socket();
    void bind(const char *host, const int port);
    void connect(const char *host, const int port);
    void listen(const int backlog);
    long send(const std::string message, const int flags = 0);
    std::string read(const int flags = 0);
    Socket accept();

    // operators
    Socket &operator =(const Socket &sock);
    friend std::ostream &operator <<(std::ostream &output, Socket &socket);
    friend std::istream &operator >>(std::istream &input, Socket &socket);
    template <class T>
    friend Socket &operator <<(Socket &sock, T &message);
    friend Socket &operator >> (Socket &sock, std::string &str);
};

template <class T>
Socket &operator <<(Socket &sock, T &message)
{
    sock.send(std::string(message));
    return sock;
}

#endif
