/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 16:30:30 by obeaj             #+#    #+#             */
/*   Updated: 2022/12/07 12:09:25 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H


#include "common.h"
#include "createSocket.hpp"
#include "parsing.hpp"
#include "server.hpp"
#include "ResponseUtils.h"

void	printParsingData(Map data, Set locations);
bool isNumber(const std::string& s);
int line_countword(std::string line);
std::string generateErrorPage(int number, std::string description);
std::string&    stringtrim(std::string &str, std::string rejected = WHITESPACES);
bool                        isMatch(String pattern, String str);
void			            printLogs(const std::string & line);
int				            checkExtansion(String filename);
pollfd			            *getfds(std::vector<createSocket> & sockets);
int 		            	getsocket(std::vector<createSocket> sockets, int fd);
std::string                 _displayTimestamp( void );
PATHMODE                    checkPathMode(std::string path);
String                      checkExtension(String filename);
// String                      dirListing(String dirname);
String                      getDate();
String                      HtmlCompose(String htmlbody, String htmltitle);
server                      selectServer(std::vector<server> servers, std::string host, std::string port);

void		            	printLogs(const std::string & line);
int	            			checkExtansion(String filename);
pollfd			            *getfds(std::vector<createSocket> & sockets);
int 			            getsocket(std::vector<createSocket> sockets, int fd);
std::string		            _displayTimestamp( void );
std::map<int, std::string>  setStatusPhrases();
void                        check(int condition);
String                      getContentType(String path, CODES status);
int			hexToDecimal(std::string str);
std::vector<std::string> split(std::string text, std::string del);
int			AppendHeaders(std::string req, std::string & body);
int		IsHexa(std::string str);
String upperCase(String str);
int			                hexToDecimal(std::string str);
std::vector<std::string>    split(std::string text, std::string del);
int			                AppendHeaders(std::string req, std::string & body);
int		                    IsHexa(std::string str);
String                      upperCase(String str);
String                      getErrorPage(server serv, CODES status);

#endif
