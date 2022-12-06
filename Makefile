# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 10:20:36 by hbel-hou          #+#    #+#              #
#    Updated: 2022/12/05 17:28:07 by hbel-hou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Webserv

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

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

INCLUDE =	include/ResponseUtils.h \
			include/cgi.hpp \
			include/client.hpp \
			include/common.h \
			include/createSocket.hpp \
			include/parsing.hpp \
			include/request.hpp \
			include/response.hpp \
			include/server.hpp \
			include/utils.h \
			include/webServ.hpp \


all: $(NAME)

$(NAME) : $(INCLUDE) $(SRCOBJ)
	$(CC) $(CFLAGS) -I include $(SRCS) -o $(NAME)

%.o : %.cpp $(INCLUDE)
	$(CC) $(CFLAGS) -I include -o $@  -c $<

$(OBEJECTDIR)/%.o : %.cpp $(INCLUDE)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I include  -o $@  -c $<

clean:
	@rm -rf $(SRCOBJ)
	@rm -rf $(OBEJECTDIR)
	@rm -f webserver.logs

fclean: clean
	@rm -f $(NAME)

re: fclean all