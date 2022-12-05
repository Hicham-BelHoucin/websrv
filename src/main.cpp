/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:57:05 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/12/05 15:22:03 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "webServ.hpp"
#include "request.hpp"

int main(int argc, char const *argv[])
{
	(void)argc;
	if (argv[1] && (checkExtansion(argv[1]) == -1))
	{
		std::cerr << "Bad extansion !!!" << std::endl;
		return EXIT_FAILURE;
	}
	else if (!argv[1])
		argv[1] = CONFIGFILE;
	try
	{
		webserv	_server(argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return 0;
}