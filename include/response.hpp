/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:45:43 by obeaj             #+#    #+#             */
/*   Updated: 2022/10/29 13:28:50 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP
# include "ResponseUtils.h"
# include "common.h"
# include "request.hpp"

class request;

class response
{
private:
    request req;
    ResponseIUtils::METHODS method;
    std::string body;
    Map headers;
public:
    response(/* args */);
    ~response();
};

response::response(/* args */)
{
}

response::~response()
{
}

#endif // !RESPONSE_HPP