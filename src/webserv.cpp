/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:03:33 by obeaj             #+#    #+#             */
/*   Updated: 2022/10/26 12:58:53 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "webServ.hpp"
#include "request.hpp"

void	get_ports(std::vector<int> & ports, Map map)
{
	std::pair <Map::iterator, Map::iterator> ret;

	ret = map.equal_range("listen");
	while (ret.first != ret.second)
	{
		ports.push_back(atoi(ret.first->second.c_str()));
		ret.first ++;
	}
}

std::string readFile(std::string name)
{
    if (argc != 2)
        return(1);
    (void)argv;
    int new_socket;
    char buffer[2048];
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in add; 
    add.sin_family = AF_INET;
    add.sin_addr.s_addr = INADDR_ANY;
    add.sin_port = htons(PORT);
    bind(sockfd, (struct sockaddr*)&add, sizeof(add));
    int addrlen = sizeof(add);
    const char* reply = 
        "HTTP/1.1 200 OK\n"
        "Date: Thu, 19 Feb 2009 12:27:04 GMT\n"
        "Server: Apache/2.2.3\n"
        "Last-Modified: Wed, 18 Jun 2003 16:05:58 GMT\n"
        "ETag: \"56d-9989200-1132c580\"\n"
        "Content-Type: text/html\n"
        "Content-Length: 75\n"
        "Accept-Ranges: bytes\n"
        "Connection: Keep Alive\n"
        "\n"
        "<h3 style=\"color: blue\">Hello message sent from obeaj host motherfucker<h3>\r\n";
    
    while(1)
    {
        listen(sockfd, 5);
        new_socket = accept(sockfd, (struct sockaddr*)&add,(socklen_t*)&addrlen);
        int valread = read(new_socket, buffer, 2048);
        send(new_socket, reply, strlen(reply), 0);
        request req(buffer);
        std::string key = "Content-Type";
        // std::cout << req.getReqMethod() << std::endl << std::endl;
        // std::cout << req.getHeaderValue(key) <<std::endl;
        // std::cout << "############################## request ###############################\n";
        // std::cout << buffer << std::endl;
        // std::cout << "######################################################################\n";
        // closing the connected socket
        close(new_socket);
    }
    // closing the listening socket
    shutdown(sockfd, SHUT_RDWR);
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

void	acceptConnection(createSocket _socket, int i)
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

void  connect(createSocket    _socket)
{
	int yes = 1;

	if (setsockopt(_socket.getSockfd(), SOL_SOCKET, SO_REUSEADDR,& yes, sizeof(yes)) == -1)
		perror("setsockopt");
    if (_socket._bind() == -1)
        std::cout << "error binding socket" << std::endl;
	if (_socket._listen() == -1)
		std::cout << "error listening socket" << std::endl;
}

createSocket	get_socket(std::vector<createSocket> & sockets, int fd)
{
	for (int i = 0; i < sockets.size(); i++)
    {
		if (sockets[i].getSockfd() == fd)
			return sockets[i];
	}
	return sockets[0];
}

int main(int argc, char const *argv[])
{
    try
	{
		std::vector<int>			ports;
		std::vector<createSocket>	sockets;
		parsing		obj("./conf/config.conf");
		AllData		data = obj.getAllData();
		AllData::iterator it = data.begin();
		std::pair <Map::iterator, Map::iterator> ret;
		fd_set	current_sockets, ready_sockets;
		server			s1;


		Map map = it->second.data;
		while (it != data.end())
        {
			get_ports(ports, it->second.data);
			it++;
		}
		for (int i = 0; i < ports.size(); i++)
		{
			sockets.push_back(createSocket(AF_INET, SOCK_STREAM, 0, map.find("host")->second, ports[i]));
		}
		s1.setSocket(sockets);
		s1.listen();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}
		// init
		// FD_ZERO(&current_sockets);
		// int max_fd;
		// max_fd = sockets.front().getSockfd() + 1;
		// for (int i = 0; i < sockets.size(); i++)
		// {
		// 	connect(sockets[i]);
		// 	FD_SET(sockets[i].getSockfd(), &current_sockets);
		// 	if (max_fd < sockets[i].getSockfd())
		// 		max_fd = sockets[i].getSockfd() + 1;
		// }
		// while (1337)
		// {
		// 	ready_sockets = current_sockets;
		// 	if (select(max_fd, &ready_sockets,NULL, NULL, NULL) == -1)
		// 		perror("select");

		// 	for (int i = 0; i < max_fd; i++)
		// 	{
		// 		if (FD_ISSET(i, &ready_sockets))
		// 		{
		// 			// if (i == sockets[0].getSockfd() || i == sockets[1].getSockfd() || i == sockets[2].getSockfd())
		// 			// {
		// 			// 	// do something
		// 			// 	std::cout << "new connection established" << std::endl;
		// 			// 	FD_SET(new_connection, &current_sockets);
		// 			// 	max_fd = new_connection + 1;
		// 			// }
		// 			// else
		// 			// {
		// 			// 	std::cout << "handle connection" << std::endl;
		// 			// 	FD_CLR(i, &current_sockets);
		// 			// 	// max_fd--;
		// 			// 	// close(i);
		// 			// 	// max_fd
		// 			// }
		// 			// int new_connection = get_socket(sockets, i)._accept();
		// 			acceptConnection(get_socket(sockets, i), 0);
		// 		}
		// 	}
		// }