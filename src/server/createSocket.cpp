/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:58:09 by obeaj             #+#    #+#             */
/*   Updated: 2022/10/24 16:46:50 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "createSocket.hpp"

createSocket::createSocket()
{

}

int createSocket::init(int domaine, int type, int protocol, std::string ip, int port)
{
    sockfd = socket(domaine, type, protocol);
    address.sin_family = domaine;
	this->port = port;
	this->ip = ip;
	if (inet_aton(ip.c_str(), &(address.sin_addr)) == -1)
		perror("inet_aton");
    address.sin_port = htons(port);
    addrlen = sizeof(address);
    return sockfd;
}

int createSocket::_close(void)
{
    return shutdown(sockfd, SHUT_RDWR);;
}

int createSocket::_bind(void)
{
    return bind(sockfd, (struct sockaddr*)&address, sizeof(address));
}

int createSocket::_accept(void)
{
    return accept(sockfd, (struct sockaddr*)&address,(socklen_t*)&addrlen);
}

int createSocket::_listen(void)
{
	if (listen(sockfd, 5) == -1)
		return (-1);
	std::cout << "listing on port: " << ip << ":" << port << std::endl;
    return (0);
}

createSocket::createSocket(int domaine, int type, int protocol, std::string ip, int port)
{
    if ((sockfd = socket(domaine, type, protocol)) < 0)
        throw std::runtime_error("Error: Socket cannot be created ! \n");
    address.sin_family = domaine;
    if (inet_aton(ip.c_str(), &(address.sin_addr)) == -1)
		perror("inet_aton");
    address.sin_port = htons(port);
    addrlen = sizeof(address);
	this->port = port;
	this->ip = ip;
}

createSocket::~createSocket()
{

}