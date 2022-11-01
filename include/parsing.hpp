/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:52:26 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/11/01 03:08:45 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_HPP
#define PARSING_HPP

#include "common.h"
#include "utils.h"
class parsing
{
	private:
		Data			data;
		Map				info;
		LocationMap		locationsInfo;
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
		Data		getData(void) const;
		int			checkDuplicatePort(Map data);
		void		checkMethodsKeyWords(LocationMap locations);
		void		checkKeyWords(void);
		void		checkBrackets(std::string text);
		int			checkPath(std::string text);
		void		checkHost(Pair);
		void		checkMethods(std::vector<std::string>  & methods);
		void		skip(const std::string & line, int & index);
		int			checkDuplicateKwywords(Map data, std::string[]);
		int			checkMessingElements(Map data, std::string[]);
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
		parsing();
		~parsing();
};


#endif //PARSING_HPP