/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:54:26 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/11/21 11:21:53 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.hpp"

//////////////////////////////////// [Getters] /////////////////////////////////////

std::string 		parsing::getHost(Map data) const {
	return data.find("host")->second;
};

std::vector<int> 	parsing::getPorts(Map data) const
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

Map					parsing::getErrorPages(Map data)
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

std::string			parsing::getServerName(Map data) const
{
	Map::iterator it;

	it = data.find("server_name");
	if (it == data.end())
		return SEVRERNAME;
	return it->second;
};

int					parsing::getMaxBodySize(Map data) const
{
	Map::iterator it;

	it = data.find("max_body_size");
	if (it == data.end())
		return CLINETMAXBODYSIZE;
	return std::stoi(it->second);
};

std::string			parsing::getRoot(Map data) const
{
	return data.find("root")->second;
};

Data	parsing::getData(void) const
{
	return data;
}

//////////////////////////////////// [tools] /////////////////////////////////////

parsing::parsing()
{

}

int	parsing::countSize(std::string text)
{
	size_t index;
	int __size;

	index = 0;
	__size = 0;
	while (1337)
	{
		index = text.find("server\n{", index);
		if (index == std::string::npos)
			return __size;
		__size++;
		index += strlen("server\n{");
	}
	return __size;
}

void	parsing::skip(const std::string & line, size_t & index)
{
	index = line.find_first_of(SPECIAL, index);
	if (index == std::string::npos)
		index = line.size();
}

void	parsing::skipWhiteSpaces(const std::string & line, size_t & index)
{
	while (line[index] && strchr(WHITESPACES, line[index]))
		index++;
}

int	parsing::getTokenType(std::string line)
{
	Pair	value = parseLine(line);

	if (value.first == "server")
		return KEYWORD;
	else if (value.first == "location")
		return LOCATION;
	if (value.first[0] == '#')
		return COMMENT;
	else if (value.first != value.second)
		return PAIR;
	else if (value.first[0] == '[')
		return OPENSQUAREBRACKET;
	else if (value.first[0] == ']')
		return CLOSESQUAREBRACKET;
	else if (value.first[0] == '{')
		return OPENCURLYBRACKET;
	else if (value.first[0] == '}')
		return CLOSECURLYBRACKET;
	else if (value.first[0] == ';')
		return SEMICOLONE;
	return NONE;
}

std::string	parsing::readFile(std::string filename)
{
	std::ifstream   in_file(filename);
    std::string     text;
    std::string     line;

    if (in_file.is_open())
	{
		while (getline(in_file, line, '\n'))
		{
			if (line != "" &&  line.find_first_not_of(WHITESPACES, 0) != std::string::npos)
			{
				line += "\n";
				text += line;
			}
		}
	}
    else
        throw std::runtime_error("cannot open file " + filename);
    return text;
}

//////////////////////////////////// [constructor and destructor ] /////////////////////////////////////

parsing::parsing(std::string filename) : _size(0)
{
	std::string text;
	std::string	subText;
	t_data		__data;
	unsigned int			i;
	int			start;
	size_t			end;

	text = readFile(filename);
	_size = countSize(text);
	checkBrackets(text);
	checkSemicolon(text);
	if (!_size)
		throw Parseerror("Usage : \n \
		server  \n\
		{  \n\
			server properties ; \n \
			location /  \n\
			{  \n\
				location properties ; \n \
			} \n\
		}");
	i = 0;
	end = 0;
	if (_size)
	{
		while (i < _size)
		{
			start = end;
			end = text.find("server\n{", start + 5);
			if (end == std::string::npos)
				end = text.size();
			subText = text.substr(start, (end - start));
			parseFile(subText, 0);
			__data.data = info;
			__data.locations = locations;
			data.push_back(__data);
			info.clear();
			locations.clear();
			i++;
		}
		checkKeyWords();
	}
	printLogs(_displayTimestamp() + "file parsed successfully");
}

parsing::~parsing() {}

//////////////////////////////////// [parse file ] /////////////////////////////////////

void	parsing::parseFile(std::string text, size_t start)
{
	std::string keywords[10] = {"listen", "host", "root", "server_name", "client_max_body_size", "error_page_403" , "error_page_404", "error_page_500", "error_page_502"};
	Pair	conf;
	size_t		end;

	end = text.find_first_of(";\n", start);
	if (end == std::string::npos)
		return ;
	if (start < end)
	{
		std::string line = text.substr(start, end - start);
		if (getTokenType(line) == PAIR)
		{
			conf = parseLine(line);
			if (conf.first == "listen")
			{
				if (conf.second.find_first_not_of("0123456789") != std::string::npos)
					throw	std::runtime_error("port value must composed only from digits ! ");
			}
			else if (conf.first == "host")
				checkHost(conf);
			else if (conf.first == "client_max_body_size")
			{
				if (conf.second.find_first_not_of("0123456789m") != std::string::npos || conf.second[conf.second.size() - 1] != 'm')
					throw std::runtime_error("client max body must be composed only from digits !");
			}
			for (int i = 0; i < 10; i++)
			{
				if (conf.first == keywords[i])
					break;
				else if (i == 9 && conf.first != keywords[i])
					throw std::runtime_error("unknown key word " + conf.first);
			}
			info.insert(conf);
		}
		else if (getTokenType(line) == LOCATION)
		{
			conf = parseLine(line);
			if (checkPath(conf.second))
				return ;
			end = text.find_first_of("}", start);
			parseLocation(text.substr(start, (end - start)), 0);
			if (locationsInfo.empty())
			{
				throw std::runtime_error("error : Curly brakets without properties");
				return ;
			}
			checkMethodsKeyWords(locationsInfo);
			locations.insert(std::make_pair(conf.second, locationsInfo));
			locationsInfo.clear();
		}
		else if (getTokenType(line) == COMMENT)
			end = text.find_first_of("\n", start);
		else if (getTokenType(line) == NONE)
		{
			throw std::runtime_error("unrecognized token : " + line);
		}
		skipWhiteSpaces(text, ++end);
		parseFile(text, end);
	}
}

