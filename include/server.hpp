/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:02:25 by obeaj             #+#    #+#             */
/*   Updated: 2022/10/25 13:42:43 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEVER_HPP
#define SEVER_HPP

#include "common.h"
#include "createSocket.hpp"
typedef std::vector<createSocket>	vector;
class server
{
	private:
		fd_set						current_sockets;
		int							max_fd;
		vector						sockets;
	public:
		server(/* args */);
		createSocket	getSocket(int fd);
		void            setSocket(vector & s);
		void            acceptConnection(createSocket _socket);
		void 			listen();
		~server();
};

#endif // SEVER_HPP