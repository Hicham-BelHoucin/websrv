/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:30:15 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/11/30 14:01:22 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webServ.hpp"

webserv::webserv()
	: sockets()
	, listning_fds()
	, master_fds()
	, clients()
	, data()
	, servers()
	, config()
{}

webserv::webserv(String filename)
	: sockets()
	, listning_fds()
	, master_fds()
	, clients()
	, data()
	, servers()
	, config()
{
	try
	{
		printLogs("\n\n\n\n---------------------------------[" \
			+ _displayTimestamp() + " start new web server session " + getenv("USER") \
			+ "]---------------------------------");
		init(filename);
		printLogs(_displayTimestamp() + "server initialized successfully");
		printLogs(_displayTimestamp() + "start listing ... ");
		setUpServer();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
}

webserv::webserv(const webserv & copy)
	: sockets(copy.sockets)
	, listning_fds(copy.listning_fds)
	, master_fds(copy.master_fds)
	, clients(copy.clients)
	, data(copy.data)
	, servers(copy.servers)
	, config(copy.config)
{}

webserv & webserv::operator=(const webserv & assgin)
{
	if (this != &assgin)
	{
		sockets = assgin.sockets;
		listning_fds = assgin.listning_fds;
		master_fds = assgin.master_fds;
		clients = assgin.clients;
		data = assgin.data;
		servers = assgin.servers;
		config = assgin.config;
	}
	return *this;
}

webserv::~webserv()
{
}

void webserv::init(String filename)
{
	parsing obj(filename);
	this->config = obj;
	pollfd new_fd;

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
	servers = createServers(data, obj);
}


void webserv::handleInputEvent(createSocket &_socket, pollfd &fd)
{
	int connection;
	pollfd new_connection;

	if (std::find(master_fds.begin(), master_fds.end(), fd.fd) != master_fds.end())
	{
		client  c(servers, config);
		connection = _socket._accept();
		if (connection == -1)
			return check(1);
		new_connection.fd = connection;
		new_connection.events = POLLIN | POLLOUT;
		new_connection.revents = 0;
		sockets.push_back(createSocket(connection, _socket.ip, _socket.port));
		listning_fds.push_back(new_connection);
		fd.events = POLLIN | POLLOUT;
		fd.revents = 0;
		clients.insert(std::make_pair(new_connection.fd, c));
		print("received new connection : " + _socket.ip + ":" + std::to_string(_socket.port));
	}
	else
	{
		if (clients.find(fd.fd) != clients.end())
		{
			int ret;
			client & c = clients[fd.fd];
			c.HnadleInputEvent(_socket, fd);
		}
	}
}

void webserv::eraseSocket(int _index, int index, int fd)
{
	sockets[_index]._close();
	sockets.erase(sockets.begin() + _index);
	listning_fds.erase(listning_fds.begin() + index);
	clients.erase(fd);
}

void webserv::handleOutputEvent(createSocket &_socket, pollfd &fd)
{
	if (clients.find(fd.fd) != clients.end())
	{
		client &c = clients[fd.fd];
		c.HnadleOutputEvent(_socket, fd);
	}
}

void webserv::setUpServer(void)
{
	nfds_t nfds;
	nfds_t ready;
	int index;

	while (1337)
	{
		ready = poll(&(listning_fds[0]), listning_fds.size(), -1);
		check(ready < 0);
		if (ready == 0)
			continue;
		for (nfds_t i = 0; i < listning_fds.size(); i++)
		{
			if (listning_fds[i].revents == 0)
				continue;
			else
			{
				index = getsocket(sockets, listning_fds[i].fd);
				if (index == -1)
					continue;
				if (listning_fds[i].revents & POLLERR || listning_fds[i].revents & POLLHUP)
					eraseSocket(index, i, listning_fds[i].fd);
				if (listning_fds[i].revents & POLLIN)
					handleInputEvent(sockets[index], listning_fds[i]);
				if (listning_fds[i].revents & POLLOUT)
					handleOutputEvent(sockets[index], listning_fds[i]);
				if (listning_fds[i].revents & POLLNVAL)
				{
					eraseSocket(index, i, listning_fds[i].fd);
					print("deleted");
					break;
				}
			}
		}
	}
}
