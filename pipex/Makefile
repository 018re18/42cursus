NAME=pipex

CC=cc
CFLAGS=-Wall -Wextra -Werror

SRCS=get_next_line.c  \
	get_next_line_utils.c \
	pipex_loop1_.c \
	pipex_loop2_.c \
	pipex_main.c \
	pipex_utils1.c \
	pipex_utils2.c \
	split.c

OBJS=$(SRCS:.c=.o)

HEADER=pipex.h

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

bonus: all

.PHONY: all clean fclean re bonus
