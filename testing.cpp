/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:44:47 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/10/21 18:55:10 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.hpp"
#include "include/request.hpp"

void	print(Map data, Set locations)
{
	std::map<std::string, LMap>::iterator begin;
	std::map<std::string, Methods>::iterator	start;
	std::map<std::string, std::string>::iterator	it;

	std::cout << "********************************" << std::endl;
	for (int i = 0 ;i < data.size(); i++)
	{
		it = data.begin();
		while (it != data.end())
		{
			std::cout << it->first << " == "<< it->second << std::endl;
			it++;
		}
	}
	std::cout << "********************************" << std::endl;
	begin = locations.begin();
	while (begin != locations.end())
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

int main() {

try
{
	parsing		obj("./conf/config.conf");
	AllData temp = obj.getAllData();
	/* code */

	AllData::iterator	begin;

	// begin = temp.begin();
	// while (begin != temp.end())
	// {
	// 	std::cout << begin->first << std::endl;
	// 	print(begin->second.data, begin->second.locations);
	// 	// std::cout << "********************************//////////////////////////////////" << std::endl;
	// 	begin++;
	// }

}
catch(const std::exception& e)
{
	std::cerr << e.what() << '\n';
	exit(0);
}
}

