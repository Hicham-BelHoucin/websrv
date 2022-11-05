/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 09:19:00 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/05 12:28:07 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H


#include <iostream>
#include "common.h"
#include "createSocket.hpp"
#include "parsing.hpp"
#include "server.hpp"

std::string&    stringtrim(std::string &str);
void			printLogs(const std::string & line);
int				checkExtansion(String filename);
pollfd			*getfds(std::vector<createSocket> & sockets);
int 			getsocket(std::vector<createSocket> sockets, int fd);

#endif // !UTILS_H
