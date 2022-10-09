/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:44:47 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/10/09 12:37:26 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parsing/parsing.hpp"

int main() {
	parsing		obj;
	Iter		begin;

	// obj.parseArray("[   GET   ,    POST   ,   DELETE    ]   ;");
	std::string text = obj.readFile("./config.conf");
	obj.parseFile(text, 0);
	for (int i = 0 ;i < obj.data.size(); i++)
	{
		begin = obj.data[i].begin();
		if (begin == obj.data[i].end())
			puts("hi");
		while (begin != obj.data[i].end())
		{
			std::cout << "key : " << begin->first << " => "<< "value : " << begin->second << std::endl;
			begin++;
		}
	}

}

