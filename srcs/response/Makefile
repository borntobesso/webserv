# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/03 14:56:07 by ntan              #+#    #+#              #
#    Updated: 2022/12/14 15:38:28 by ntan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	response_test.cpp\
					Context.cpp\
					../config/Keys.cpp\
					../config/Config.cpp\
					../config/Server.cpp\
					../config/Location.cpp\
					../client/Request.cpp\
					Status.cpp\
					Response.cpp
				
OBJS			= 	$(SRCS:.cpp=.o)

DEPENDS 		= 	$(patsubst %.cpp,%.d,$(SRCS))			
CC				=	c++
RM				=	rm -f
CFLAGS			=	-Wall -Wextra -Werror -g -std=c++98
NAME			=	config_test

all:			$(NAME)

%.o:%.tpp
				$(CC) $(CFLAGS) -I. -c $< -o $@ -E

%.o:%.cpp
				$(CC) $(CFLAGS) -MMD -MP -I. -c $< -o $@ -E

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) -I. $(SRCS) -o $(NAME)

-include $(DEPENDS)

clean:
				$(RM) $(OBJS) $(DEPENDS)

fclean:
				$(RM) $(OBJS) $(DEPENDS)
				$(RM) $(NAME)

re:				fclean all
