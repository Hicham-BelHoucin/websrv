/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:03:33 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/05 12:57:14 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webServ.hpp"

webserv::webserv()
	: sockets()
	, data()
{}

webserv::~webserv() {
	// if (fds)
	// 	delete [] fds;
}

void webserv::init(String filename)
{
	parsing		obj(filename);
	pollfd		new_fd;

	data = obj.getData();
	sockets = createSockets(data, obj);
	for (int i = 0; i < sockets.size(); i++)
	{
		new_fd.fd = sockets[i].getSockfd();
		new_fd.events = POLLIN | POLLOUT;
		new_fd.revents = 0;
		listning_fds.push_back(new_fd);
		master_fds.push_back(sockets[i].getSockfd());
	}
}

webserv::webserv(String filename)
	: sockets()
	, data()
{
	try
	{
		init(filename);
		setUpServer();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

void	webserv::handleInputEvent(createSocket _socket, pollfd & fd)
{
	int		connection;
	pollfd	new_connection;

	if (std::find(master_fds.begin(), master_fds.end(), _socket.getSockfd()) != master_fds.end())
	{
		connection = _socket._accept();
		if (connection == -1)
			std::cout << strerror(errno) << std::endl;
		new_connection.fd = connection;
		new_connection.events = POLLIN | POLLOUT;
		new_connection.revents = 0;
		sockets.push_back(createSocket(connection, _socket.ip, _socket.port));
		listning_fds.push_back(new_connection);
	}
	else
	{
		_socket._read(_socket.getSockfd());
		fd.events = POLLOUT;
	}
}

void	webserv::eraseSocket(int _index, int index)
{
	sockets[_index]._close();
	sockets.erase(sockets.begin() + _index);
	listning_fds.erase(listning_fds.begin() + index);
}

void	webserv::handleOutputEvent(createSocket _socket, pollfd & fd)
{
	_socket._send(_socket.getSockfd());
	fd.events = POLLIN | POLLOUT;
}

void webserv::setUpServer(void) {
	nfds_t 	nfds;
	nfds_t 	ready;
	int 	index;
	std::map <int, int> client;

	while (1337)
	{
		ready = poll(&(listning_fds[0]), listning_fds.size(), -1);
		if (ready < 0)
			std::cout << strerror(errno) << std::endl;
		if (ready == 0)
			continue ;
		for (nfds_t i = 0; i < listning_fds.size(); i++)
		{
			if (listning_fds[i].revents == 0)
				continue ;
			else
			{
				index = getsocket(sockets, listning_fds[i].fd);
				if (listning_fds[i].revents & POLLERR || listning_fds[i].revents & POLLHUP)
					eraseSocket(index, i);
				if (listning_fds[i].revents & POLLIN)
					handleInputEvent(sockets[index], listning_fds[i]);
				if (listning_fds[i].revents & POLLOUT)
					handleOutputEvent(sockets[index], listning_fds[i]);
			}
		}
	}
}
