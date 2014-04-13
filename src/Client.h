//  Created by Gusakov Nikita on 13/04/14.
//  Copyright (c) 2014 nkt. All rights reserved.

#ifndef __chat__Client__
#define __chat__Client__

#include <iostream>
#include "Socket.h"

class Client
{
private:
    Socket *sock;
public:
    Client(const char *host, const int port);
    ~Client();
};

#endif
