/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:02:50 by obeaj             #+#    #+#             */
/*   Updated: 2022/10/25 13:50:11 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
static std::string readFile(std::string name)
{
    std::ifstream   in_file(name);
    std::string     text;
    std::string     line;

    if (in_file.is_open())
    {
        while (getline(in_file, line, '\0'))
            text += line;
    }
    else
        std::cout << "error" << std::endl;
    return text;
}

server::server() : max_fd(0)
{
	FD_ZERO(&current_sockets);
}

void server::setSocket(vector&	s)
{
	for (int i = 0; i < s.size(); i++)
	{
		s[i]._bind();
		s[i]._listen();
		FD_SET(s[i].getSockfd(), &current_sockets);
		if (max_fd < s[i].getSockfd())
			max_fd = s[i].getSockfd();
	}
	this->sockets = s;
}

createSocket server::getSocket(int fd)
{
	for (int i = 0; i < sockets.size(); i++)
	{
		if (sockets[i].getSockfd() == fd)
			return sockets[i];
	}
	return sockets[0];
}

void	server::acceptConnection(createSocket _socket)
{
	int             connection;
    char            buff[1024];
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
    response += readFile("./src/page.html");
	response += "\r\n";
    connection = _socket._accept();
    if (connection == -1)
        std::cout << "error accepting connection" << std::endl;
    read(connection, buff, 1024);
    write(connection, response.c_str(), response.size());
    close(connection);
}

void	server::listen()
{
	fd_set ready_sockets;
	while (1337)
	{
		ready_sockets = current_sockets;
		if (select(max_fd, &ready_sockets,NULL, NULL, NULL) == -1)
			perror("select");
		for (int i = 0; i < max_fd; i++)
		{
			if (FD_ISSET(i, &ready_sockets))
			{
				acceptConnection(getSocket(i));
			}
		}
	}
}

server::~server()
{
}