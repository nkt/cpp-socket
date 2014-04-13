//  Created by Gusakov Nikita on 13/04/14.
//  Copyright (c) 2014 nkt. All rights reserved.

#ifndef __chat__Server__
#define __chat__Server__

#include <iostream>
#include <list>
#include <thread>
#include "Socket.h"

class Server
{
private:
    Socket *sock;
    int backlog;
    std::list<Socket> listeners;
public:
    Server(const char *host, const int port, const int backlog);
    ~Server();
    void run();
};

#endif
