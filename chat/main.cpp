//  Created by Gusakov Nikita on 11/04/14.
//  Copyright (c) 2014 nkt. All rights reserved.

#include <iostream>
#include "../src/Server.h"

int main(int argc, const char **argv)
{
    Server serv("localhost", 1111, 10000);
    serv.run();
}
