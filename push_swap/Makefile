NAME=push_swap

CC=cc
CFLAGS=-Wall -Wextra -Werror

SRCS=

OBJS=$(SRCS:.c=.o)

HEADER=push_swap.h

all:$(NAME)

$(NAME):$(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all


.PHONY: all clean fclean re
