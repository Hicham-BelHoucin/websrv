/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:02:25 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/19 11:55:40 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEVER_HPP
#define SEVER_HPP

#include "common.h"
#include "utils.h"
#include "createSocket.hpp"
class server
{
	private:
		String 				_root;
		String 				_serverName;
		String 				_host;
		Set					_locations;
		int                 _maxBodySize;
		std::vector<int>	_ports;
		Map					_errorPages;
	public:
		server();
		server(String, String, String, Set, int, std::vector<int>, Map);
		server & operator=(const server & obj) {
			_root = obj._root;
			_serverName = obj._serverName;
			_host = obj._host;
			_locations = obj._locations;
			_maxBodySize = obj._maxBodySize;
			_ports = obj._ports;
			_errorPages = obj._errorPages;
			return *this;
		}
		String getRootPath();
		String getHost();
		Set getlocations();
		String getServerName();
		std::vector<int> getPorts();
		Map getErrorPages();
		int getMaxBodySize() {
			// fix this later
			return _maxBodySize * 1000000;
		}
		~server();
};

#endif // SEVER_HPP