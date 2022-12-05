/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:03:26 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/12/05 13:34:16 by hbel-hou         ###   ########.fr       */
/*   Updated: 2022/12/04 17:24:03 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "common.h"
#include "utils.h"
#include <iostream>
#include "request.hpp"
#include "response.hpp"

class client
{
	private:
		std::string 				req_string;
		std::string 				res_string;
		bool						donereading;
		bool						chunked;
		bool						donesending;
		int 						sent;
		int							total;
		std::vector<server>			servers;
		parsing 					config;
		std::string 				connection;
	public:
		int				_read(int);
		int				_send(int);
		bool			isDone(void);
		void			isDoneSending(int v);
		void			setTotal(int v);
		void			setDoneReading(bool value);
		bool			isSent(void);
		void			clean(void);
		std::string		getReqString(void) const;
		bool			isChunked(std::string req);
		int 			HnadleInputEvent(pollfd & fd);
		int 			HnadleOutputEvent(pollfd & fd);
		int				normalRevc(int connection);
		std::string		handleChunked(std::string req);
		void			setResString(const std::string & res);
		client(void);
		client(const std::vector<server> servers, const parsing config);
		client(const client & copy);
		client & operator=(const client & assign);
		~client();
};

#endif // CLIENT_HPP