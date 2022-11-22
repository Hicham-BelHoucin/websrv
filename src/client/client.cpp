/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:04:33 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/11/21 16:44:48 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

client::client(/* args */) : donereading(false)
{
	std::string data = readFile("./src/index.html");
	res_string =
        "HTTP/1.1 200 OK\n"
        "date: Thu, 19 Feb 2009 12:27:04 GMT\n"
        "derver: Apache/2.2.3\n"
        "last-modified: Wed, 18 Jun 2003 16:05:58 GMT\n"
        "ETag: \"56d-9989200-1132c580\"\n"
        "Content-Type: text/html\n"
        "Content-Length: " + std::to_string(data.length()) + "\n"
        "Accept-Ranges: bytes\n"
        "Connection: Keep Alive\n"
        "\n";
    res_string += data;
	res_string += "\r\n";
}

void	client::clean(void)
{
	req_string.clear();
	// you will need to uncomment this when you merge response
	// res_string.clear();
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

int	client::_read(int connection)
{
	char 	buff[1001];
	int		ret = 0;

	bzero(buff + 0, 1001);
	if (!isDone())
	{
		ret = recv(connection, buff, 999, 0);
		buff[ret] = '\0';
		if (ret < 0)
		{
			// print(ret);
			return -1;
		}
		if (ret == 0 || ret < 999)
			this->donereading = true;
		req_string += static_cast<std::string>(buff);
	}
	return ret;
}

int	client::_send(int connection)
{
	char *buffptr;
	int rv;
	int len;

	len = res_string.length();
	buffptr = (char *)res_string.c_str();
	while (len > 0)
	{
		rv = send(connection, buffptr, len, 0);
		if (rv < 0)
			return rv;
		buffptr += rv;
		len -= rv;
	}
	return rv;
}

client::~client()
{
}