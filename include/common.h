/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:06:51 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/10/25 13:11:04 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
#define COMMON_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <cstring>
#include <fstream>
#include <sstream>

typedef enum s_type
{
	NONE = 0,
	KEYWORD,
	PAIR,
	LOCATION,
	OPENCURLYBRACKET,
	CLOSECURLYBRACKET,
	OPENSQUAREBRACKET,
	CLOSESQUAREBRACKET,
	SEMICOLONE,
	COMMENT,
} t_type;


#define	UPPERCASE ABCDEFGHIJKLMNOPQRSTUVWXYZ
#define	SPECIAL	  "{}[];,"
#define	LOWERCASE abcdefghijklmnopqrstuvwxyz
#define	WHITESPACES " \t\n\v\f\r"

typedef	std::vector <std::string >								Methods;
typedef std::pair<std::string, std::string>						Pair;
typedef	std::multimap<std::string , std::string>				Map;
typedef	std::map<std::string , Methods>							LMap;
typedef std::map<std::string, LMap>								Set;
typedef	std::map<std::string , std::string >::iterator			Iter;

typedef	struct s_data
{
	Map 			data;
	Set				locations;
} t_data;

typedef std::multimap<std::string, t_data>								AllData;

#endif // COMMON_H