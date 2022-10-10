/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:52:26 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/10/10 13:04:32 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_HPP
#define PARSING_HPP

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

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstring>
# include <fstream>
#define	UPPERCASE ABCDEFGHIJKLMNOPQRSTUVWXYZ
#define	SPECIAL	  "{}[];,"
#define	LOWERCASE abcdefghijklmnopqrstuvwxyz
#define	WHITESPACES " \t\n\v\f\r"

typedef	std::vector<std::multimap<std::string, std::string> >		Data;
typedef	std::vector <std::string >								Methods;
typedef std::pair<std::string, std::string>						Pair;
typedef	std::multimap<std::string , std::string>						Map;
typedef	std::map<std::string , Methods>							LMap;
typedef std::map<std::string, LMap>								Set;
typedef	std::map<std::string , std::string >::iterator			Iter;

typedef	struct s_data
{
	Data 			data;
	Set				locations;
} t_data;

typedef std::multimap<std::string, t_data>								AllData;

class parsing
{
	private:
		AllData			allData;
		Data 			data;
		Map				info;
		LMap			locationsInfo;
		Set				locations;
		unsigned int	_size;
	public:
		class Usage : public std::exception
        {
            const char * what() const throw ();
        };
		AllData		getAllData(void) const;
		void		checkMethods(std::vector<std::string>  & methods);
		void		skip(const std::string & line, int & index);
		std::vector <std::string >		parseArray(const std::string &  line);
		void		parseFile(std::string text, int start);
		void		parseLocation(std::string text, int start);
		Pair		parseLine(std::string line);
		int			countSize(std::string text);
		int			getTokenType(std::string line);
		void		skipWhiteSpaces(const std::string &  line, int & index);
		std::string	readFile(std::string filename);
		parsing(std::string filename);
		~parsing();
};


#endif //PARSING_HPP