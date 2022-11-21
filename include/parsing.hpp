/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:52:26 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/11/20 11:45:39 by obeaj            ###   ########.fr       */
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
		std::string 		getHost(Map data) const {
			return data.find("host")->second;
		};
		std::vector<int> 	getPorts(Map data) const
		{
          	std::vector<int>    					ports;
			std::pair<Map::iterator, Map::iterator>	ret;
			int 									port;

			ret = data.equal_range("listen");
			while (ret.first != ret.second)
			{
				port = std::stoi(ret.first->second);
				ports.push_back(port);
				ret.first ++;
			}
			return ports;
		};
		Map					getErrorPages(Map data)
		{
			Map errorPages;

			if (data.find("error_page_403") != data.end())
				errorPages.insert(*data.find("error_page_403"));
			else
				errorPages.insert(std::make_pair("error_page_403", ERROR403));
			if (data.find("error_page_403") != data.end())
				errorPages.insert(*data.find("error_page_404"));
			else
				errorPages.insert(std::make_pair("error_page_404", ERROR404));
			if (data.find("error_page_500") != data.end())
				errorPages.insert(*data.find("error_page_500"));
			else
				errorPages.insert(std::make_pair("error_page_500", ERROR500));
			if (data.find("error_page_502") != data.end())
				errorPages.insert(*data.find("error_page_502"));
			else
				errorPages.insert(std::make_pair("error_page_502", ERROR502));
			return errorPages;
		}
		std::string			getServerName(Map data) const
		{
			Map::iterator it;

			it = data.find("server_name");
			if (it == data.end())
                return SEVRERNAME;
			return it->second;
		};
		int					getMaxBodySize(Map data) const
		{
			Map::iterator it;

			it = data.find("max_body_size");
			if (it == data.end())
                return CLINETMAXBODYSIZE;
			return std::stoi(it->second);
		};
		std::string			getRoot(Map data) const
		{
            return data.find("root")->second;
        };
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
		parsing & operator=(const parsing & obj);
		parsing();
		~parsing();
};

std::vector<int>	getallPorts(Data data, parsing obj);
std::vector<createSocket>	createSockets(Data data, parsing obj);
std::vector<server> createServers(Data data, parsing obj);

#endif //PARSING_HPP