/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
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
# include <dirent.h>
# include <algorithm>

# define ERROR404 "./src/errors/error_404.html"
# define ERROR403 "./src/errors/error_403.html"
# define ERROR405 "./src/errors/error_405.html"
# define ERROR500 "./src/errors/error_500.html"
# define ERROR502 "./src/errors/error_502.html"
# define CONFIGFILE "./conf/config.conf"
# define CLINETMAXBODYSIZE 1
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