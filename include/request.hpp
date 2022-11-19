/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:54:00 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/18 22:03:27 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP
#include "utils.h"

//  Informational 1xx
#define CONTINUE 100
#define SWITCHING_PROTOCOL 101

// Successful 2xx
#define OK 200
#define CREATED 201
#define ACCEPTED 202
#define NON_AUTHORITATIVE 203
#define NO_CONTENT 204
#define RESET_CONTENT 205
#define PARTIAL_CONTENT 206

// Redirection 3xx
#define MULTIPLE_CHOICES 300
#define MOVED_PERMANENTLY 301
#define FOUND 302
#define SEE_OTHER 303
#define NOT_MODIFIED 304
#define USE_PROXY 305

// Client Error 4xx
#define BAD_REQUEST 400
#define UNAUTHORIZED 401
#define PAYMENT_REQUIRED 402
#define FORBIDEN 403
#define NOT_FOUND 404
#define METHOD_NOT_ALLOWED 405
#define NOT_ACCEPTABLE 406
#define PROXY_AUTHENTCATION_REQUIRED 407
#define REQUEST_TIMEOUT 408
#define CONFLICT 409
#define GONE 410
#define LENGTH_REQUIRED 411
#define PRECONDITION_FAILED 412
#define REQUEST_ENTITY_TOO_LARGE 413
#define REQUEST_URI_TOO_LONG 414
#define UNSUPPORTED_MEDIA_TYPE 415
#define REQUEST_RANGE_NOT_SATISFIABLE 416
#define EXPECTATION_FAILED 417

// Server Error 5xx
#define INTERNAL_SERVER_ERROR 500
#define NOT_IMPLEMENTED 501
#define BAD_GETEWAY 502
#define SERVICE_UNABAILABLE 503
#define GATEWAY_TIMEOUT 504
#define HTTP_VERSOIN_NOT_SUPPORTED 505


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
        std::string getReqQuery();
        void        ClearRequest();
};
#endif