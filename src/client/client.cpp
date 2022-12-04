/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:04:33 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/12/04 11:43:24 by hbel-hou         ###   ########.fr       */
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

std::string	client::handleChunked(std::string req, int connection)
{
	std::string body;
	std::string head;
	std::string temp;

	head = req.find("\r\n\r\n") != std::string::npos ? req.substr(0, req.find("\r\n\r\n") + 4) : req;
	req.erase(req.find(head), head.length());
	for (int i = 0; i < req.size(); i++)
	{
		int j;
		for (j = i; j < req.size(); j++)
		{
			if (req[j] == '\n')
				break ;
		}
		try
		{
			j++;
			temp = req.substr(i, (j - i));
			if (!temp.empty() && temp != "\r\n" &&  IsHexa(temp))
			{
				temp.erase(temp.find("\r\n"), strlen("\r\n"));
				// print(temp);
				int a = hexToDecimal(temp);
				if (a == 0)
					break;
				temp = req.substr(j, a);
				print("////////////////////");
				print(temp);
				print("////////////////////");
				body.append(temp);
				j += a;
			}
			i = j;
		}
		catch(const std::exception& e) {}
	}
	return (head + body);
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
				req_string = handleChunked(req_string, 0);
			// print(req_string);
			request req;
			req = request();
			req.setservers(servers);
			req.requestCheck(getReqString());
			connection = req.getHeaderValue("Connection");
			response res(req, config);
			setResString(res.getResponse());
			print(res.getResponse());
			// std::cout << YELLOW <<res.getResponse() << std::endl;
			req.ClearRequest();
			res.ClearResponse();
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
	// char 	buff[1025];
	// int		ret = 1024;

	if (!isDone())
	{
		// if (isChunked(req_string))
		// {
		// 	// bzero(buff, 1024);
		// 	// ret = recv(connection, buff, 1024, 0);
		// 	// if (ret < 0)
		// 		// return -1;
		// 	// buff[ret] = '\0';
		// 	// if (ret > 0)
		// 		// req_string.append(buff, ret);
		// 	handleChunked(req_string, connection);
		// 	// req_string = handleChunked(req_string);
		// 	// return (500);
		// }
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

