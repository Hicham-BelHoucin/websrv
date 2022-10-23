/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:03:33 by obeaj             #+#    #+#             */
/*   Updated: 2022/10/22 18:58:14 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webServ.hpp"
#include "createSocket.hpp"
#include <fstream>

std::string readFile(std::string name)
{
    std::ifstream   in_file(name);
    std::string     text;
    std::string     line;

    if (in_file.is_open())
    {
        while (getline(in_file, line, '\0'))
            text += line;
    }
    else
        std::cout << "error" << std::endl;
    return text;
}

int main(int argc, char const *argv[])
{
    createSocket    _socket;
    int             connection;
    char            buff[1024];
    std::string response;

	response =
        "HTTP/1.1 200 OK\n"
        "Date: Thu, 19 Feb 2009 12:27:04 GMT\n"
        "Server: Apache/2.2.3\n"
        "Last-Modified: Wed, 18 Jun 2003 16:05:58 GMT\n"
        "ETag: \"56d-9989200-1132c580\"\n"
        "Content-Type: text/html\n"
        "Content-Length: 1900\n"
        "Accept-Ranges: bytes\n"
        "Connection: Keep Alive\n"
        "\n";
    response += readFile("./src/page.html");
	response += "\r\n";
    if (_socket.init(AF_INET, SOCK_STREAM, 0, "0.0.0.0", 1024) == -1)
        std::cout << "error creating socket" << std::endl;
    if (_socket._bind() == -1)
        std::cout << "error binding socket" << std::endl;
    while (1)
    {
        if (_socket._listen() == -1)
            std::cout << "error listening socket" << std::endl;
        connection = _socket._accept();
        if (connection == -1)
            std::cout << "error accepting connection" << std::endl;
        read(connection, buff, 1024);
        write(connection, response.c_str(), response.size());
    	close(connection);
    }
    _socket._close();
    return 0;
}