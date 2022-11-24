/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:04:33 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/11/24 18:20:47 by hbel-hou         ###   ########.fr       */
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

bool	client::isChunked()
{
	return chunked;
}

void	client::handleChunked(std::string req, std::string &body)
{
	static int toLoaded;
	int index = req.find("\r\n\r\n");
	std::string headers;
	headers = index != std::string::npos ? req.substr(0, index + 4) : "";
	std::stringstream str(index != std::string::npos ? req.substr(index + 4) : req);
	std::string line;
	std::string tocopy;
	if (!toLoaded)
	{
		if (!headers.empty())
			body.append(headers);
		while (getline(str, line, '\n'))
		{
			if (line.find_first_not_of("0123456789abcdefABCDEF\r\n") == std::string::npos)
			{
				toLoaded = hexToDecimal(line);
				if (toLoaded == 0)
					return ;
				tocopy = str.str().substr(line.length() + 1, toLoaded);
				body.append(tocopy);
				toLoaded -= tocopy.length();
				return ;
			}
		}
	}
	else
	{
		if (req.find("0\r\n") != std::string::npos)
			req.erase(req.find("0\r\n"), 3);
		body.append(req);
		toLoaded -= req.length();
	}
	if (toLoaded < 0)
	{
		print("'" + body + "'");
		toLoaded = 0;
	}
}

void	client::setIsChunked(std::string req){
	chunked = (req.find("Transfer-Encoding: chunked")!= std::string::npos);
}

int	client::_read(int connection)
{
	static int i;
	char 	buff[1001];
	std::string _req;
	int		ret = 0;

	bzero(buff + 0, 1001);
	if (!isDone())
	{
		ret = recv(connection, buff, 999, 0);
		buff[ret] = '\0';
		if (ret < 0)
			return -1;
		if (!i)
			setIsChunked(buff);
		if (isChunked() == true)
			handleChunked(buff, req_string);
		else
			req_string += static_cast<std::string>(buff);
		if (ret == 0 || ret < 999)
		{
			this->donereading = true;
			i = -1;
		}
	}
	i++;
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