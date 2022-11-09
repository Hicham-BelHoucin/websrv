/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:53:39 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/06 17:20:16 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "request.hpp"

/*-----------------------------Consructors Destructors------------------------------------*/

request::request()
{

}

request::request(const request & obj)
{
	*this = obj;
}

request & request::operator=(const request & obj)
{
	if (&obj != this)
	{
		this->req_method = obj.req_method;
		this->req_path = obj.req_path;
		this->req_version = obj.req_version;
		this->req_body = obj.req_body;
		this->req_headers = obj.req_headers;
		this->error = obj.error;
	}
	return *this;
}

request::request(std::string _req)
{
    std::stringstream reqstream(_req);
    std::string line;
    std::getline(reqstream, line, '\n');
    parseReqMethods(line);
    while (std::getline(reqstream, line, '\n') && line != "\r")
    {
        parseReqLine(line);
    }
    while (std::getline(reqstream, line))
    {
        req_body += stringtrim(line);
        req_body += "\n";
    }

    std::cout << req_method << "\t" << req_path << "\t" << req_version << "\n";
    for (Map::iterator itr = req_headers.begin(); itr !=req_headers.end(); ++itr) {
        if(itr->first != "" && itr->second != "")
        {
            std::cout << itr->first << ":" ;
            std::cout << itr->second << "\n" ;
        }
    }
    std::cout<<std::endl;
    std::cout << req_body;
    std::cout << "\n --------------------------------------------------------------------\n\n";
}

request::~request()
{
}

/*---------------------------------Member functions----------------------------------------*/

void request::parseReqLine(std::string line)
{
    std::stringstream str(line);
    std::string key;
    std::string value;
    std::getline(str, key, ':');
    std::getline(str, value);
    req_headers.insert(Pair(stringtrim(key),stringtrim(value)));
}

void request::parseReqMethods(std::string line)
{
    std::stringstream str(line);
    std::string key;
    std::vector<std::string> values;
    std::string value;

    std::getline(str, key, ' ');
    req_method = stringtrim(key);
    std::getline(str, key, ' ');
    req_path = stringtrim(key);
    std::getline(str, key, ' ');
    req_version = stringtrim(key);
}

/*--------------------------------------Getters-------------------------------------------*/

std::string request::getHeaderValue(std::string key)
{
    try
    {
        return req_headers.at(key);
    }
    catch(...)
    {
        return "NoValue";
    }

}

std::string request::getReqMethod()
{
    return this->req_method;
}

std::string request::getReqVersion()
{
    return this->req_version;
}

std::string request::getReqPath()
{
    return this->req_path;
}

std::string request::getReqBody()
{
    return this->req_body;
}

std::string request::getReqPort()
{
    std::string port = getHeaderValue("Host");
    std::size_t found;

    if((found = port.find_first_of(":") != std::string::npos))
        port = port.substr(found + 1, port.length() - 1);
	return port;
}

std::string request::getReqHost()
{
    std::string host = getHeaderValue("Host");
    std::size_t found;

    if((found = host.find_first_of(":") != std::string::npos))
        host = host.substr(0, found - 1);
	return host;
}