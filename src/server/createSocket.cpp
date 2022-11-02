/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:58:09 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/02 16:01:20 by hbel-hou         ###   ########.fr       */
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

int	 createSocket::_read(int connection)
{
	char 	buff[100] = {0};
	ssize_t	i = 1;
	String 	str;

	while (i)
	{
		i = recv(connection, buff, 99, 0);
		if (i == -1)
			perror("recv");
		str += buff;
		if (i < 99)
			break;
	}
	std::cout << str << std::endl;
	return sockfd;
}

int	 createSocket::_send(int connection)
{
    std::string response;
	response =
        "HTTP/1.1 200 OK\n"
        "Date: Thu, 19 Feb 2009 12:27:04 GMT\n"
        "Server: Apache/2.2.3\n"
        "Last-Modified: Wed, 18 Jun 2003 16:05:58 GMT\n"
        "ETag: \"56d-9989200-1132c580\"\n"
        "Content-Type: text/html\n"
        "Content-Length: 1900\n"
        "Accept-Ranges: bytes\n"
        "Connection: Keep Alive\n"
        "\n";
    response += readFile("/Users/hbel-hou/Desktop/websrv/src/page.html");
	response += "\r\n";
    send(connection, response.c_str(), response.size(), 0);
    close(connection);
	return sockfd;
}

int	 createSocket::_connect(void)
{
	if (_bind() == -1)
		perror("bind");
	return _listen();
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

createSocket::createSocket(std::string ip, int port)
{
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        throw std::runtime_error("Error: Socket cannot be created ! \n");
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