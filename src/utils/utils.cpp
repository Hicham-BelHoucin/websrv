/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 09:19:03 by obeaj             #+#    #+#             */
/*   Updated: 2022/10/27 16:06:52 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// trim from end of string (right)
std::string& rtrim(std::string& str, const std::string &ws)
{
    str.erase(str.find_last_not_of(WHITESPACES) + 1);
    return str;
}

// trim from beginning of string (left)
std::string& ltrim(std::string& str, const std::string &ws)
{
    str.erase(0, str.find_first_not_of(WHITESPACES));
    return str;
}

// trim from both ends of string (right then left)
std::string&    stringtrim(std::string &str)
{
    return(ltrim(rtrim(str, WHITESPACES), WHITESPACES));
}

// print logs in the log file
void			printLogs(const std::string & line)
{
	std::ofstream	logfile;

	logfile.open("werserver.logs", std::ifstream::app);
	if (logfile.is_open())
	{
		logfile << line << std::endl;
		logfile.close();
	}
}