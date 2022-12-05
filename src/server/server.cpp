/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:02:50 by obeaj             #+#    #+#             */
/*   Updated: 2022/12/05 13:02:26 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

server::server()
	: _root()
	, _serverName()
    , _host()
	, _locations()
    , _maxBodySize()
	, _ports()
    , _errorPages()
{}

server::server(String root, String host, String serverName, Set locations, int maxBodySize, std::vector<int> ports, Map errorPages)
	: _root(root)
	, _serverName(serverName)
    , _host(host)
	, _locations(locations)
    , _maxBodySize(maxBodySize)
	, _ports(ports)
    , _errorPages(errorPages)
{}

server::server(const server & obj)
	: _root(obj._root)
	, _serverName(obj._serverName)
    , _host(obj._host)
	, _locations(obj._locations)
    , _maxBodySize(obj._maxBodySize)
	, _ports(obj._ports)
    , _errorPages(obj._errorPages)
{}

server & server::operator=(const server & obj)
{
	if (this != &obj)
	{
		_root = obj._root;
		_serverName = obj._serverName;
		_host = obj._host;
		_locations = obj._locations;
		_maxBodySize = obj._maxBodySize;
		_ports = obj._ports;
		_errorPages = obj._errorPages;
	}
	return *this;
}

server::~server() {}

String server::getRootPath()
{
	size_t index;
	if (_root.back() == '/')
	{
		index = _root.length() - 1;
		_root.erase(index, 1);
	}
	return _root;
}

String server::getHost() const
{
	return _host;
}

Set server::getlocations() const
{
	return _locations;
}

String server::getServerName() const
{
	return _serverName;
}

std::vector<int> server::getPorts() const
{
	return _ports;
}

Map server::getErrorPages() const
{
	return _errorPages;
}

int server::getMaxBodySize() const
{
	return _maxBodySize;
}
