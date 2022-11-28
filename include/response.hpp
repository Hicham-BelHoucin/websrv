/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:45:43 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/28 19:16:08 by obeaj            ###   ########.fr       */
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
    parsing __conf;
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
    Map         _upload;
    METHODS method;
    CODES _status_code;
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
    String      handleUpload(LocationMap location);
    // server      selectServer(std::vector<server> servers, std::string host, std::string port);
    LocationMap locationMatch(Set locations, String path);
    String      MethodCheck(LocationMap location, String method, String path, String body);
    void        checkAndAppend(Map &map, String &str, String key);
    String      getResponse();
    String      dirListing(String dirname);
    String      getCgiBody(String cgi_body);
};

#endif // !RESPONSE_HPP