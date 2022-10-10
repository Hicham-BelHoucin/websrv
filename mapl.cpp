/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 07:26:01 by imabid            #+#    #+#             */
/*   Updated: 2022/10/10 10:10:13 by imabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>

int main()
{
    std::multimap<std::string, std::string> map;
    // {
    //    std::make_pair("hhhhh","aaaaaa"),
    //    std::make_pair("hello","world"),
    //    std::make_pair("yoyo","yaya"),
    //    std::make_pair("haha","hoho"),
    // };
    map.insert(std::make_pair("imad","abid"));
    map.insert(std::make_pair("hello","aaaaaa"));
    map.insert(std::make_pair("imad","aaaaaa"));
    // std::cout << map.at("hhhhh");
    std::cout << map.count("hhhhh") << std::endl; 
    std::map<std::string, std::string>::iterator it = map.begin();
    it = map.find("imad");
    it++;
    it->second = "waaaa";
    
    for(std::map<std::string, std::string>::iterator it = map.begin() ; it != map.end(); it++)
        std::cout << it->first << " " << it->second << std::endl;
    // std::cout << map.max_size() << std::endl;
    std::cout << map.size() << std::endl;
    //  map.clear();
    // for(std::map<std::string, std::string>::iterator it = map.begin() ; it != map.end(); it++)
    //     std::cout << it->first << " " << it->second << std::endl;
    
}
