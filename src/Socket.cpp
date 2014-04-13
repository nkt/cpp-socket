//  Created by Gusakov Nikita on 11/04/14.
//  Copyright (c) 2014 nkt. All rights reserved.

#include "Socket.h"

Socket::Socket(const int domain, const int type, const int protocol)
{
    handler = socket(domain, type, protocol);
    if (handler == -1) {
        throw std::runtime_error(strerror(errno));
    }
}
Socket::Socket(const int _handler, const sockaddr &address)
{
    handler = _handler;
}

Socket::~Socket()
{
    if (handler != -1) {
        shutdown(handler, SHUT_RDWR);
        close(handler);
    }
}

void Socket::bind(const char *host, const int port)
{
    if (::bind(handler, Socket::getAddressByHostname(host, port), sizeof(sockaddr)) == -1) {
        throw std::runtime_error(strerror(errno));
    }
}

void Socket::connect(const char *host, const int port)
{
    if (::connect(handler, Socket::getAddressByHostname(host, port), sizeof(sockaddr)) == -1) {
        throw std::runtime_error(strerror(errno));
    }
}

void Socket::listen(const int backlog)
{
    if (::listen(handler, backlog) == -1) {
        throw std::runtime_error(strerror(errno));
    }
}

Socket Socket::accept()
{
    sockaddr address;
    socklen_t length = sizeof(address);
    int subHandler = ::accept(handler, &address, &length);

    if (subHandler < 0) {
        throw std::runtime_error(strerror(errno));
    }

    return Socket(subHandler, address);
}

long Socket::send(const std::string message, int flags)
{
    long length = ::send(handler, message.c_str(), message.size(), flags);
    if (length == -1) {
        throw std::runtime_error(strerror(errno));
    }
    return length;
}

std::string Socket::read(const int flags)
{
    char buff[8192];
    if (recv(handler, buff, sizeof(buff), flags) == 0) {
        throw std::runtime_error("Connection aborted");
    }
    return std::string(buff);
}

std::ostream &operator <<(std::ostream &output, Socket &socket)
{
    return output << socket.read();
}

std::istream &operator >>(std::istream &input, Socket &socket)
{
    std::string message;
    std::getline(input, message);
    socket.send(message);
    return input;
}

Socket &operator <<(Socket &socket, std::string &message)
{
    socket.send(message);
    return socket;
}

Socket &operator >> (Socket &sock, std::string &str)
{
    str = sock.read();
    return sock;
}

sockaddr *Socket::getAddressByHostname(const char *host, const int port)
{
    sockaddr_in *address = new sockaddr_in;
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    
    hostent *phe = gethostbyname(host);
    memcpy(&address->sin_addr, phe->h_addr, phe->h_length);
    
    return reinterpret_cast<sockaddr *>(address);
}
