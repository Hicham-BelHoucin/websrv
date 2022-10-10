/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:54:26 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/10/10 09:59:35 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.hpp"
/*------------------------------EXCEPTIONS----------------------------------------*/

const char* parsing::BRACES::what() const throw()
{
	return "Error: You have an unclosed brace !";
}
const char* parsing::CURLY_BRACES::what() const throw()
{
	return "Error: You have an unclosed curly brace !";
}
const char* parsing::SEMCOLON::what() const throw()
{
	return "Error: A semicolon is missing !";
}
const char* parsing::NFOUND_KEY::what() const throw()
{
	return "Error: You have an unclosed brace !";
}

/*--------------------------------------------------------------------------------*/

parsing::parsing(std::string filename)
{
	std::string text;

	text = readFile(filename);
	parseFile(text, 0);
	data.push_back(info);
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

    if (in_file.is_open())
		getline(in_file, text, '\0');
    else
        std::cout << "error" << std::endl;
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
	else if (value.first == "[")
		return OPENSQUAREBRACKET;
	else if (value.first == "]")
		return CLOSESQUAREBRACKET;
	else if (value.first == "{")
		return OPENCURLYBRACKET;
	else if (value.first == "}")
		return CLOSECURLYBRACKET;
	else if (value.first == ";")
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
			locations.insert(std::make_pair(conf.second, locationsInfo));
			locationsInfo.clear();
		}
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

void parsing::syntax(std::string file)
{
    std::string data = readFile(file);
    
    if (!curly_braces(data))
        throw CURLY_BRACES();
    else if (!braces(data))
        throw BRACES();
    else if (!semicolon(data))
        throw SEMCOLON();
	else if(!check_keys())
		throw NFOUND_KEY();
}

int parsing::curly_braces(std::string data)
{
	return 0;
}
int parsing::braces(std::string data)
{
	return 0;
}
int parsing::semicolon(std::string data)
{
	std::stringstream str(data);
	std::string line;
	while(std::getline(str, line, '\n'))
	{
		std::cout << line;
	}
	return 0;
}

int parsing::check_keys()
{
	return 0;
}



parsing::~parsing()
{
	
}

