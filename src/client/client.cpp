/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:04:33 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/12/07 15:51:33 by hbel-hou         ###   ########.fr       */
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
	return (req.find("Transfer-Encoding: chunked") != std::string::npos);
}

size_t		findSpecial(std::string text, size_t index)
{
	while (index < text.size())
	{
		if (text[index] == '\n')
			return index;
		index++;
	}
	return 0;
}


std::string	client::handleChunked(std::string req)
{
	std::string body;
	std::string head;
	std::string temp;
	int end;

	head = req.find("\r\n\r\n") != std::string::npos ? req.substr(0, req.find("\r\n\r\n") + 4) : req;
	req.erase(req.find(head), head.length());
	end = 0;
	for (size_t i = 0; i < req.size();)
	{
		size_t j;
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
				int a = hexToDecimal(temp);
				if (a == 0)
					break;
				temp = req.substr(j, a);
				body.append(temp);
				j += a;
			}
			i = j;
		}
		catch (...){}
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
	// print(req_string);
	if (isDone() == true && req_string != "")
	{
		if (total == 0)
		{
			if (isChunked(req_string))
				req_string = handleChunked(req_string);
			request req;
			req = request();
			req.setservers(servers);
			req.requestCheck(getReqString());
			connection = req.getHeaderValue("Connection");
			response res(req, config);
			setResString(res.getResponse());
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
	static	int 	i;
    char     buff[10025];
    int        ret = 10024;
    int headerslength = 0;
    size_t index = 0;
    int    contentlength = 0;

    bzero(buff, 10024);
    ret = recv(connection, buff, 10024, 0);
    if (ret <= 0)
        return -1;
    buff[ret] = '\0';
    if (ret > 0)
        req_string.append(buff, ret);
    try
    {
        headerslength = req_string.find("\r\n\r\n") != std::string::npos ? req_string.find("\r\n\r\n") + 4 : 0;
        index = req_string.find("Content-Length: ");
		if (index != NOTFOUND)
		{
        	index += strlen("Content-Length: ");
            contentlength = std::stoi(req_string.substr(index, req_string.find("\r\n", index) - index));
      	}
    }
    catch(const std::exception& e)
    {
        headerslength = 0;
        index = 0;
        contentlength = 0;
    }
    if ((req_string.length() < 20048 && isChunked(req_string)) || chunked == true)
    {
		chunked = true;
        size_t index = req_string.find("0\r\n\r\n", i);
        if (index != NOTFOUND)
            this->donereading = true;
		i = req_string.length();
    }
    else if ((contentlength + headerslength <= (int)req_string.length())
            || (!contentlength && ret < 10024))
        this->donereading = true;
    return ret;
}

int	client::_read(int connection)
{
	if (!isDone())
		return normalRevc(connection);
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
	if (rv <= 0)
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
	, chunked(false)
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
	, chunked(false)
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
	, chunked(false)
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

