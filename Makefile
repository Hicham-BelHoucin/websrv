# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 10:20:36 by hbel-hou          #+#    #+#              #
#    Updated: 2022/11/21 11:02:38 by obeaj            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Webserv

CC = c++

CFLAGS = -g


SRCS = src/parsing/parsing.cpp \
	   src/request/request.cpp \
	   src/utils/utils.cpp \
	   src/server/createSocket.cpp \
	   src/server/server.cpp \
	   src/webserv.cpp \
	   src/main.cpp \
	   src/response/response.cpp \
	   src/client/client.cpp \
	   src/cgi/cgi.cpp

SRCOBJ = $(SRCS:.cpp=.o)

INCLUDE =	include/createSocket.hpp \
			include/parsing.hpp \
			include/request.hpp \
			include/server.hpp \
			include/webServ.hpp \
			include/utils.h \
			include/response.hpp \
			include/ResponseUtils.h \
			include/client.hpp \
			include/cgi.hpp

all: $(NAME)

$(NAME) : $(INCLUDE) $(SRCOBJ)
	$(CC) $(CFLAGS) -I include $(SRCS) -o $(NAME) -g

%.o : %.cpp $(INCLUDE)
	$(CC) $(CFLAGS) -I include -o $@  -c $< -g

clean:
	@rm -f $(SRCOBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all