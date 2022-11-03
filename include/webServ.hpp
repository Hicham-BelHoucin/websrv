/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServ.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:06:18 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/02 12:55:28 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "common.h"
#include "createSocket.hpp"
#include "parsing.hpp"
#include "server.hpp"

class webserv
{
	private:
		std::vector<createSocket>	sockets;
		Data						data;
		pollfd						*fds;
    public:
        webserv();
        webserv(String);
		void	setUpServer(void);
        ~webserv();
};

#endif // WEBSERV_HPP