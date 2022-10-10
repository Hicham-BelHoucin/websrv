/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:54:26 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/10/09 12:36:36 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.hpp"

parsing::parsing()
{
}

void	parsing::checkMethods(std::vector<std::string>  & methods)
{
	for (int i = 0; i < methods.size(); i++)
	{
		std::transform(methods[i].begin(), methods[i].end(), methods[i].begin(), ::toupper);
		if ((methods[i] != "GET" ) && ( methods[i] != "POST" ) && ( methods[i] != "DELETE" ))
		{
			throw std::runtime_error("Bad Syntax in allow_methods\nUsage : [GET,POST,DELETE]");
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
void	parsing::parseFile(std::string text, int start)
{
	// Map		info;
	Pair	conf;
	int		end;

	if (start > end)
		return ;
	end = text.find_first_of("\n", start);
	if (end == std::string::npos)
		end = text.size();
	if (start < end)
	{
		std::string line = text.substr(start, end - start);
		if (line == "location_/")
		{
			puts("push");
			data.push_back(info);
			return ;
		}
		conf = parseLine(line);
		info.insert(conf);
		skipWhiteSpaces(text, ++end);
		parseFile(text, end);
	}
}

void	parsing::parseArray(const std::string & line)
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
				skip(line, j);
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
	}

}

parsing::~parsing()
{
}

