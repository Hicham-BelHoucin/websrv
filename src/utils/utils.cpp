/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 09:19:03 by obeaj             #+#    #+#             */
/*   Updated: 2022/10/31 17:39:10 by hbel-hou         ###   ########.fr       */
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

std::vector<int>	getallPorts(Data data, parsing obj)
{
	std::vector<int> ports;
	std::vector<int> temp;
	for (int i = 0; i < data.size(); i++)
	{
		temp = obj.getPorts(data[0].data);
		ports.insert(ports.end(), temp.begin(), temp.end());
	}
	return ports;
}

std::vector<server> createServers(Data data, parsing obj)
{
	String 				root;
	String 				host;
	String 				serverName;
	Set 				locations;
	int 				maxBodySize;
	std::vector<int> 	ports;
	Map 				errorPages;
	std::vector<server>	servers;

	for (int i = 0; i < data.size(); i++)
	{
		root = obj.getRoot(data[i].data);
		host = obj.getHost(data[i].data);
		serverName = obj.getServerName(data[i].data);
		maxBodySize = obj.getMaxBodySize(data[i].data);
		locations = data[i].locations;
		errorPages = obj.getErrorPages(data[i].data);
		ports = obj.getPorts(data[i].data);
		servers.push_back(server(root, host, serverName, locations, maxBodySize, ports, errorPages));
	}
	return servers;
}

int	checkExtansion(String filename)
{
	if (filename.compare(filename.size() - 4, filename.size(), "conf"))
		return -1;
	return 0;
}