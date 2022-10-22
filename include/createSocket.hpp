/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:54:09 by obeaj             #+#    #+#             */
/*   Updated: 2022/10/22 14:33:39 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATESOCKET_HPP
#define CREATESOCKET_HPP
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>

class createSocket
{
    private:
        int                 sockfd;
        int                 addrlen;
        struct sockaddr_in  address;
    public:
        createSocket();
        createSocket(int domaine, int type, int protocol, u_int32_t ip, int port);
        int init(int domaine, int type, int protocol, u_int32_t ip, int port);
        int _bind(void);
        int _listen(void);
        int _accept(void);
        int _close(void);
        ~createSocket();
        int getSockfd();      
};
#endif