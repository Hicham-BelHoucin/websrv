# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 10:20:36 by hbel-hou          #+#    #+#              #
#    Updated: 2022/11/02 11:32:00 by hbel-hou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Webserv

CC = c++

# CFLAGS = -g

SRCS = src/parsing/parsing.cpp src/request/request.cpp src/utils/utils.cpp src/response/response.cpp src/server/createSocket.cpp src/server/server.cpp src/webserv.cpp src/main.cpp

SRCOBJ = $(SRCS:.cpp=.o)

INCLUDE = include/createSocket.hpp include/parsing.hpp include/request.hpp include/server.hpp include/webServ.hpp

all: $(NAME)

$(NAME) : $(INCLUDE) $(SRCOBJ)
	$(CC) $(CFLAGS) -I include $(SRCS) -o $(NAME)

%.o : %.cpp $(INCLUDE)
	$(CC) $(CFLAGS) -I include -o $@  -c $<

clean:
	@rm -f $(SRCOBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all