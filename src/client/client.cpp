/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:04:33 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/12/02 15:44:06 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

void	client::isDoneSending(int value)
{
	sent = value;
}

void	client::setDoneReading(bool value)
{
	donereading = value;
}

void	client::setTotal(int value)
{
	total = value;
}

bool	client::isSent(void) {
	return donesending;
};

void	client::setResString(const std::string & res) {
	res_string = res;
}

int 	client::HnadleInputEvent(pollfd & fd) {
	int ret;

	ret = _read(fd.fd);
	if (ret == -1)
		fd.revents = POLLNVAL;
	fd.events = POLLIN | POLLOUT;
	return 0;
};

int 	client::HnadleOutputEvent(pollfd & fd) {
	std::string connection = "";
	if (isDone() == true && req_string != "")
	{
		if (total == 0)
		{
			print(req_string);
			request req;
			req = request();
			req.setservers(servers);
			req.requestCheck(getReqString());
			response res(req, config);
			setResString(res.getResponse());
		}
		_send(fd.fd);
	}
	fd.events = POLLIN | POLLOUT;
	return 0;
};

void	client::clean(void)
{
	req_string.clear();
	res_string.clear();
	total = 0;
	sent = 0;
	donereading = false;
	donesending = true;
}

bool	client::isDone(void)
{
	return donereading;
}

std::string		client::getReqString() const
{
	return req_string;
}

int	client::_read(int connection)
{
	char 	buff[501];
	int		ret = 500;

	bzero(buff, 500);
	if (!isDone())
	{
		ret = recv(connection, buff, 500, 0);
		if (ret < 0)
			return -1;
		buff[ret] = '\0';
		if (ret == 0 || ret < 500)
			this->donereading = true;
		if (ret > 0)
			req_string.append(buff, ret);
	}
	return ret;
}

int	client::_send(int connection)
{
	int rv;

	rv = 0;
	if (total == 0)
	{
		total = res_string.length();
		sent = 0;
	}
	if (res_string.length() - sent > 0)
		rv = send(connection, res_string.c_str() + sent, res_string.length() - sent, 0);
	if (rv == -1)
		return -1;
	sent += rv;
	if ((total != 0 && total == sent))
		clean();
	return 0;
}

client::client(void)
	: req_string("")
	, res_string("")
	, donereading(false)
	, donesending(true)
	, sent(0)
	, total(0)
	, servers()
	, config()
{}

client::client(const std::vector<server> servers, const parsing config)
	: req_string("")
	, res_string("")
	, donereading(false)
	, donesending(true)
	, sent(0)
	, total(0)
	, servers(servers)
	, config(config)
{}

client::client(const client & copy)
	: req_string(copy.req_string)
	, res_string(copy.res_string)
	, donereading(copy.donereading)
	, donesending(copy.donesending)
	, sent(copy.sent)
	, total(copy.total)
	, servers(copy.servers)
	, config(copy.config)
{}

client & client::operator=(const client & assign)
{
	if (this != &assign)
	{
		req_string = assign.req_string;
		res_string = assign.res_string;
		donereading = assign.donereading;
		chunked = assign.chunked;
		donesending = assign.donesending;
		sent = assign.sent;
		total = assign.total;
		servers = assign.servers;
		config = assign.config;
	}
	return *this;
}

client::~client()
{
}

