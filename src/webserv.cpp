/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:03:33 by obeaj             #+#    #+#             */
/*   Updated: 2022/10/22 17:25:40 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "webServ.hpp"
// #include "createSocket.hpp"
// #include <fstream>

// std::string readFile(std::string name)
// {
//     std::ifstream   in_file(name);
//     std::string     text;
//     std::string     line;

//     if (in_file.is_open())
//     {
//         while (getline(in_file, line, '\0'))
//             text += line;
//     }
//     else
//         std::cout << "error" << std::endl;
//     return text;
// }

// int main(int argc, char const *argv[])
// {
//     createSocket    _socket;
//     int             connection;
//     char            buff[1024];
//     std::string response;

//     response = readFile("./src/page.html");
//     if (_socket.init(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 9999) == -1)
//         std::cout << "error creating socket" << std::endl;
//     if (_socket._bind() == -1)
//         std::cout << "error binding socket" << std::endl;
//     while (1)
//     {
//         if (_socket._listen() == -1)
//             std::cout << "error listening socket" << std::endl;
//         connection = _socket._accept();
//         if (connection == -1)
//             std::cout << "error accepting connection" << std::endl;
//         read(connection, buff, 1024);
//         std::cout << buff << std::endl;
//         send(connection, response.c_str(), response.size(), 0);
//     }
//     close(connection);
//     _socket._close();
//     return 0;
// }

#include "webServ.hpp"
#include <cstring>
#define PORT 9999

int main(int argc, char const *argv[])
{
    (void)argv;
    int new_socket;
    char buffer[1024];
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in add; 
    add.sin_family = AF_INET;
    add.sin_addr.s_addr = INADDR_ANY;
    add.sin_port = htons(PORT);
    bind(sockfd, (struct sockaddr*)&add, sizeof(add));
    int addrlen = sizeof(add);
    while(1)
    {
        listen(sockfd, 5);
        new_socket = accept(sockfd, (struct sockaddr*)&add,(socklen_t*)&addrlen);
        int valread = read(new_socket, buffer, 1024);
        std::cout << buffer << std::endl;
        send(new_socket, "<h3 style=\"color: blue\">Hello message sent from obeaj host motherfucker<h3>", strlen("<h3 style=\"color: red\">Hello message sent from obeaj host motherfucker<h3>"), 0);
        std::cout << "<h3>Hello message sent<h3>\n";
    // closing the connected socket
    close(new_socket);
    // closing the listening socket
    }
    shutdown(sockfd, SHUT_RDWR);
 
}