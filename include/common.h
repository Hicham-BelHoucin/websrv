/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:06:51 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/11/03 15:58:57 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
#define COMMON_H

# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <iostream>
# include <unistd.h>
# include <iostream>
# include <vector>
# include <map>
# include <set>
# include <stack>
# include <cstring>
# include <fstream>
# include <ostream>
# include <sstream>
# include <poll.h>

# define ERROR404 "/Users/obeaj/websrv/src/error/error_404.html"
# define ERROR403 "/Users/obeaj/websrv/src/error/error_403.html"
# define ERROR500 "/Users/obeaj/websrv/src/error/error_500.html"
# define ERROR502 "/Users/obeaj/websrv/src/error/error_502.html"
# define CONFIGFILE "/Users/obeaj/websrv/conf/config.conf"
# define CLINETMAXBODYSIZE 1
# define SEVRERNAME "exmaple.com"

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


#define	UPPERCASE "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define	SPECIAL	  "{}[];,"
#define	LOWERCASE "abcdefghijklmnopqrstuvwxyz"
#define	WHITESPACES " \t\n\v\f\r"

typedef	std::vector <std::string >								Methods;
typedef std::pair<std::string, std::string>						Pair;
typedef	std::multimap<std::string , std::string>				Map;
typedef	std::map<std::string , Methods>							LocationMap;
typedef std::map<std::string, LocationMap>						Set;
typedef	std::string												String;

typedef	struct s_data
{
	Map 			data;
	Set				locations;
} t_data;

typedef	std::vector<t_data>													Data;
std::string		readFile(std::string filename);

#endif // COMMON_H