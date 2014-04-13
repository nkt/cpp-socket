//  Created by Gusakov Nikita on 13/04/14.
//  Copyright (c) 2014 nkt. All rights reserved.

#include "Client.h"

Client::Client(const char *host, const int port)
{
    sock = new Socket();
    sock->connect(host, port);
}

Client::~Client()
{
    delete sock;
}
