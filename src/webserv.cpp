/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:03:33 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/19 10:51:21 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webServ.hpp"

webserv::webserv()
	: sockets()
	, data()
{}

webserv::~webserv() {

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
		printLogs("\n\n\n\n---------------------------------[" \
			+ _displayTimestamp() + " start new web server session " + getenv("USER") \
			+ "]---------------------------------");
		init(filename);
		printLogs(_displayTimestamp() + "server initialized successfully");
		printLogs(_displayTimestamp() + "start listing ... ");
		setUpServer();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

void	webserv::handleInputEvent(createSocket & _socket, pollfd & fd)
{
	int		connection;
	pollfd	new_connection;

	if (std::find(master_fds.begin(), master_fds.end(), fd.fd) != master_fds.end())
	{
		client  c;
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
		clients.insert(std::make_pair(fd.fd, c));
	}
	else
	{
		int ret;
		client & c = clients[fd.fd];
		ret = c._read(fd.fd);
		// if (ret == -1)
		// 	fd.revents = POLLNVAL;
		fd.events = POLLIN | POLLOUT;
	}
}

void	webserv::eraseSocket(int _index, int index)
{
	sockets[_index]._close();
	sockets.erase(sockets.begin() + _index);
	listning_fds.erase(listning_fds.begin() + index);
}

void	webserv::handleOutputEvent(createSocket & _socket, pollfd & fd)
{
	client &c = clients[fd.fd];
	std::string connection;
	if (c.isDone() == true)
	{
		request &req = c.getReq();
		req = request(); 
		req.requestCheck(c.getReqString());
		connection = req.getHeaderValue("Connection");
		if (c._send(fd.fd) < 0 || connection == "close")
			fd.revents = POLLNVAL;
		fd.events = POLLIN;
		c.clean();
	}
}

void webserv::setUpServer(void) {
	nfds_t 	nfds;
	nfds_t 	ready;
	int 	index;

	while (1337)
	{
		ready = poll(&(listning_fds[0]), listning_fds.size(), -1);
		check(ready < 0);
		if (ready == 0)
			continue ;
		for (nfds_t i = 0; i < listning_fds.size(); i++)
		{
			if (listning_fds[i].revents == 0)
				continue ;
			else
			{
				index = getsocket(sockets, listning_fds[i].fd);
				if (index == -1)
					continue ;
				if (listning_fds[i].revents & POLLERR || listning_fds[i].revents & POLLHUP)
					eraseSocket(index, i);
				if (listning_fds[i].revents & POLLIN)
					handleInputEvent(sockets[index], listning_fds[i]);
				if (listning_fds[i].revents & POLLOUT)
					handleOutputEvent(sockets[index], listning_fds[i]);
				if (listning_fds[i].revents & POLLNVAL)
					eraseSocket(index, i);
			}
		}
	}
}