//////////////////////////////////// [parse line] /////////////////////////////////////

Pair	parsing::parseLine(std::string line)
{
	std::string keyWord;
	std::string value;
	size_t			start;
	size_t			end;

	start = 0;
	end = line.find_first_of(" ", start);
	keyWord = line.substr(start, end - start);
	start = end + 1;
	skipWhiteSpaces(line, start);
	end = line.find_first_of(";", start);
	value = line.substr(start, end - start);
	if (keyWord[0] != '#' && keyWord != "return" && keyWord != "server_name" && value.find_first_of(WHITESPACES) != std::string::npos)
		throw std::runtime_error("error in this line => " + value);
	return std::make_pair(keyWord, value);
}

//////////////////////////////////// [check keywords ] /////////////////////////////////////

void	parsing::checkHost(Pair conf)
{
	if (conf.second.find_first_not_of("0123456789.") != std::string::npos)
		throw	std::runtime_error("host value must composed only from digits ! ");
	int j = 0;
	for (unsigned long i = 0; i < conf.second.size(); i++)
	{
		if (conf.second[i] == '.' && !std::isdigit(conf.second[i + 1]))
			throw std::runtime_error("host value must be an ip address ! => 0.0.0.0");
		else if (conf.second.find_first_not_of("0123456789", i) != std::string::npos)
		{
			j++;
			i = conf.second.find_first_not_of("0123456789", i);
			if (conf.second[i] == '.' && !conf.second[i + 1])
				throw std::runtime_error("host value must be an ip address ! => 0.0.0.0");
		}
	}
	if (j != 3)
		throw std::runtime_error("host value must be an ip address ! => 0.0.0.0");
}

int		parsing::checkDuplicatePort(Map data)
{
	std::pair<Map::iterator, Map::iterator> conf;
	std::set<int>							ports;
	int										port;

	conf = data.equal_range("listen");
	while (conf.first != conf.second)
	{
		port = std::stoi(conf.first->second);
		if (ports.find(port)!= ports.end())
			throw std::runtime_error("duplicate port!");
		ports.insert(port);
		conf.first++;
	}
	return 0;
}

int        parsing::checkMessingElements(Map data, std::string keys[])
{
	for (int i = 0; i < 3; i++)
	{
		if (data.count(keys[i]) == 0)
			throw std::runtime_error("messing element: " + keys[i]);
	}
	return 0;
}

int        parsing::checkDuplicateKwywords(Map data, std::string keys[])
{
	std::pair<Map::iterator, Map::iterator> conf;

	for (int i = 1; i < 10; i++)
    {
		if (data.count(keys[i]) > 1)
			throw std::runtime_error("duplicate kwywords: " + keys[i]);
	}
	return 0;
}

void	parsing::checkKeyWords(void)
{
	unsigned long				i;
	std::string keywords[10] = {
		"listen",
		"host",
		"root",
		"server_name",
		"client_max_body_size",
		"error_page_403" ,
		"error_page_404",
		"error_page_500",
		"error_page_502"
	};

	i = 0;
	while (i < data.size())
	{
		checkDuplicatePort(data[i].data);
		checkMessingElements(data[i].data, keywords);
		checkDuplicateKwywords(data[i].data, keywords);
		i++;
	}
}

//////////////////////////////////// [parse locations] /////////////////////////////////////

void	parsing::checkMethodsKeyWords(LocationMap locations)
{
	LocationMap::iterator		begin;
	std::string names[8] = {
		"upload_enable",
		"upload_store",
		"allow_methods",
		"autoindex" ,
		"index",
		"return",
		"fastcgi_pass",
		"root"
	};

	begin = locations.begin();
	while (begin != locations.end())
	{
		for (int i = 0; i < 8; i++)
		{
			if (begin->first == "upload_enable" || begin->first == "autoindex")
			{
				if (begin->second[0] != "off" && begin->second[0] != "on")
				{
					throw std::runtime_error("unacceptable value : " + begin->second[0]);
					return ;
				}
			}
			else if (names[i] == begin->first)
				break;
			else if (i == 7 && names[i] != begin->first)
			{
				throw std::runtime_error("unknown key word " + begin->first);
				return ;
			}
		}
		begin++;
	}
}

