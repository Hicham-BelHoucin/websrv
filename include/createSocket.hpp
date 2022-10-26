/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:54:09 by obeaj             #+#    #+#             */
/*   Updated: 2022/10/25 13:07:29 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATESOCKET_HPP
#define CREATESOCKET_HPP

#include "common.h"
class createSocket
{
    private:
        int                 sockfd;
        int                 addrlen;
		int					port;
		std::string			ip;
        struct sockaddr_in  address;
    public:
        createSocket();
        createSocket(int domaine, int type, int protocol, std::string ip, int port);
        int init(int domaine, int type, int protocol, std::string ip, int port);
        int _bind(void);
        int _listen(void);
        int _accept(void);
        int _close(void);
        ~createSocket();
        int getSockfd(){return sockfd;};
};
#endif