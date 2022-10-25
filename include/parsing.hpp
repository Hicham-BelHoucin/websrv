/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:52:26 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/10/25 15:10:52 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_HPP
#define PARSING_HPP

#include "shortcuts.h"

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


typedef	struct s_data
{
	Map 			data;
	Set				locations;
} t_data;

typedef std::multimap<std::string, t_data>								AllData;

class parsing
{
	private:
		AllData			allData;
		Map				info;
		LMap			locationsInfo;
		Set				locations;
		unsigned int	_size;
	public:
		class Usage : public std::exception
        {
            const char * what() const throw ();
        };
		class UnclosedBrakets : public std::exception
        {
            const char * what() const throw ();
        };
		class Nosemicolon : public std::exception
        {
            const char * what() const throw ();
        };
		class Extrasemicolon : public std::exception
        {
            const char * what() const throw ();
        };
		class Nobarcket : public std::exception
        {
            const char * what() const throw ();
        };
		AllData		getAllData(void) const;
		void		checkMethodsKeyWords(LMap locations);
		void		checkKeyWords(void);
		void		checkBrackets(std::string text);
		int			checkPath(std::string text);
		void		checkMethods(std::vector<std::string>  & methods);
		void		skip(const std::string & line, int & index);
		std::vector <std::string >		parseArray(const std::string &  line);
		void		parseFile(std::string text, int start);
		void		parseLocation(std::string text, int start);
		Pair		parseLine(std::string line);
		void        checkSemicolon(std::string text);
		int			countSize(std::string text);
		int			getTokenType(std::string line);
		void		skipWhiteSpaces(const std::string &  line, int & index);
		std::string	readFile(std::string filename);
		parsing(std::string filename);
		~parsing();
};


#endif //PARSING_HPP