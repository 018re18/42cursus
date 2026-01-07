# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/20 00:00:00 by rookuma           #+#    #+#              #
#    Updated: 2025/12/07 16:40:51 by rookuma          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pthread

SRCS	= main.c \
		  init.c \
		  utils1.c \
		  utils2.c \
		  state.c \
		  loop.c \
		  destroy.c \
		  watcher.c

OBJS	= $(SRCS:.c=.o)

HEADER	= philo.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
