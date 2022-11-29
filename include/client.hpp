/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:03:26 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/11/26 18:38:58 by hbel-hou         ###   ########.fr       */
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
		std::string req_string;
		std::string res_string;
		bool		donereading;
		bool		chunked;
		bool		donesending;
		request		req;
		response	res;
		int			sent;
		int			total;
	public:
		int		_read(int);
		int		_send(int);
		bool	isDone(void);
		void	isDoneSending(int v);
		void	setTotal(int v);
		bool	isSent(void);
		void	clean(void);
		std::string getReqString(void) const;
		bool	isChunked();
		void	setIsChunked(std::string req);
		void	handleChunked(std::string req, std::string&);
		void	setResString(const std::string & res) {
			res_string = res;
		}
		client();
		~client();
};

#endif // CLIENT_HPP