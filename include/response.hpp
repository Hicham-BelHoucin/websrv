/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:45:43 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/19 16:36:31 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP
# include "ResponseUtils.h"
# include "common.h"
# include "request.hpp"
# include "parsing.hpp"
# include "cgi.hpp"
class request;

class response
{
private:
    request __req;
    std::string _response;
    std::string _body;
    std::size_t _ContentLenght;
    std::string _reqMethod;
    server      _serv;
    String      _rootpath;
    Set         _ServerLocations;
    LocationMap _location;
    std::string _path;
    std::map<int,std::string> statusPhrases;
    ResponseIUtils::METHODS method;
    ResponseIUtils::CODES _status_code;
    bool isCgiBody;
    parsing conf;
    Map headers;
public:
    response();
    ~response();
    response(request _req, parsing _conf);
    void        setHeaders(request req);
    void        ResponseBuilder();
    void        ClearResponse();
    String      MethodGet(LocationMap location, String path, String body);
    String      MethodPost(LocationMap location, String path, String body);
    String      MethodPut(LocationMap location, String path, String body);
    String      MethodDelete(LocationMap location, String path, String body);
    String      MethodNotAllowed(LocationMap location, String path, String body);
    String      writeContent(String path, String body);
    server      selectServer(std::vector<server> servers, std::string host, std::string port);
    LocationMap locationMatch(Set locations, String path);
    String      MethodCheck(LocationMap location, String method, String path, String body);
    void        checkAndAppend(Map &map, String &str, String key);
};

#endif // !RESPONSE_HPP