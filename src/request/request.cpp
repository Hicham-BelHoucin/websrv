/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:30:49 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/21 16:49:25 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "request.hpp"
#include "utils.h"

/*-----------------------------Consructors Destructors------------------------------------*/

request::request()
{
	status = 200;
    req = "";
	req_method ="";
	req_body ="";
	req_version ="";
	req_path= "";
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

}

/*---------------------------------Member functions----------------------------------------*/

void    request::requestPrint()
{
    std::cout << "----------------------------------------Request---------------------------------------------------"<< std::endl;

    std::cout << "\e[1;35mMethod :\e[1;36m " << req_method <<"\e[1;33m"<< std::endl;
    std::cout << "\e[1;35mUrl :\e[1;36m " << req_path <<"\e[1;33m"<< std::endl;
    std::cout << "\e[1;35mVersion :\e[1;36m " << req_version <<"\e[1;33m"<< std::endl;
    if(!req_query.empty())
        std::cout << "\e[1;35mQuery :\e[1;36m " << req_query <<"\e[1;33m"<< std::endl;
    for(std::map<std::string ,std::string>::iterator it = req_headers.begin(); it != req_headers.end() ; it++)
	{
		std::cout << "\e[1;35m" << it->first << ":\e[1;36m " << it->second <<"\e[1;33m"<<std::endl;
	}
    if(!req_body.empty())
        std::cout << "\e[1;35mBody :\e[1;36m " << req_body <<"\e[1;33m"<< std::endl;

    std::cout << "--------------------------------------------------------------------------------------------------"<<std::endl;
}

int request::requestCheck(std::string _req)
{
    req = _req;
    int st = 0;
    if((st = parseReqMethods()) || (st = parseHeaders()))
    {
        status = st;
        return status;
    }
    requestPrint();
    return 0;
}

request::~request()
{
}

int request::parseHeaders()
{
    std::string all;
    int lt_of_head;
    std::string key;
    std::string value;

    while ((lt_of_head = req.find("\r\n")) != std::string::npos)
    {
        if(lt_of_head == 0)
        {
            req = req.substr(req.find("\r\n") + 2,req.length());
            break;
        }
        all = req.substr(0, lt_of_head);
        if(all.find(':') == std::string::npos)
            return ResponseIUtils::BAD_REQUEST;
        key = all.substr(0,all.find(':'));
        value = all.substr(all.find(' ') + 1, all.length());
        req_headers.insert(std::make_pair((key), value));
        if(req_headers.count("Host") > 1  || req_headers.count("Host") < 0)
            return ResponseIUtils::BAD_REQUEST;
        req = req.substr(req.find("\r\n") + 2,req.length());
    }
    std::map<std::string,std::string>::iterator it;
    std::string port;
    if((it = req_headers.find("Host") ) != req_headers.end())
    {
        port = it->second.substr(it->second.find(":") + 1, it->second.length());
        if(!isNumber(port))
            return ResponseIUtils::BAD_REQUEST;
    }
    if((it = req_headers.find("Content-Type")) != req_headers.end())
    {
        if(it->second.find("multipart") != std::string::npos && it->second.find("boundary") == std::string::npos)
            return ResponseIUtils::BAD_REQUEST;
    }
    if((it = req_headers.find("Content-Length") )!= req_headers.end())
    {
        server obj;

        obj = selectServer(servers, getReqHost(), getReqPort());
        if(!isNumber(it->second))
        {
            return ResponseIUtils::BAD_REQUEST;
        }
        if(std::stoi(it->second) > obj.getMaxBodySize())
            return REQUEST_ENTITY_TOO_LARGE;
    }
    if(!req.empty())
        req_body = req;
    return 0;
}

int request::parseReqMethods()
{
    std::string r_line;
    std::string r_all;
    int f = req.find("\r\n");
    if(f != std::string::npos)
    {
        r_line = req.substr(0,req.find("\n"));
        r_all = r_line.substr(0,r_line.find(' '));
        if(r_all != "GET" && r_all != "PUT" && r_all != "DELETE" && r_all != "POST")
            return ResponseIUtils::NOT_IMPLEMENTED;
        else
        {
            req_method = r_all;
            r_all = r_line.substr(r_line.find(' ') + 1,r_line.length());
        }
        r_all = r_all.substr(0,r_all.find(' '));
        if(r_all.at(0) == '/')
        {
            if(r_all.find("?") != std::string::npos)
            {
                req_path = r_all.substr(0,r_all.find('?'));
                req_query = r_all.substr(r_all.find('?') + 1);
            }
            else
                req_path = r_all;
            r_all = r_line.substr(r_all.find(' ') + 1,r_line.find('\r'));
        }
        else
            return ResponseIUtils::BAD_REQUEST;
        r_all = r_all.substr(r_all.find(' ') + 1,req.find("\r\n"));
        r_all = r_all.substr(r_all.find(' ') + 1,req.find("\r\n"));
        if(r_all == "HTTP/1.1")
            req_version = r_all;
        else
            return HTTP_VERSOIN_NOT_SUPPORTED;
    }
    req = req.substr(req.find("\r\n") + 2,req.length());
    return 0;
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

std::map<std::string, std::string> request::getHeaders()
{
    return req_headers;
}

std::string request::getReqMethod()
{
    return this->req_method;
}

std::string request::getReqQuery()
{
    return this->req_query;
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

    if((found = port.find_first_of(":")) != std::string::npos)
        port = port.substr(found + 1);
	return "3000";
}

std::string request::getReqHost()
{
    std::string host = getHeaderValue("Host");
    std::size_t found;

    if((found = host.find_first_of(":")) != std::string::npos)
        host = host.substr(0, found);
	return host;
}

void        request::ClearRequest()
{
    req = "";
    req_method = "";
    req_path = "";
    req_version = "";
    req_body = "";
    req_query = "";
    status = 0;
    req_headers.clear();
    error = 0;
}