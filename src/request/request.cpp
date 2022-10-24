/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:53:39 by obeaj             #+#    #+#             */
/*   Updated: 2022/10/21 19:32:29 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "request.hpp"

request::request(std::string _req)
{
    std::stringstream reqstream(_req);
    std::string line;
    std::getline(reqstream, line, '\n');
    parseReqMethods(line);
    while (std::getline(reqstream, line, '\n'))
    {
        // parseReqLine(line);
        std::cout << line << "\n";
    }
}
request::~request()
{
}
void request::parseReqLine(std::string line)
{
    std::stringstream str(line);
    std::string key;
    std::vector<std::string> values;
    std::string value;
    std::getline(str, key, ':');
    while(std::getline(str, value, ','))
    {
                std::cout << value << "\n";

        // values.push_back(value);
    }
    
}
void request::parseReqMethods(std::string line)
{
    std::stringstream str(line);
    std::string key;
    std::vector<std::string> values;
    std::string value;
    std::getline(str, key, ' ');
    if (key != "GET" || key != "POST" || key != "DELETE")
    {
        std::cout << "\033[1;31mError : Request method not handled !\033[0m\n";
        error = 2;
        return ;
    }
    while(std::getline(str, value, ' '))
    {
        values.push_back(value);
    }
    req.insert(std::pair<std::string,std::vector<std::string> >(key,values));
    
    // for (std::map<std::string, std::vector<std::string> >::iterator itr =req.begin(); itr !=req.end(); ++itr) {
    //     std::cout << itr->first << ": " ;
    //     for(std::vector<std::string>::iterator i = itr->second.begin(); i != itr->second.end(); ++i )
    //         std::cout << *i << "\t" ;
        
    //     std::cout << "\n" ;
    // }
}