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
private:
    static inline sockaddr *getAddressByHostname(const char *host, const int port);
    Socket(const int _handler, const sockaddr &address);
protected:
    int handler;
public:
    int backlog;
    Socket(const int domain = AF_INET, const int type = SOCK_STREAM, const int protocol = IPPROTO_TCP);
    ~Socket();
    void bind(const char *host, const int port);
    void connect(const char *host, const int port);
    void listen(const int backlog);
    long send(const std::string message, const int flags = NULL);
    std::string read(const int flags = NULL);
    Socket accept();

    // operators
    friend std::ostream& operator << (std::ostream& out, Socket& socket);
    friend std::istream& operator >> (std::istream& out, Socket& socket);
};

#endif
