/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:03:33 by obeaj             #+#    #+#             */
/*   Updated: 2022/10/12 16:35:10 by obeaj            ###   ########.fr       */
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
