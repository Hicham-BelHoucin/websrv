/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServ.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:06:18 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/21 15:12:25 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "common.h"
#include "createSocket.hpp"
#include "parsing.hpp"
#include "server.hpp"
#include "client.hpp"

class webserv
{
	private:
		std::vector<createSocket>	sockets;
		std::vector<pollfd>			listning_fds;
		std::vector<int>			master_fds;
		std::map<int, client>		clients;
		Data						data;
		std::vector<server>			servers;
		parsing 					config;
    public:
        void init(String);
		void handleInputEvent(createSocket &, pollfd &);
		void handleOutputEvent(createSocket &, pollfd &);
		void eraseSocket(int, int, int);
		void setUpServer(void);
        webserv();
        webserv(String);
        ~webserv();
};

#endif // WEBSERV_HPP