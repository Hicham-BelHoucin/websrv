/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:30:49 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/30 14:39:02 by hbel-hou         ###   ########.fr       */
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
    req = _req;
    int st = 0;
    if((st = parseReqMethods()) || (st = parseHeaders()))
    {
        std::cout << st << " \n";
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
            return BAD_REQUEST;
        key = all.substr(0,all.find(':'));
        value = all.substr(all.find(' ') + 1, all.length());
        req_headers.insert(std::make_pair((key), value));
        if(req_headers.count("Host") > 1  || req_headers.count("Host") < 0)
            return BAD_REQUEST;
        req = req.substr(req.find("\r\n") + 2,req.length());
    }
    std::map<std::string,std::string>::iterator it;
    std::string port;
    if((it = req_headers.find("Host")) != req_headers.end())
    {
        port = it->second.substr(it->second.find(":") + 1, it->second.length());
        if(!isNumber(port))
            return BAD_REQUEST;
    }
    if((it = req_headers.find("Content-Type")) != req_headers.end())
    {
        if(it->second.find("multipart") != std::string::npos && it->second.find("boundary") == std::string::npos)
            return BAD_REQUEST;
        boundry = it->second.substr(it->second.find("=") + 1, it->second.find("\r\n"));
    }
    // if((it = req_headers.find("Content-Length") )!= req_headers.end())
    // {
    //     server obj;

    //     obj = selectServer(servers, getReqHost(), getReqPort());
    //     if(!isNumber(it->second))
    //     {
    //         return BAD_REQUEST;
    //     }
    //     if(std::stoi(it->second) > obj.getMaxBodySize())
    //         return LARGE_PAYLOAD;
    // }
    int s = 0;
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
    std::string bd;
    int f_of_ct;
    // int f;
    std::string key;
    std::string value;
    std::string b;
    std::string newreq;
    std::string c;
    int f;
    newreq = req;
    std::string bound = "--" + boundry;
    int last_bound;
    if((last_bound = newreq.find(bound + "--")) == std::string::npos)
        return BAD_REQUEST;
    // newreq = newreq.substr(newreq.find(bound) + bound.length() + 2,newreq.length());
    newreq = newreq.substr(newreq.find(bound) + bound.length() + 2,last_bound + bound.length() + 2);
    // newreq = newreq.substr(0, last_bound + bound.length() + 2);
    int q = bound.length() + 2;
    // int v = newreq.find(bound);
    // bd = newreq.substr(0,v);
    // std::cout << "hi " << bd <<  std::endl;
    // std::cout << "hi " << v <<std::endl;
    // int f = newreq.find(bound);
    // newreq = newreq.substr(0,f);
    for(int j = 0 ; q < newreq.length() ; j++)
    {
        // if(newreq.find(bound) != std::string::npos)
            f = newreq.find(bound);
        // else if(newreq.find(bound + "--") != std::string::npos)
        //     f = newreq.find(bound + "--");
        // int z = newreq.find(bound,q);
        // else if(newreq.find(bound + "--") != std::string::npos)
        //     f = newreq.find(bound,bound.length() + 4);
        bd = newreq.substr(0,f);
        newreq = newreq.substr(f+ bound.length() + 2,newreq.length());
        int l;

        if(bd.find("filename=\"") != std::string::npos)
        {
            key = bd.erase(0,bd.find("filename=\"") + 10);
            key = key.substr(0,key.find("\""));
            l = bd.find("\r\n\r\n") + 4;
            // std::cout << "this is bd " << bd << std::endl;
            // std::cout << "this is lenght " << bd.length() << std::endl;
            int m = bd.length() - 2;
            while (l < m)
            {
                value += bd[l++];
            }
        body_con.insert(std::make_pair(key, value));
        key.clear();
        value.clear();
        }
        // std::cout << "this is req " <<  newreq << "|" <<std::endl;
        // bd = newreq.substr(q,f - q);
        // std::cout << "this is req " <<  bd << "|" <<std::endl;
        // std::cout << "this is q " << q  << std::endl;
        // if(j > 5)
        //     break;
        // q = f;
        // std::cout << "this is the f " << f <<  "this is q " << q << "this is req " << newreq.length() << std::endl;
    }
    // for(int j = 0 ; newreq.length() != 0 ; j++)
    // {
    //     if(newreq.find(bound) != std::string::npos)
    //         f = newreq.find(bound);
    //     else if(newreq.find(bound + "--") != std::string::npos)
    //         f = newreq.find(bound + "--");
    //     // int z = newreq.find(bound,q);
    //     // else if(newreq.find(bound + "--") != std::string::npos)
    //     //     f = newreq.find(bound,bound.length() + 4);
    //     bd = newreq.substr(0,f);
    //     newreq = newreq.substr(f+ bound.length() + 2,newreq.length());
    //     int l;

    //     if(bd.find("filename=\"") != std::string::npos)
    //     {
    //         key = bd.erase(0,bd.find("filename=\"") + 10);
    //         key = key.substr(0,key.find("\""));
    //         l = bd.find("\r\n\r\n") + 4;
    //         // std::cout << "this is bd " << bd << std::endl;
    //         // std::cout << "this is lenght " << bd.length() << std::endl;
    //         int m = bd.length();
    //         while (l < m)
    //         {
    //             value += bd[l++];
    //         }
    //     body_con.insert(std::make_pair(key, value));
    //     key.clear();
    //     value.clear();
    //     }
    //     // std::cout << "this is req " <<  newreq << "|" <<std::endl;
    //     // bd = newreq.substr(q,f - q);
    //     // std::cout << "this is req " <<  bd << "|" <<std::endl;
    //     // std::cout << "this is q " << q  << std::endl;
    //     // if(j > 5)
    //     //     break;
    //     q = f;
    //     std::cout << "this is the f " << f <<  "this is q " << q << "this is req " << newreq.length() << std::endl;
    // }
    // while (newreq != "--\r\n")
    // {
    //     if(newreq.find(bound)!= std::string::npos)
    //         b = newreq.substr(0,newreq.find(bound));
    //     else
    //         break;
    //     while(b.length())
    //     {
    //         if((f_of_ct = b.find("\n")) != std::string::npos)
    //         {
    //             bd = b.substr(0,f_of_ct);
    //             if(bd.find("Content-Disposition:") != std::string::npos && bd.find("filename") == std::string::npos)
    //                 break;
    //             else if(bd.find("Content-Disposition") != std::string::npos && bd.find("filename") != std::string::npos)
    //             {
    //                 key = bd.erase(0,bd.find("filename=\"") + 10);
    //                 key = key.substr(0,key.find("\""));
    //             }
    //             else if(bd.find("Content-Type") != std::string::npos)
    //                 c = bd.substr(bd.find(":") + 1,bd.length());
    //             else
    //                 value += bd += '\n';
    //         }
    //         b = b.substr(f_of_ct + 1,b.length());
    //     }
    //     if(!key.empty() || !value.empty())
    //         body_con.insert(std::make_pair(key, value));
    //     key.clear();
    //     value.clear();
    //     if((f = newreq.find(bound) + bound.length() + 2) != std::string::npos)
    //         newreq = newreq.substr(newreq.find(bound) + bound.length() + 2,newreq.length());
    // }
    // for(std::map<std::string ,std::string>::iterator it = body_con.begin(); it != body_con.end() ; it++)
	// {
	// 	std::cout << "|\e[1;35m" << it->first << ":\e[1;36m " << it->second <<"|\e[1;33m"<<std::endl;
	// }
    // for(std::map<std::string ,std::string>::iterator it = body_con.begin(); it != body_con.end() ; it++)
	// {
	// 	std::cout << "| " << it->first << " : " << it->second <<" |"<<std::endl;
	// }
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
            return NOT_IMPLEMENTED;
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
            return BAD_REQUEST;
        r_all = r_all.substr(r_all.find(' ') + 1,req.find("\r\n"));
        r_all = r_all.substr(r_all.find(' ') + 1,req.find("\r\n"));
        if(r_all == "HTTP/1.1")
            req_version = r_all;
        else
            return NON_SUPPORTED_HTTPVERSION;
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