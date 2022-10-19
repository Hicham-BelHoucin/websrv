/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:53:39 by obeaj             #+#    #+#             */
/*   Updated: 2022/10/19 12:38:17 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "request.hpp"

request::request(std::string _req)
{
    std::stringstream reqstream(_req);
    std::string line_0;
    std::string line;
    std::getline(reqstream, line_0, '\n');
    
    while (std::getline(reqstream, line, '\n'))
    {
        parseReqLine(line);
    }
}
request::~request()
{
    
}
void request::parseReqLine(std::string line)
{
    
}
void request::parseReqMethods(std::string line)
{
    
}