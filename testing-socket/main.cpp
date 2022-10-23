/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 10:05:40 by hbel-hou          #+#    #+#             */
/*   Updated: 2022/10/18 13:40:41 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <iostream>
#include <cstdlib> // For exit() and EXIT_FAILURE
#include <iostream> // For cout
#include <unistd.h> // For read
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

int main() {
	std::string response = readFile("./testing-socket/data.html");
	// Create a socket (IPv4, TCP)
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		std::cout << "Failed to create socket. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	// Listen to port 9999 on any address
	sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = INADDR_ANY;
	sockaddr.sin_port = htons(9999); // htons is necessary to convert a number to
									// network byte order
	if (bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
		std::cout << "Failed to bind to port 9999. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	// Start listening. Hold at most 10 connections in the queue
	while (1)
	{

		if (listen(sockfd, 10) < 0) {
			std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
			exit(EXIT_FAILURE);
		}

		// Grab a connection from the queue
		unsigned long addrlen = sizeof(sockaddr);
		int connection = accept(sockfd, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
		if (connection < 0) {
			std::cout << "Failed to grab connection. errno: " << errno << std::endl;
			exit(EXIT_FAILURE);
		}

		// Read from the connection
		char buffer[100000];
		ssize_t bytesRead = read(connection, buffer, 100000);
		std::cout << "The message was: " << buffer;

		// Send a message to the connection
		// std::string response = "Good talking to you\n";
		send(connection, response.c_str(), response.size(), 0);

		// Close the connections
		close(connection);
	}
	close(sockfd);
}