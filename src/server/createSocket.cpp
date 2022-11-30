/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:34:14 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/11/30 10:24:41 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "createSocket.hpp"

createSocket::createSocket()
{

}

int	 createSocket::getSockfd(void)
{
	return sockfd;
}

int	 createSocket::_connect(void)
{
	if (_bind() == -1)
		throw std::runtime_error("cannot start a web server");
	return _listen();
}

int createSocket::_close(void)
{
	shutdown(sockfd, SHUT_RDWR);
    return close(sockfd);
}

int createSocket::_bind(void)
{
	int yes = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    return bind(sockfd, (struct sockaddr*)&address, sizeof(address));
}

int createSocket::_accept(void)
{
    return accept(sockfd, (struct sockaddr*)&address,(socklen_t*)&addrlen);
}

int createSocket::_listen(void)
{
	if (listen(sockfd, -1) == -1)
		return (-1);
	std::cout << "listing on port: " << ip << ":" << port << std::endl;
    return (0);
}

createSocket::createSocket(int connection, std::string ip, int port)
{
	sockfd = connection;
    address.sin_family = AF_INET;
    if (inet_aton(ip.c_str(), &(address.sin_addr)) == -1)
		perror("inet_aton");
    address.sin_port = htons(port);
    addrlen = sizeof(address);
	this->port = port;
	this->ip = ip;
}

createSocket::createSocket(std::string ip, int port)
{
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        throw std::runtime_error("Error: Socket cannot be created ! \n");
	fcntl(sockfd, F_SETFL, O_NONBLOCK);
    address.sin_family = AF_INET;
    if (inet_aton(ip.c_str(), &(address.sin_addr)) == -1)
		perror("inet_aton");
    address.sin_port = htons(port);
    addrlen = sizeof(address);
	this->port = port;
	this->ip = ip;
	_connect();
}

createSocket::~createSocket()
{

}