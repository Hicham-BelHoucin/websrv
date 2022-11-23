/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:54:00 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/23 17:40:55 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP
#include "utils.h"

#define hh "\e[1;35m"
class request
{
    private:
        std::string 						req;
        std::string 						req_method;
        std::string 						req_path;
        std::string 						req_version;
        std::string 						req_body;
        std::string 						req_query;
        CODES                                 status;
        std::map<std::string, std::string> 	req_headers;
        int									error;
        std::vector<server>                 servers;
    public:
        request(std::string _req);
        request();
        request(const request & obj);
        request & operator=(const request & obj);
        ~request();
        CODES           parseHeaders();
        CODES           requestCheck(std::string _req);
        void            requestPrint();
        CODES           parseReqMethods();
        void            parseReqBody(std::string reqbody);
        std::string     getHeaderValue(std::string key);
        std::string     getReqMethod();
        std::string     getReqVersion();
        std::string     getReqPath();
        std::string     getReqBody();
        std::string     getReqPort();
        std::string     getReqHost();
        std::map<std::string, std::string> getHeaders();
        std::string     getReqQuery();
        CODES           getReqStatus();
        void            ClearRequest();
        void            setservers(const std::vector<server> & obj) {servers = obj;};
};
#endif