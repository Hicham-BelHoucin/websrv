/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:54:00 by obeaj             #+#    #+#             */
/*   Updated: 2022/10/26 14:41:33 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP
#include "utils.h"

class request
{
    private:
        std::string req_method;
        std::string req_path;
        std::string req_version;
        std::string req_body;
        std::map<std::string, std::string> req_headers;
        int error;
    public:
        request(std::string _req);
        ~request();
        void        parseReqLine(std::string line);
        void        parseReqMethods(std::string line);
        void        parseReqBody(std::string reqbody);
        std::string getHeaderValue(std::string &key);
        std::string getReqMethod();    
        std::string getReqVersion();
        std::string getReqPath();
        std::string getReqBody();
};
#endif