/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:54:00 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/28 18:25:11 by obeaj            ###   ########.fr       */
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
        std::string 						boundry;
        int                                 status;
        std::map<std::string, std::string> 	req_headers;
        Map 	                            body_con;
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
        int         getReqStatus();
        void        parseReqBody();
        std::string getHeaderValue(std::string key);
        std::string getReqMethod();
        std::string getReqVersion();
        std::string getReqPath();
        std::string getReqBody();
        std::string getReqPort();
        std::string getReqHost();
        std::map<std::string, std::string> getHeaders();
        std::string getReqQuery();
        Map         getFilesBody();
        void        ClearRequest();
        void        setservers(const std::vector<server> & obj) {servers = obj;};
};
#endif