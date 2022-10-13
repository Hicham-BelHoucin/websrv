/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:58:09 by obeaj             #+#    #+#             */
/*   Updated: 2022/10/13 17:07:20 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "createSocket.hpp"
createSocket::createSocket()
{
    
}
createSocket::createSocket(int domaine, int type, int protocol, u_int32_t ip, int port)
{
    if ((sockfd = socket(domaine, type, protocol)) < 0)
        throw std::runtime_error("Error: Socket cannot be created ! \n");
    address.sin_family = domaine;
    address.sin_addr.s_addr = ip;
    address.sin_port = htons(port);
}
createSocket::~createSocket()
{
    
}