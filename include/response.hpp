/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:45:43 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/01 03:52:47 by obeaj            ###   ########.fr       */
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
    ResponseIUtils::METHODS method;
    ResponseIUtils::CODES _status_code;
    parsing conf;
    Map headers;
public:
    response();
    ~response();
    response(request &_req, parsing &_conf);
    void setHeaders();
    void setBody();
    void setStatusCode();
    void ResponseBuilder();
    void ClearResponse();
    

};

#endif // !RESPONSE_HPP