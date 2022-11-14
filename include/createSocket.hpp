/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.42.fr>                +#+  +:+       +#+        */
/*                                              

#ifndef CREATESOCKET_HPP
#define CREATESOCKET_HPP

#include "common.h"
class createSocket
{
    public:
        int                 sockfd;
        int                 addrlen;
		int					port;
		std::string			ip;
        struct sockaddr_in  address;
    public:
        createSocket();
        createSocket(int sockfd, std::string ip, int port);
        createSocket(std::string ip, int port);
        int _bind(void);
        int _listen(void);
        int _accept(void);
        int _close(void);
		int _connect(void);
        ~createSocket();
        int getSockfd();
};

#endif