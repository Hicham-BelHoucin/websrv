/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 09:19:00 by obeaj             #+#    #+#             */
/*   Updated: 2022/10/31 17:40:14 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

#include "common.h"
#include "server.hpp"
#include "parsing.hpp"

std::string&    stringtrim(std::string &str);
void			printLogs(const std::string & line);
std::vector<int>	getallPorts(Data data, parsing obj);
std::vector<server> createServers(Data data, parsing obj);
int	checkExtansion(String filename);

#endif // !UTILS_H
