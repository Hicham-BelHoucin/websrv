/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:17:03 by obeaj             #+#    #+#             */
/*   Updated: 2022/12/07 15:50:28 by hbel-hou         ###   ########.fr       */
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
# include <fcntl.h>
# include <poll.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <climits>
# include <algorithm>

# define CONFIGFILE "./conf/config.conf"
# define NOTFOUND std::string::npos

# define CGI_BUFSIZE 1024
// Colors
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define RESET "\033[0m"

# define CLINETMAXBODYSIZE 2147483647
# define SEVRERNAME "exmaple.com"

# define print(msg)                            \
    {                                          \
        std::cout << msg << std::endl;         \
    }


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
typedef std::vector<std::string>::iterator                   	VecIterator;

typedef	struct s_data
{
	Map 			data;
	Set				locations;
} t_data;

typedef	std::vector<t_data>													Data;
std::string		readFile(std::string filename);

#endif // COMMON_H