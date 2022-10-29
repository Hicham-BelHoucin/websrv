# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 10:20:36 by hbel-hou          #+#    #+#              #
#    Updated: 2022/10/26 16:19:47 by obeaj            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Webserv

CC = c++

# CFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = src/parsing/parsing.cpp src/request/request.cpp src/response/response.cpp src/server/createSocket.cpp src/server/server.cpp src/webserv.cpp src/utils/utils.cpp

SRCOBJ = $(SRCS:.cpp=.o)

INCLUDE = include/createSocket.hpp include/parsing.hpp include/request.hpp include/server.hpp include/webServ.hpp include/utils.h

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