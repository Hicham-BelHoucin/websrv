/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:29:53 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/11/19 14:43:02 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H


#include <iostream>
#include "common.h"
#include "createSocket.hpp"
#include "parsing.hpp"
#include "server.hpp"
#include "ResponseUtils.h"

bool isNumber(const std::string& s);
int line_countword(std::string line);
std::string generateErrorPage(int number, std::string description);
std::string&                stringtrim(std::string &str);
bool                        isMatch(String pattern, String str);
void			            printLogs(const std::string & line);
int				            checkExtansion(String filename);
pollfd			            *getfds(std::vector<createSocket> & sockets);
int 		            	getsocket(std::vector<createSocket> sockets, int fd);
std::string                 _displayTimestamp( void );
ResponseIUtils::PATHMODE    checkPathMode(std::string path);
String                      checkExtension(String filename);
String                      dirListing(String dirname);
String                      getDate();
std::string&    			stringtrim(std::string &str);
void						printLogs(const std::string & line);
int							checkExtansion(String filename);
pollfd						*getfds(std::vector<createSocket> & sockets);
int 						getsocket(std::vector<createSocket> sockets, int fd);
std::string					_displayTimestamp( void );
void 						check(int condition);
server selectServer(std::vector<server> servers, std::string host, std::string port);

#endif // !UTILS_H
