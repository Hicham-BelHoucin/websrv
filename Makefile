# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 10:20:36 by hbel-hou          #+#    #+#              #
#    Updated: 2022/11/19 15:41:28 by hbel-hou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Webserv

CC = c++

CFLAGS = -g 

OBEJECTDIR = ./objects

SRCS =  src/client/client.cpp \
		src/parsing/parsing.cpp \
		src/request/request.cpp \
		src/response/response.cpp \
		src/server/createSocket.cpp \
		src/server/server.cpp \
		src/utils/utils.cpp \
		src/main.cpp \
		src/webserv.cpp \

SRCOBJ = $(SRCS:.cpp=.o)
SRCOBJ := $(addprefix $(OBEJECTDIR)/, $(SRCOBJ))

INCLUDE = include/createSocket.hpp include/parsing.hpp include/request.hpp include/server.hpp include/webServ.hpp include/utils.h include/response.hpp include/ResponseUtils.h

all: $(OBEJECTDIR) $(NAME)

$(NAME) : $(INCLUDE) $(SRCOBJ)
	$(CC) $(CFLAGS) -I include $(SRCS) -o $(NAME)

$(OBEJECTDIR) : 
	@mkdir -p $(OBEJECTDIR)/src/parsing/
	@mkdir -p $(OBEJECTDIR)/src/client/
	@mkdir -p $(OBEJECTDIR)/src/request/
	@mkdir -p $(OBEJECTDIR)/src/response/
	@mkdir -p $(OBEJECTDIR)/src/server/
	@mkdir -p $(OBEJECTDIR)/src/server/
	@mkdir -p $(OBEJECTDIR)/src/utils/
	@mkdir -p $(OBEJECTDIR)/src/

$(OBEJECTDIR)/%.o : %.cpp $(INCLUDE)
	$(CC) $(CFLAGS) -I include  -o $@  -c $<

clean:
	@rm -rf $(SRCOBJ)
	@rm -rf $(OBEJECTDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all