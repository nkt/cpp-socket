//  Created by Gusakov Nikita on 13/04/14.
//  Copyright (c) 2014 nkt. All rights reserved.

#include "Server.h"

Server::Server(const char *host, const int port, const int _backlog)
{
    backlog = _backlog;
    sock = new Socket();
    sock->bind(host, port);
    sock->listen(backlog);
}

Server::~Server()
{
    delete sock;
}