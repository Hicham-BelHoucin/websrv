/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:52:26 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/12/07 16:01:11 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_HPP
#define PARSING_HPP

#include "common.h"
#include "utils.h"
class server;
class parsing
{
	private:
		Data				data;
		Map					info;
		LocationMap			locationsInfo;
		Set					locations;
		unsigned int		_size;
	public:
		class Parseerror : public std::exception
        {
			private:
				const char * error;
			public:
				Parseerror(std::string error) : error(error.c_str()) {};
				const char * what() const throw ();
        };
		Data				getData(void) const;
		std::string 		getHost(Map data) const;
		std::string 		getReturn(Map data) const;
		std::vector<int> 	getPorts(Map data) const;
		Map					getErrorPages(Map data);
		std::string			getServerName(Map data) const;
		int					getMaxBodySize(Map data) const;
		std::string   		trimString(std::string s, std::string rejected = WHITESPACES);
		std::string			getRoot(Map data) const;
		int					checkDuplicatePort(Map data);
		void				checkMethodsKeyWords(LocationMap locations);
		void				checkKeyWords(void);
		void				checkBrackets(std::string text);
		int					checkPath(std::string text);
		void				checkHost(Pair);
		void				checkMethods(std::vector<std::string>  & methods);
		void				skip(const std::string & line, size_t & index);
		int					checkDuplicateKwywords(Map data, std::string[]);
		int					checkMessingElements(Map data, std::string[]);
		std::vector 		<std::string >		parseArray(const std::string &  line);
		void				parseFile(std::string text, size_t start);
		void				parseLocation(std::string text, size_t start);
		Pair				parseLine(std::string line);
		void        		checkSemicolon(std::string text);
		int					countSize(std::string text);
		int					getTokenType(std::string line);
		void				skipWhiteSpaces(const std::string &  line, size_t & index);
		std::string			readFile(std::string filename);
		int					IsSpecialKey(std::string);
		parsing(std::string filename);
		parsing & operator=(const parsing & obj);
		parsing();
		~parsing();
};

std::vector<int>	getallPorts(Data data, parsing obj);
std::vector<createSocket>	createSockets(Data data, parsing obj);
std::vector<server> createServers(Data data, parsing obj);

#endif //PARSING_HPP