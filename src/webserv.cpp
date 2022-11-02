/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:03:33 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/02 16:02:57 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webServ.hpp"

webserv::webserv()
	: sockets()
	, data()
	, fds(nullptr)
{}

webserv::~webserv() {
	// if (fds)
	// 	delete [] fds;
}

webserv::webserv(String filename)
	: sockets()
	, data()
	, fds(nullptr)
{
	try
	{
		parsing		obj(filename);
		data = 		obj.getData();
		sockets = createSockets(data, obj);
		setUpServer();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

void webserv::setUpServer(void) {
	nfds_t 	nfds;
	nfds_t 	ready = 0;
	createSocket soc;

	fds = getfds(sockets);
	while (1337)
	{
		ready = poll(fds, nfds, -1);
		for (nfds_t i = 0; i < sockets.size(); i++)
		{
			if (fds[i].revents = 0)
				continue ;
			else
			{
				soc = getsocket(sockets, fds[i].fd);
				int connection = soc._accept();
				if (connection != -1)
					perror("accept");
				soc._read(connection);
				soc._send(connection);
				close(connection);
			}
		}
	}
}
