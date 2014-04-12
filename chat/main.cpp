//  Created by Gusakov Nikita on 11/04/14.
//  Copyright (c) 2014 nkt. All rights reserved.

#include <iostream>
#include "../src/Socket.h"

int main(int argc, const char * argv[])
{
    try {
        Socket sock;
        sock.bind("localhost", 8081);
        sock.listen(100);
        for (;;) {
            try {
                Socket client = sock.accept();
                std::cout << client << std::endl;
                client << "HTTP/1.1 200 OK";
            } catch(std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

