/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 09:19:03 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/20 11:54:08 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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

std::string	_displayTimestamp( void )
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer [80];

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	strftime (buffer, 80, "[%d/%m/%Y  %H:%M:%S] ", timeinfo);
	return buffer;
}

// print logs in the log file
void			printLogs(const std::string & line)
{
	// std::ofstream	logfile;

	// logfile.open("werserver.logs", std::ifstream::app);
	// if (logfile.is_open())
	// {
	// 	logfile << "" << line  << std::endl;
	// 	logfile.close();
	// }
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

int			hexToDecimal(std::string str)
{
	std::stringstream stream;
	int 				ret;

	stream << str;
	stream >> std::hex >> ret;
	return ret;
}

std::vector<createSocket>	createSockets(Data data, parsing obj)
{
	std::vector<createSocket>					sockets;
	std::pair<Map::iterator, Map::iterator>		ret;
	createSocket								socket;
	String										host;

	for (int i = 0; i < data.size(); i++)
	{
		ret = data[i].data.equal_range("listen");
		host = data[i].data.find("host")->second;
		while (ret.first != ret.second)
		{
			int port = std::stoi(ret.first->second);
			if (std::find(sockets.begin(), sockets.end(), createSocket(0, host, port)) == sockets.end())
			{
				socket = createSocket(host, port);
				sockets.push_back(socket);
			}
			ret.first++;
		}
	}
	return sockets;
}

int	getsocket(std::vector<createSocket> sockets, int fd)
{
	for (int i = 0; i < sockets.size(); i++)
		if (sockets[i].getSockfd() == fd)
			return i;
	return -1;
}

int	checkExtansion(String filename)
{
	if (filename.compare(filename.size() - 4, filename.size(), "conf"))
		return -1;
	return 0;
}

std::string	readFile(std::string filename)
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
    return text;
}

bool	isMatch(String pattern, String str)
{
	if (pattern.empty() && str.empty())
		return (true);
	if (pattern.at(0) == '?' && str.empty())
		return (false);
	if (!pattern.substr(1).empty())
	{
		if ((pattern.at(0) == '*' || pattern.at(0) == '?') && !pattern.substr(1).empty() && str.empty())
			return (false);
	}
	if (pattern.at(0) == '?' || pattern.at(0) == str.at(0))
		return (isMatch(pattern.substr(1), str.substr(1)));
	if (pattern.at(0) == '*')
		return (isMatch(pattern.substr(1), str) || isMatch(pattern, str.substr(1)));
	return (false);
}

ResponseIUtils::PATHMODE	checkPathMode(std::string path)
{
	struct stat  st;

	if(stat(path.c_str(), &st) == 0)
	{
		if(st.st_mode &  S_IFDIR &&  st.st_mode & S_IRWXU)
			return	ResponseIUtils::D_ALL;
		else if (st.st_mode & S_IFDIR && st.st_mode & S_IRUSR && st.st_mode & S_IWUSR)
			return    ResponseIUtils::D_RW;
		else if (st.st_mode & S_IFDIR && st.st_mode & S_IXUSR && st.st_mode & S_IWUSR)
			return    ResponseIUtils::D_WX;
		else if (st.st_mode & S_IFDIR && st.st_mode & S_IRUSR && st.st_mode & S_IXUSR)
			return    ResponseIUtils::D_RX;
		else if (st.st_mode & S_IFDIR && st.st_mode & S_IRUSR)
			return    ResponseIUtils::D_READ;
		else if (st.st_mode & S_IFDIR && st.st_mode & S_IWUSR)
			return    ResponseIUtils::D_WRITE;
		else if (st.st_mode & S_IFDIR && st.st_mode & S_IXUSR)
			return    ResponseIUtils::D_EXEC;
		else if(st.st_mode & S_IFREG && st.st_mode & S_IRWXU)
			return	ResponseIUtils::F_ALL;
		else if (st.st_mode & S_IFREG && st.st_mode & S_IRUSR && st.st_mode & S_IWUSR)
			return    ResponseIUtils::F_RW;
		else if (st.st_mode & S_IFREG && st.st_mode & S_IXUSR && st.st_mode & S_IWUSR)
			return    ResponseIUtils::F_WX;
		else if (st.st_mode & S_IFREG && st.st_mode & S_IRUSR && st.st_mode & S_IXUSR)
			return    ResponseIUtils::F_RX;
		else if (st.st_mode & S_IFREG && st.st_mode & S_IRUSR)
			return    ResponseIUtils::F_READ;
		else if (st.st_mode & S_IFREG && st.st_mode & S_IWUSR)
			return    ResponseIUtils::F_WRITE;
		else if (st.st_mode & S_IFREG && st.st_mode & S_IXUSR)
			return    ResponseIUtils::F_EXEC;
		else if (st.st_mode & S_IFDIR)
			return    ResponseIUtils::DIR;
		else if (st.st_mode & S_IFREG)
			return	  ResponseIUtils::FILE;
		else
			return (ResponseIUtils::NONE);
	}
    return (ResponseIUtils::NONE);
}

