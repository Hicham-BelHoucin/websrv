/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:57:21 by obeaj             #+#    #+#             */
/*   Updated: 2022/12/05 13:32:39 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgi.hpp"

cgi::cgi(/* args */)
{
}

cgi::~cgi()
{
}


cgi::cgi(String path, request req) : body(req.getReqBody())
{
    cgiEnvInit(path,req);
}


void cgi::cgiEnvInit(String path, request req)
{
    std::map<std::string, std::string>	headers = req.getHeaders();
    std::map<std::string, std::string>::iterator it = headers.begin();
	String temp;

	this->env["GATEWAY_INTERFACE"] = "CGI/1.1";
	this->env["REDIRECT_STATUS"] = "200";
	this->env["SCRIPT_NAME"] = path;
	this->env["SCRIPT_FILENAME"] = path;
	this->env["REQUEST_METHOD"] = req.getReqMethod();
	this->env["CONTENT_LENGTH"] = std::to_string(this->body.length());
	this->env["CONTENT_TYPE"] = headers["Content-Type"];
	this->env["PATH_INFO"] = req.getReqPath();
	this->env["PATH_TRANSLATED"] = req.getReqPath();
	this->env["QUERY_STRING"] = req.getReqQuery();
	this->env["AUTH_TYPE"] = headers["Authorization"];
	this->env["REMOTE_IDENT"] = headers["Authorization"];
	this->env["REMOTE_USER"] = headers["Authorization"];
	this->env["REQUEST_URI"] = req.getReqPath() + req.getReqQuery();
	this->env["SERVER_NAME"] = headers["Host"];
	this->env["SERVER_PROTOCOL"] = "HTTP/1.1";
	this->env["SERVER_SOFTWARE"] = "Webserv IHO-0.1";
	while (it != headers.end())
	{
		temp = it->first;
		if (temp.find("-") != std::string::npos)
			std::replace(temp.begin(), temp.end(), '-', '_');
		this->env["HTTP_" + upperCase(temp)] = it->second;
		it++;
	}
}

String cgi::executeCgi(String script, String cgi_pass)
{
	pid_t		pid;
	int			saveStdin;
	int			saveStdout;

	char		**envv;
	std::string	newBody;

	envv = getEnv();
	saveStdin = dup(STDIN_FILENO);
	saveStdout = dup(STDOUT_FILENO);

	FILE	*fIn = tmpfile();
	FILE	*fOut = tmpfile();
	long	fdIn = fileno(fIn);
	long	fdOut = fileno(fOut);
	int		n = 1;

	write(fdIn, body.c_str(), body.size());
	lseek(fdIn, 0, SEEK_SET);

	pid = fork();

	if (pid == -1)
	{
		printLogs( "Fork crashed.");
		return ("Status: 500 \r\n\r\n");
	}
	else if (!pid)
	{
		if (!cgi_pass.empty())
		{
			char *const args[] = {(char *const)cgi_pass.c_str(), (char *const)script.c_str()};
			dup2(fdIn, STDIN_FILENO);
			dup2(fdOut, STDOUT_FILENO);
			execve(cgi_pass.c_str(), args, envv);
			printLogs("Error: Execve crashed !!");
			write(STDOUT_FILENO, "Status: 500 \r\n\r\n", 16);
			exit(1);
		}
		dup2(fdIn, STDIN_FILENO);
		dup2(fdOut, STDOUT_FILENO);
		execve(script.c_str(), NULL, envv);
		printLogs("Error: Execve crashed !!");
		write(STDOUT_FILENO, "Status: 500 \r\n\r\n", 16);
		exit(1);

	}
	else
	{
		char	buffer[CGI_BUFSIZE] = {0};

		waitpid(-1, NULL, 0);
		lseek(fdOut, 0, SEEK_SET);

		n = 1;
		while (n > 0)
		{
			memset(buffer, 0, CGI_BUFSIZE);
			n = read(fdOut, buffer, CGI_BUFSIZE - 1);
			newBody += buffer;
		}
	}

	dup2(saveStdin, STDIN_FILENO);
	dup2(saveStdout, STDOUT_FILENO);
	fclose(fIn);
	fclose(fOut);
	close(fdIn);
	close(fdOut);
	close(saveStdin);
	close(saveStdout);
	for (size_t i = 0; envv[i]; i++)
		delete[] envv[i];
	delete[] envv;
	return (newBody);
}


char** cgi::getEnv() const
{
	char	**envv = new char*[env.size() + 1];
	int	j = 0;
	for (std::map<std::string, std::string>::const_iterator i = env.begin(); i != env.end(); i++) {
		std::string	element = i->first + "=" + i->second;
		envv[j] = new char[element.size() + 1];
		envv[j] = strcpy(envv[j], (const char*)element.c_str());
		j++;
	}
	envv[j] = NULL;
	return envv;
}


