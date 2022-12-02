/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:32:40 by obeaj             #+#    #+#             */
/*   Updated: 2022/12/02 11:39:55 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
        int 		_bind(void);
        int 		_listen(void);
        int 		_accept(void);
        int 		_close(void);
		int 		_connect(void);
        int 		_read(int connection);
        int 		_send(int connection);
        int 		getSockfd();
        bool		operator==(const createSocket &);
        createSocket();
        createSocket(int sockfd, std::string ip, int port);
        createSocket(std::string ip, int port);
        createSocket(const createSocket & obj);
        createSocket & operator=(const createSocket & obj);
        ~createSocket();
};

#endif