/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:52:26 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/10/09 12:36:39 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_HPP
#define PARSING_HPP

typedef enum s_type
{
	WORD = 1,
	PAIR,
} t_type;

#include <iostream>
#include <vector>
#include <map>
#include <cstring>
# include <fstream>
#define	UPPERCASE ABCDEFGHIJKLMNOPQRSTUVWXYZ
#define	SPECIAL	  "{}[];,"
#define	LOWERCASE abcdefghijklmnopqrstuvwxyz
#define	WHITESPACES " \t\n\v\f\r"

typedef	std::vector<std::map<std::string, std::string> >	Data;
typedef std::pair<std::string, std::string>					Pair;
typedef	std::map<std::string , std::string >				Map;
typedef	std::map<std::string , std::string >::iterator		Iter;

class parsing
{
	public:
		Data 	data;
		Map		info;
	public:
		void		checkMethods(std::vector<std::string>  & methods);
		void		skip(const std::string & line, int & index);
		void		parseArray(const std::string &  line);
		void		parseFile(std::string text, int start);
		Pair		parseLine(std::string line);
		void		skipWhiteSpaces(const std::string &  line, int & index);
		std::string	readFile(std::string filename);
		parsing();
		~parsing();
};


#endif //PARSING_HPP