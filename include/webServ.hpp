/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServ.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:06:18 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/19 11:26:50 by imabid           ###   ########.fr       */
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
    public:
        void init(String);
		void handleInputEvent(createSocket &, pollfd &);
		void handleOutputEvent(createSocket &, pollfd &);
		void eraseSocket(int, int);
		void setUpServer(void);
        webserv();
        webserv(String);
        ~webserv();
};

#endif // WEBSERV_HPP