String checkExtension(String filename)
{
	if (filename.empty())
        return ("");
	size_t found = filename.find_last_of(".");
	if (found == std::string::npos)
        return (filename);
	return (filename.substr(found + 1));
}

String dirListing(String dirname)
{
	DIR *dr;
	struct dirent *en;
	String body;
	dr = opendir(dirname.c_str()); //open all directory
	if (dr)
	{
		while ((en = readdir(dr)) != NULL) \
		{
			if (en->d_name[0]!= '.')
			{
				body.append(en->d_name);
				body.append("\n");
			}
		}
		closedir(dr); //close all directory
	}
	return(body);
}


String getDate()
{
	char m_time[50];

	time_t now = time(0);
	tm *ltm = gmtime(&now);
	strftime(m_time, sizeof(m_time), "%a, %d %b %Y %H:%M:%S GMT", ltm);
	String s(m_time);
	return (s);
}

void check(int condition)
{
	if (condition)
	{
		// printLogs(strerror(errno));
		print(strerror(errno));
	}
}

std::map<int, std::string> setStatusPhrases()
{
	std::map<int, std::string> status;

	status[200] = "OK";
	status[201] = "Created";
	status[202] = "Accepted";
	status[203] = "Non-Authoritative Information";
	status[204] = "No Content";
	status[205] = "Reset Content";
	status[206] = "Partial Content";
	status[300] = "Multiple Choices";
	status[301] = "Moved Permanently";
	status[302] = "Found";
	status[303] = "See Other";
	status[304] = "Not Modified";
	status[305] = "Use Proxy";
	status[308] = "Permanent Redirect";
	status[400] = "Bad Request";
	status[401] = "Unauthorized";
	status[403] = "Forbidden";
	status[404] = "Not Found";
	status[405] = "Method Not Allowed";
	status[406] = "Not Acceptable";
	status[410] = "Gone";
	status[411] = "Length Required";
	status[500] = "Internal Server Error";
	status[501] = "Not Implemented";
	status[502] = "Bad Gateway";
	status[505] = "HTTP Version Not Supported";

	return status;
}

String	getContentType(String path)
{
	String type = checkExtension(path);
	if (type == "html")
		return("text/html");
	else if (type == "css")
		return "text/css";
	else if (type == "js")
		return "text/javascript";
	else if (type == "jpeg" || type == "jpg")
		return "image/jpeg";
	else if (type == "png")
		return "image/png";
	else if (type == "bmp")
		return "image/bmp";
	else if (type == "json")
		return "application/json";
	else
		return "text/plain";
}

bool isNumber(const std::string& s)
{
    return s.find_first_not_of("0123456789") == std::string::npos;
}

int line_countword(std::string line)
{
    int c = 0;
    for(int i = 0 ; i < line.size() ;i++)
    {
        if(line[i] == ' ')
           c++;
    }
    c = c + 1;
    return c;
}

server selectServer(std::vector<server> servers, std::string host, std::string port)
{
    std::vector<server>::iterator it = servers.begin();
    std::vector<server> selected;
    server elected;
    while (it != servers.end())
    {
        std::vector<int> ports = (*it).getPorts();
        if (std::find(ports.begin(), ports.end(), stoi(port)) != ports.end())
        {
            selected.push_back(*it);
        }
        it++;
    }
    it = selected.begin();
    while (it != selected.end())
    {
        std::stringstream s((*it).getServerName());
        std::string servername;
        while (std::getline(s, servername, ' '))
        {
            if (servername == host)
                elected = *it;
        }
        it++;
    }
	if (elected.getHost() == "")
		elected = servers[0];
    return elected;
}

std::string generateErrorPage(int number, std::string description)
{
	return (
		"<!DOCTYPE html> \n \
		<html lang=\"en\"> \n \
		<head> \n \
			<title>Document</title> \n \
			<style> \n \
				.container { \n \
					display: flex; \n \
					height: 100vh; \n \
					width: 100vw; \n \
					flex-direction:column; \n \
					justify-content: center; \n \
					align-items: center; \n \
				} \n \
				div { \n \
					color: black; \n \
					font-weight: 800; \n \
					font-size: 5rem; \n \
				} \n \
			</style> \n \
		</head> \n \
		<body class=\"container\"> \n \
			<div>Error " + std::to_string(number) + "</div> \n \
			<div>" + description + "</div> \n \
		</body> \n \
		</html>"
	);
}