int	parsing::checkPath(std::string text)
{
	if (text[0] != '/' && text[0] != '*')
	{
		throw std::runtime_error("loacation must be followed by path '/' ");
		return (1);
	}
	if (text[0] == '*' && text[1] != '.')
	{
		throw std::runtime_error("loacation must be followed by path '" + text + "'");
		return (1);
	}
	if (text[0] == '*' && (text.substr(1) != ".php" && text.substr(1) != ".py"))
	{
		throw std::runtime_error("unacceptable extensions " + text + " expected extensions : ['.php', '.py']");
		return (1);
	}
	return (0);
}

void	parsing::parseLocation(std::string text, size_t start)
{
	std::string line;
	Methods		methods;
	Pair	conf;
	size_t		end;

	end = text.find_first_of(";\n", start);
	if (end == std::string::npos)
		return;
	if (start < end)
	{
		line = text.substr(start, end - start);
		if (getTokenType(line) == PAIR)
		{
			conf = parseLine(line);
			if (conf.second[0] == '[')
			{
				methods = parseArray(conf.second);
				if (methods.empty())
				{
					throw std::runtime_error("empty square brackets ! ");
					return ;
				}
			}
			else
			{
				if (conf.second.find_first_of("{}[];,()") != std::string::npos)
					throw std::runtime_error("error : " + conf.second);
				methods.clear();
				methods.push_back(conf.second);
			}
			locationsInfo.insert(std::make_pair(conf.first, methods));
		}
		else if (getTokenType(line) == COMMENT)
			end = text.find_first_of("\n", start);
		else if (getTokenType(line) == NONE)
		{
			throw std::runtime_error("unrecognized token : '" + line + "'");
			return ;
		}
		skipWhiteSpaces(text, ++end);
		parseLocation(text, end);
	}
}

//////////////////////////////////// [syntax check] /////////////////////////////////////

void	parsing::checkBrackets(std::string text)
{
	std::stack<char> s;

	for (unsigned long i = 0; i < text.size(); i++)
	{
		if ((text[i] == '}' || text[i] == ']') && s.empty())
		{
			throw Parseerror("Error: You Have an Unclosed Bracket !");
			return ;
		}
		if (text[i] == '{' || text[i] == '[')
			s.push(text[i]);
		else if (text[i] == '}' && s.top() == '{')
			s.pop();
		else if (text[i] == ']' && s.top() == '[')
			s.pop();
		else if (text[i] == '}' && s.top() != '{')
		{
			throw Parseerror("Error: You Have an Unclosed Bracket !");
			return ;
		}
		else if (text[i] == ']' && s.top() != '[')
		{
			throw Parseerror("Error: You Have an Unclosed Bracket !");
			return ;
		}
	}
	if (!s.empty())
		throw Parseerror("Error: You Have an Unclosed Bracket !");
}

int parsing::IsSpecialKey(std::string line)
{
	size_t	index = 0;

	skipWhiteSpaces(line, index);
	if (line == "server" || line[index] == '{' || line[index] == '}' || line.compare(index, 8, "location") == 0 || line[index] == '#')
		return (1);
	return (0);
}

void parsing::checkSemicolon(std::string text)
{
	std::stringstream str(text);
	std::string line;
	size_t index = 0;
	size_t pos = 0;

	while (std::getline(str, line, '\n'))
	{
		skipWhiteSpaces(line, index);
		pos = line.find(';');
		if (IsSpecialKey(line) == 1)
			continue;
		else if (line[line.size() - 1] != ';')
			throw std::runtime_error("missing semicolone !" + line);
		else if (pos != std::string::npos && line[pos] == ';' && line[pos + 1] == ';')
			throw std::runtime_error("extra semicolone !" + line);
		else if (line[index] == ';')
			throw std::runtime_error("extra semicolone !" + line);
	}
}

//////////////////////////////////// [exeptions] /////////////////////////////////////

const char * parsing::Parseerror::what() const throw ()
{
	return error;
}

//////////////////////////////////// [parse allow methods] /////////////////////////////////////

void	parsing::checkMethods(std::vector<std::string>  & methods)
{
	for (unsigned long i = 0; i < methods.size(); i++)
	{
		if ((methods[i] != "GET" ) && ( methods[i] != "POST" ) && ( methods[i] != "DELETE" ))
		{
			throw std::runtime_error("Bad Syntax in allow_methods\nUsage : [GET,POST,DELETE] => '" + methods[i] + "'");
			return ;
		}
	}
}

std::vector <std::string >	parsing::parseArray(const std::string & line)
{
	std::stringstream				string(line.substr(1, line.size() - 2));
	std::vector <std::string >		methods;
	std::string						method;

	while (getline(string, method, ','))
	{
		if (method == "" || line[line.size() - 2] == ',')
			throw std::runtime_error("Usage [GET,POST,DELETE]");
		methods.push_back(method);
	}
	checkMethods(methods);
	return methods;
}
