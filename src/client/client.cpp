/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:04:33 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/12/03 15:50:17 by hbel-hou         ###   ########.fr       */
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

bool	client::isChunked(std::string req)
{
	return (req.find("Transfer-Encoding: chunked")!= std::string::npos);
}

std::string	client::handleChunked(std::string req)
{
	std::string			line;
	int					index;
	std::string 		body = req.find("\r\n\r\n") != std::string::npos ? req.substr(req.find("\r\n\r\n") + 4) : "";
	std::stringstream	str(body);

	index = 0;
	while (getline(str, line, '\n'))
	{
		// print(line);
		if (IsHexa(line) == 1)
		{
			line.append("\n");
			index = req.find(line, index);
			if (index != std::string::npos)
				req.erase(index, line.length());
			index += line.length();
		}
	}
	return (req);
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
	if (isDone() == true && req_string != "")
	{
		if (total == 0)
		{
			if (isChunked(req_string))
				req_string = handleChunked(req_string);
			// print(req_string);
			// exit(0);
			request req;
			req = request();
			req.setservers(servers);
			req.requestCheck(getReqString());
			connection = req.getHeaderValue("Connection");
			response res(req, config);
			setResString(res.getResponse());
		}
		if (_send(fd.fd) == -1 || connection == "close")
			fd.revents = POLLNVAL;
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
	chunked = false;
}

bool	client::isDone(void)
{
	return donereading;
}

std::string		client::getReqString() const
{
	return req_string;
}

int client::normalRevc(int connection)
{
	char 	buff[1025];
	int		ret = 1024;
	int headerslength = 0;
	int index = 0;
	int	contentlength = 0;

	bzero(buff, 1024);
	ret = recv(connection, buff, 1024, 0);
	if (ret < 0)
		return -1;
	buff[ret] = '\0';
	if (ret > 0)
		req_string.append(buff, ret);
	try
	{
		headerslength = req_string.find("\r\n\r\n") != std::string::npos ? req_string.find("\r\n\r\n") + 4 : 0;
		index = req_string.find("Content-Length: ") + strlen("Content-Length: ");
		contentlength = std::stoi(req_string.substr(index, req_string.find("\r\n", index) - index));
	}
	catch(const std::exception& e)
	{
		headerslength = 0;
		index = 0;
		contentlength =0;
	}
	if ((contentlength + headerslength <= req_string.length())
			|| (!contentlength && ret < 1024))
		this->donereading = true;
	return ret;
}

int	client::_read(int connection)
{
	if (!isDone())
	{
		return normalRevc(connection);
	}
	return 0;
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
	return rv;
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
	, chunked(false)
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
	, chunked(false)
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
	, chunked(false)
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

