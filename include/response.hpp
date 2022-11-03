/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:45:43 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/03 19:56:32 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP
# include "ResponseUtils.h"
# include "common.h"
# include "request.hpp"
# include "parsing.hpp"

class request;

class response
{
private:
    std::string _response;
    std::string _body;
    std::size_t _ContentLenght;
    request req;
    std::string _path;
    ResponseIUtils::METHODS method;
    ResponseIUtils::CODES _status_code;
    parsing conf;
    Map headers;
public:
    response();
    ~response();
    response(request _req, parsing _conf);
    void        setHeaders(Pair header);
    void        setBody();
    void        setStatusCode();
    void        ResponseBuilder();
    void        ClearResponse();
    server      selectServer(std::vector<server> servers, std::string host, std::string port);
    LocationMap locationMatch(Set locations, String path);
};

#endif // !RESPONSE_HPP