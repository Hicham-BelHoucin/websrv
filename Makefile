# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 10:20:36 by hbel-hou          #+#    #+#              #
#    Updated: 2022/12/03 23:50:38 by obeaj            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Webserv

CC = c++

CFLAGS = 

OBEJECTDIR = .objects

SRCS = src/parsing/parsing.cpp \
	   src/server/createSocket.cpp \
	   src/server/server.cpp \
	   src/webserv.cpp \
	   src/main.cpp \
	   src/client/client.cpp \
	   src/cgi/cgi.cpp \
	   src/utils/utils.cpp \
	   src/response/response.cpp \
	   src/request/request.cpp \

SRCOBJ = $(SRCS:.cpp=.o)
SRCOBJ := $(addprefix $(OBEJECTDIR)/, $(SRCOBJ))

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

$(OBEJECTDIR)/%.o : %.cpp $(INCLUDE)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I include  -o $@  -c $< -g

clean:
	@rm -rf $(SRCOBJ)
	@rm -rf $(OBEJECTDIR)
	@rm -f webserver.logs

fclean: clean
	@rm -f $(NAME)

re: fclean all