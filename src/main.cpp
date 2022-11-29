/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:57:05 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/11/29 13:05:26 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "webServ.hpp"
#include "request.hpp"

int main(int argc, char const *argv[])
{
	if (argv[1] && (checkExtansion(argv[1]) == -1))
		return EXIT_FAILURE;
	else if (!argv[1])
		argv[1] = CONFIGFILE;
	webserv	_server(argv[1]);
	return 0;
}