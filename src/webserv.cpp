/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:03:33 by obeaj             #+#    #+#             */
/*   Updated: 2022/10/18 14:13:08 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webServ.hpp"
#define PORT 80

int main(int argc, char const *argv[])
{
    if (argc != 2)
        return(1);
    (void)argv;
    int new_socket;
    char buffer[2048];
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in add; 
    add.sin_family = AF_INET;
    add.sin_addr.s_addr = INADDR_ANY;
    add.sin_port = htons(PORT);
    bind(sockfd, (struct sockaddr*)&add, sizeof(add));
    int addrlen = sizeof(add);
    const char* reply = 
        "HTTP/1.1 200 OK\n"
        "Date: Thu, 19 Feb 2009 12:27:04 GMT\n"
        "Server: Apache/2.2.3\n"
        "Last-Modified: Wed, 18 Jun 2003 16:05:58 GMT\n"
        "ETag: \"56d-9989200-1132c580\"\n"
        "Content-Type: text/html\n"
        "Content-Length: 75\n"
        "Accept-Ranges: bytes\n"
        "Connection: Keep Alive\n"
        "\n"
        "<h3 style=\"color: blue\">Hello message sent from obeaj host motherfucker<h3>\r\n";
    while(1)
    {
        listen(sockfd, 5);
        new_socket = accept(sockfd, (struct sockaddr*)&add,(socklen_t*)&addrlen);
        int valread = read(new_socket, buffer, 2048);
        send(new_socket, reply, strlen(reply), 0);
        std::cout << buffer << std::endl;
        // closing the connected socket
        close(new_socket);
        // closing the listening socket
    }
    shutdown(sockfd, SHUT_RDWR);
 
}
