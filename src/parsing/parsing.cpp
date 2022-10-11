/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:54:26 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/10/11 17:05:51 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.hpp"

void	parsing::checkBrackets(std::string text)
{
	std::stack<char> s;

	for (int i = 0; i < text.size(); i++)
	{
		if ((text[i] == '}' || text[i] == ']') && s.empty())
		{
			throw UnclosedBrakets();
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
			throw UnclosedBrakets();
			return ;
		}
		else if (text[i] == ']' && s.top() != '[')
		{
			throw UnclosedBrakets();
			return ;
		}

	}
	if (!s.empty())
		throw UnclosedBrakets();
}


void parsing::checkSemicolon(std::string text)
{
	std::stringstream str(text);
	std::string line;
	while (std::getline(str, line, '\n'))
	{
		std::stringstream ln(line);
		int index = 0;
		std::string l;
		ln >> l;
		skipWhiteSpaces(line, index);
		if ( l != "server" && l != "location" && line[line.length() - 1] != ';' && 
			!strchr(line.c_str(), '}') && !strchr(line.c_str(), '{') && line[index] != '#')
		{
			std::cout << line << std::endl;
			throw Nosemicolon();
		}
		else if ((((l.substr(0,6) == "server" && l.substr(0,7) != "server_") || l.substr(0,8) == "location" || line[index] == '{' || 
			line[index] == '}') && line[line.length() - 1] == ';') || l == ";")
		{
			std::cout << line << std::endl;
			throw Extrasemicolon();
		}
		else if ((strchr(line.c_str(),'{') || strchr(line.c_str(),'}')))
		{
			int i = 0;
			while(line[i] != '\0')
			{
				if (!strchr("\n\t\v\f\r ", line[i]) && line[i] != '}' && line[i] != '{')
				{
					throw Nobarcket();
				}
				i++;
			}
		}
	}
}

AllData	parsing::getAllData(void) const
{
	return allData;
}

int	parsing::countSize(std::string text)
{
	size_t index;
	size_t __size;

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

void	parsing::checkKeyWords(void)
{
	std::string keywords[3] = {"listen", "host", "root"};
	AllData::iterator begin;
	int				i = 0;

	begin = allData.begin();
	while (begin != allData.end())
	{
		for (int j = 0; j < 3; j++)
		{
			if (begin->second.data.find(keywords[j]) == begin->second.data.end())
			{
				throw std::runtime_error("messing 1 necessary element => '" + keywords[j] + "' server Number : " + std::to_string(i + 1));
				return ;
			}
		}
		i++;
		begin++;
	}
}

parsing::parsing(std::string filename) : _size(0)
{
	std::string text;
	std::string	subText;
	t_data		__data;
	int			i;
	int			start;
	int			end;

	text = readFile(filename);
	_size = countSize(text);
	checkBrackets(text);
	checkSemicolon(text);
	if (!_size)
		throw Usage();
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
			allData.insert(std::make_pair("server", __data));
			info.clear();
			locations.clear();
			i++;
		}
		// checkKeyWords();
	}
}

void	parsing::checkMethods(std::vector<std::string>  & methods)
{
	for (int i = 0; i < methods.size(); i++)
	{
		if ((methods[i] != "GET" ) && ( methods[i] != "POST" ) && ( methods[i] != "DELETE" ))
		{
			throw std::runtime_error("Bad Syntax in allow_methods\nUsage : [GET,POST,DELETE] => '" + methods[i] + "'");
			return ;
		}
	}
}

void	parsing::skip(const std::string & line, int & index)
{
	index = line.find_first_of(SPECIAL, index);
	if (index == std::string::npos)
		index = line.size();
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

void	parsing::skipWhiteSpaces(const std::string & line, int & index)
{
	while (line[index] && strchr(WHITESPACES, line[index]))
		index++;
}

Pair	parsing::parseLine(std::string line)
{
	std::string keyWord;
	std::string value;
	int			start;
	int			end;

	start = 0;
	end = line.find_first_of(" ", start);
	keyWord = line.substr(start, end - start);
	start = end + 1;
	skipWhiteSpaces(line, start);
	end = line.find_first_of(";", start);
	value = line.substr(start, end - start);
	return std::make_pair(keyWord, value);
}

const char * parsing::Usage::what() const throw ()
{
	return "Usage : \n \
		server  \n\
		{  \n\
			server properties ; \n \
			location /  \n\
			{  \n\
				location properties ; \n \
			} \n\
		}";
}

const char * parsing::UnclosedBrakets::what() const throw ()
{
	return "Error: You Have an Unclosed Bracket !";
}
const char * parsing::Nosemicolon::what() const throw ()
{
	return "Error: A semicolon is missing !";
}
const char * parsing::Extrasemicolon::what() const throw ()
{
	return "Error: An extra semicolon found !";
}
const char * parsing::Nobarcket::what() const throw ()
{
	return "Error: The curly braket should be in a single line !";
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

void	parsing::parseLocation(std::string text, int start)
{
	std::string line;
	Methods		methods;
	Pair	conf;
	int		end;

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
			}
			else
			{
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
		}
		skipWhiteSpaces(text, ++end);
		parseLocation(text, end);
	}
}

void	parsing::parseFile(std::string text, int start)
{
	Pair	conf;
	int		end;

	end = text.find_first_of(";\n", start);
	if (end == std::string::npos)
		return ;
	if (start < end)
	{
		std::string line = text.substr(start, end - start);
		if (getTokenType(line) == PAIR)
		{
			conf = parseLine(line);
			info.insert(conf);
		}
		else if (getTokenType(line) == LOCATION)
		{
			conf = parseLine(line);
			end = text.find_first_of("}", start);
			parseLocation(text.substr(start, (end - start)), 0);
			if (locationsInfo.empty())
			{
				throw std::runtime_error("error : Curly brakets without properties");
				return ;
			}
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

std::vector <std::string >	parsing::parseArray(const std::string & line)
{
	std::vector <std::string > methods;

	for (int i = 0; line[i] != ';'; i++)
	{
		if (line[i] == '[')
		{
			i++;
			for (int j = i; line[j] != ']' && j < line.size(); j++)
			{
				int start;
				skipWhiteSpaces(line, j);
				start = j;
				j = line.find_first_of(" {}[];,", j);
				if (j == std::string::npos)
					j = line.size();
				if (start < j)
					methods.insert(methods.end(), line.substr(start, j - start));
			}
			break;
		}
	}
	try
	{
		checkMethods(methods);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		exit(0);
	}
	return methods;
}

parsing::~parsing()
{
	// delete [] allData;
}

