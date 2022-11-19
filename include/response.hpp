/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:45:43 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/15 19:57:58 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP
// # include "ResponseUtils.h"
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
    // ResponseIUtils::METHODS method;
    // ResponseIUtils::CODES _status_code;
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