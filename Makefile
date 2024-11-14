# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/13 18:06:35 by dyao              #+#    #+#              #
#    Updated: 2024/11/14 18:58:20 by dyao             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo
SRCS			=	srcs/input.c \
					srcs/main.c \
					srcs/start.c \
					srcs/tool.c \
					srcs/check.c \
					srcs/print.c

OBJS			= ${SRCS:.c=.o}
CFLAGS 			= -Wall -Wextra -Werror -I -g #-pthread
CC				= cc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY:	all clean fclean re