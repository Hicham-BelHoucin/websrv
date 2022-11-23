/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:03:26 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/11/23 17:25:39 by obeaj            ###   ########.fr       */
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
		void	setResString(const std::string & res) 
		{
			res_string = res;
		}
		client();
		~client();
};

#endif // CLIENT_HPP