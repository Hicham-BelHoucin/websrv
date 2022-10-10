/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:44:47 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/10/09 15:46:39 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parsing/parsing.hpp"

int main() {
	parsing		obj("./config.conf");
	std::map<std::string, LMap>::iterator begin;
	std::map<std::string , Methods>::iterator	start;
	std::map<std::string , std::string>::iterator	it;

	std::cout << "********************************" << std::endl;
	for (int i = 0 ;i < obj.data.size(); i++)
	{
		it = obj.data[i].begin();
		while (it != obj.data[i].end())
		{
			std::cout << it->first << " == "<< it->second << std::endl;
			it++;
		}
	}
	std::cout << "********************************" << std::endl;
	begin = obj.locations.begin();
	while (begin != obj.locations.end())
	{
		std::cout << begin->first << std::endl;
		start = begin->second.begin();
		while (start != begin->second.end())
		{
			std::cout << "	" << start->first << " : " << std::endl;
			for (int i = 0; i < start->second.size() ; i++)
				std::cout << "			" << start->second[i] << std::endl;
			start ++;
		}
		begin++;
	}
}

