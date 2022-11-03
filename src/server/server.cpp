/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:02:50 by obeaj             #+#    #+#             */
/*   Updated: 2022/10/31 16:37:07 by hbel-hou         ###   ########.fr       */
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