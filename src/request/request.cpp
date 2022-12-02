/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:30:49 by obeaj             #+#    #+#             */
/*   Updated: 2022/12/02 18:48:05 by imabid           ###   ########.fr       */
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
        this->status = obj.status;
        this->body_con = obj.body_con;
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
    int     st = 0;

    req = _req;
    if((st = parseReqMethods()) || (st = parseHeaders()))
    {
        std::cout << "this is s " << st << std::endl;
        status = st;
        return status;
    }
    // requestPrint();
    return 0;
}

request::~request()
{
}

int request::parseHeaders()
{
    std::string     all;
    std::string     key;
    std::string     value;
    int             lt_of_head;
    int             s = 0;

    while ((lt_of_head = req.find("\r\n")) != std::string::npos)
    {
        if(lt_of_head == 0)
        {
            req = req.substr(req.find("\r\n") + 2,req.length());
            break;
        }
        all = req.substr(0, lt_of_head);
        if(all.find(':') == std::string::npos)
        {
            printLogs(_displayTimestamp() + "BAD_REQUEST");
            return BAD_REQUEST;
        }
        key = all.substr(0,all.find(':'));
        value = all.substr(all.find(' ') + 1, all.length());
        req_headers.insert(std::make_pair((key), value));
        if(req_headers.count("Host") > 1  || req_headers.count("Host") < 0)
        {
            printLogs(_displayTimestamp() + "BAD_REQUEST");
            return BAD_REQUEST;
        }
        req = req.substr(req.find("\r\n") + 2,req.length());
    }
    std::map<std::string,std::string>::iterator it;
    std::string port;
    if((it = req_headers.find("Host")) != req_headers.end())
    {
        port = it->second.substr(it->second.find(":") + 1, it->second.length());
        if(!isNumber(port))
        {
            printLogs(_displayTimestamp() + "BAD_REQUEST");
            return BAD_REQUEST;
        }
    }
    if((it = req_headers.find("Content-Type")) != req_headers.end())
    {
        if(it->second.find("multipart") != std::string::npos && it->second.find("boundary") == std::string::npos)
        {
            printLogs(_displayTimestamp() + "BAD_REQUEST");
            return BAD_REQUEST;
        }
        boundry = it->second.substr(it->second.find("=") + 1, it->second.find("\r\n"));
    }
    if((it = req_headers.find("Content-Length") )!= req_headers.end())
    {
        server obj;

        obj = selectServer(servers, getReqHost(), getReqPort());
        if(!isNumber(it->second))
        {
            printLogs(_displayTimestamp() + "BAD_REQUEST");
            return BAD_REQUEST;
        }
        if(std::stoi(it->second) > obj.getMaxBodySize())
        {
            printLogs(_displayTimestamp() + "LARGE_PAYLOAD");
            return LARGE_PAYLOAD;
        }
    }
    if(!req.empty())
    {
        req_body = req;
        if((it = req_headers.find("Content-Type")) != req_headers.end() && it->second.find("multipart") != std::string::npos)
        {
            if((s = parseReqBody()))
                return s;
        }
    }
    return 0;
}

int       request::parseReqBody()
{
    std::string     content;
    std::string     key;
    std::string     value;
    std::string     newreq;
    std::string     bound;
    int             bound_pos;
    int             content_pos;
    int             con_last_pos;
    int             bound_len;
    int             last_bound;
    
    newreq = req;
    bound = "--" + boundry;
    if((last_bound = newreq.find(bound + "--")) == std::string::npos)
    {
        printLogs(_displayTimestamp() + "BAD_REQUEST");
        return BAD_REQUEST;
    }
    newreq = newreq.substr(newreq.find(bound) + bound.length() + 2,last_bound + bound.length() + 2);
    bound_len = bound.length() + 2;
    for(int j = 0 ; bound_len < newreq.length() ; j++)
    {
        bound_pos = newreq.find(bound);
        content = newreq.substr(0,bound_pos);
        newreq = newreq.substr(bound_pos + bound.length() + 2, newreq.length());
        if(content.find("filename=\"") != std::string::npos)
        {
            key = content.erase(0,content.find("filename=\"") + 10);
            key = key.substr(0,key.find("\""));
            content_pos = content.find("\r\n\r\n") + 4;
            con_last_pos = content.length() - 2;
            while (content_pos < con_last_pos)
                value += content[content_pos++];
            body_con.insert(std::make_pair(key, value));
            key.clear();
            value.clear();
        }
    }
    return 0;
}

int request::parseReqMethods()
{
    std::string     r_line;
    std::string     r_all;
    int             f_line;

    f_line = req.find("\r\n");
    if(f_line != std::string::npos)
    {
        r_line = req.substr(0,req.find("\n"));
        r_all = r_line.substr(0,r_line.find(' '));
        if(r_all != "GET" && r_all != "PUT" && r_all != "DELETE" && r_all != "POST")
        {
            printLogs(_displayTimestamp() + "NOT_IMPLEMENTED");
            return NOT_IMPLEMENTED;
        }
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
        {
            printLogs(_displayTimestamp() + "BAD_REQUEST");
            return BAD_REQUEST;
        }
        r_all = r_all.substr(r_all.find(' ') + 1,req.find("\r\n"));
        r_all = r_all.substr(r_all.find(' ') + 1,req.find("\r\n"));
        if(r_all == "HTTP/1.1")
            req_version = r_all;
        else
        {
            printLogs(_displayTimestamp() + "NON_SUPPORTED_HTTPVERSION");
            return NON_SUPPORTED_HTTPVERSION;
        }
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

Map request::getFilesBody()
{
    return body_con;
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

int request::getReqStatus()
{
    return status;
}