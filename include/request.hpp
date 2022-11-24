/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:54:00 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/20 13:40:22 by imabid           ###   ########.fr       */
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
        int                                 status;
        std::map<std::string, std::string> 	req_headers;
        int									error;
        std::vector<server>                 servers;
    public:
        request(std::string _req);
        request();
        request(const request & obj);
        request & operator=(const request & obj);
        ~request();
        int         parseHeaders();
        int         requestCheck(std::string _req);
        void        requestPrint();
        int         parseReqMethods();
        void        parseReqBody(std::string reqbody);
        std::string getHeaderValue(std::string key);
        std::string getReqMethod();
        std::string getReqVersion();
        std::string getReqPath();
        std::string getReqBody();
        std::string getReqPort();
        std::string getReqHost();
        std::map<std::string, std::string> getHeaders();
        std::string getReqQuery();
        void        ClearRequest();
        void        setservers(const std::vector<server> & obj) {servers = obj;};
};
#endif