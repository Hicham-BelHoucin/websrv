/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:44:47 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/10/10 15:29:24 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parsing/parsing.hpp"

void	print(Data data, Set locations)
{
	std::map<std::string, LMap>::iterator begin;
	std::map<std::string, Methods>::iterator	start;
	std::map<std::string, std::string>::iterator	it;

	std::cout << "********************************" << std::endl;
	for (int i = 0 ;i < data.size(); i++)
	{
		it = data[i].begin();
		while (it != data[i].end())
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
	parsing		obj("./config.conf");
	AllData temp = obj.getAllData();
	/* code */

	AllData::iterator	begin;

	begin = temp.begin();
	while (begin != temp.end())
	{
		std::cout << begin->first << std::endl;
		print(begin->second.data, begin->second.locations);
		// std::cout << "********************************//////////////////////////////////" << std::endl;
		begin++;
	}

}
catch(const std::exception& e)
{
	std::cerr << e.what() << '\n';
	exit(0);
}
}

