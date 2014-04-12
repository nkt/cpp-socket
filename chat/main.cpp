//  Created by Gusakov Nikita on 11/04/14.
//  Copyright (c) 2014 nkt. All rights reserved.

#include <iostream>
#include "../src/Socket.h"

int main(int argc, const char * argv[])
{
    std::string request;
    try {
        Socket sock;
        sock.bind("localhost", 5000);
        sock.listen(100000);
        for (;;) {
            try {
                Socket client = sock.accept();
                client >> request;
                client << "HTTP/1.1 200 OK\r\n\r\n";
                client << request;
            } catch(std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

