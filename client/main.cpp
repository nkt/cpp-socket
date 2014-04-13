//  Created by Gusakov Nikita on 11/04/14.
//  Copyright (c) 2014 nkt. All rights reserved.

#include <iostream>
#include "../src/Client.h"

int main(int argc, const char **argv)
{
    Client client("localhost", 1111);
    client.run();
}
