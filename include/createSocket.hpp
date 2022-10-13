/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:54:09 by obeaj             #+#    #+#             */
/*   Updated: 2022/10/12 16:50:44 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATESOCKET_HPP
#define CREATESOCKET_HPP
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <errno.h>

class createSocket
{
    private:
        int sockfd;
        struct sockaddr_in address;
    public:
        createSocket();
        createSocket(int domaine, int type, int protocol, u_int32_t ip, int port);
        ~createSocket();
        int getSockfd();      
};
#endif