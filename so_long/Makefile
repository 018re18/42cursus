NAME=so_long

CC=cc
CFLAGS=-Wall -Wextra -Werror

SRCS=

OBJS=$(SRCS:.c=.o)

HEADER=so_long.h

all:$(NAME)

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all


.PHONY: all clean fclean re
