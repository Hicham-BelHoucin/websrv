/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:02:50 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/03 00:39:50 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

server::server() {}
server::~server() {}
server::server(String root, String host, String serverName, Set locations, int maxBodySize, std::vector<int> ports, Map errorPages)
	: _root(root)
    , _host(host)
	, _serverName(serverName)
	, _locations(locations)
    , _maxBodySize(maxBodySize)
	, _ports(ports)
    , _errorPages(errorPages)
{}

String server::getRootPath()
{
	return _root;
}
String server::getHost()
{
	return _host;
}
Set server::getlocations()
{
	return _locations;
}
String server::getServerName()
{
	return _serverName;
}
std::vector<int> server::getPorts()
{
	return _ports;
}
Map server::getErrorPages()
{
	return _errorPages;
}