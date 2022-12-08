/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:02:25 by obeaj             #+#    #+#             */
/*   Updated: 2022/12/07 15:59:06 by hbel-hou         ###   ########.fr       */
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
		String 				_return;
	public:
		String 				getRootPath(void);
		String 				getHost(void) const;
		String 				getReturn(void) const;
		Set 				getlocations(void) const;
		String				getServerName(void) const;
		std::vector<int>	getPorts(void) const;
		Map 				getErrorPages(void) const;
		int 				getMaxBodySize(void) const;
		server(void);
		server(String, String, String, Set, int, std::vector<int>, Map, String);
		server(const server & obj);
		server & operator=(const server & obj);
		~server(void);
};

#endif // SEVER_HPP