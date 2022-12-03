/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:04:33 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/12/03 15:37:53 by imabid           ###   ########.fr       */
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

int 	client::HnadleInputEvent(createSocket & _socket, pollfd & fd) {
	int ret;

	ret = _read(fd.fd);
	if (ret == -1)
		fd.revents = POLLNVAL;
	fd.events = POLLIN | POLLOUT;
	return 0;
};

int 	client::HnadleOutputEvent(createSocket & _socket, pollfd & fd) {
	std::string connection = "";
	if (isDone() == true && req_string != "")
	{
		if (total == 0)
		{
			request req;
			req = request();
			req.setservers(servers);
			req.requestCheck(getReqString());
			response res(req, config);
			setResString(res.getResponse());
			// std::cout << "------------------------------------------------------------------------------------first" << std::endl;
			// print(req_string);
			// std::cout << "------------------------------------------------------------------------------------end" << std::endl;
			// usleep(2000000);
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
	donereading = false;
}

bool	client::isDone(void)
{
	return donereading;
}

std::string		client::getReqString() const
{
	return req_string;
}

int    client::_read(int connection)
{
    char     buff[1025];
    int        ret = 1024;
    int headerslength = 0;
    int index = 0;
    int    contentlength = 0;

    bzero(buff, 1024);

    if (!isDone())
    {
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
	{
		clean();
		total = 0;
		sent = 0;
	}
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

