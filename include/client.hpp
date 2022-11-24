/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:03:26 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/11/24 18:20:57 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "common.h"
#include <iostream>
#include "request.hpp"
#include "response.hpp"

class client
{
	private:
		int 		fd;
		std::string req_string;
		std::string res_string;
		bool		donereading;
		bool		chunked;
		request		req;
		response	res;
	public:
		int		_read(int);
		int		_send(int);
		bool	isDone(void);
		void	clean(void);
		std::string getReqString(void) const;
		request	&	getReq(void) {
			return req;
		}
		response	getRes(void) const {
			return res;
		}
		bool	isChunked();
		void	setIsChunked(std::string req);
		void	handleChunked(std::string req, std::string&);
		void	setResString(const std::string & res) {
			// std::string data = readFile(res);
			// if (data == "")
			// 	data = generateErrorPage(404, "Not Found");
			// res_string =
			// 	"HTTP/1.1 200 OK\n"
			// 	"Date: Thu, 19 Feb 2009 12:27:04 GMT\n"
			// 	"Server: Apache/2.2.3\n"
			// 	"Last-Modified: Wed, 18 Jun 2003 16:05:58 GMT\n"
			// 	"ETag: \"56d-9989200-1132c580\"\n"
			// 	"Content-Type: text/html\n"
			// 	"Content-Length: " + std::to_string(res.length()) + "\n"
			// 	"Accept-Ranges: bytes\n"
			// 	"Connection: Keep Alive\n"
			// 	"\n";
			// res_string += res;
			// res_string += "\r\n";
			res_string = res;
		}
		client();
		~client();
};

#endif // CLIENT_HPP