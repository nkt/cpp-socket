//  Created by Gusakov Nikita on 13/04/14.
//  Copyright (c) 2014 nkt. All rights reserved.

#include "Server.h"

Server::Server(const char *host, const int port, const int _backlog) : backlog(_backlog)
{
    sock = new Socket();
    sock->bind(host, port);
    sock->listen(backlog);
}

Server::~Server()
{
    delete sock;
}

void Server::run()
{
    std::thread accepterThread([this](){
        for (;;) {
            listeners.push_back(sock->accept());
        }
    });
    
    std::thread listenerThread([this](){
        std::string message;
        for (;;) {
            if (listeners.empty()) {
                usleep(100);
                continue;
            }
            for (Socket client : listeners) {
                client >> message;
                if (message.size() > 0) {
                    for (Socket listener : listeners) {
                        listener << message;
                    }
                }
            }
        }
    });
    
    accepterThread.join();
    listenerThread.join();
}
