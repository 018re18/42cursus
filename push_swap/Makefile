NAME=push_swap

CC=cc
CFLAGS=-Wall -Wextra -Werror

SRCS=push_swap_check.c \
	push_swap_main.c \
	push_swap_op1.c \
	push_swap_op2.c \
	push_swap_op3.c \
	push_swap_slice1.c \
	push_swap_slice2.c \
	push_swap_slice3.c \
	push_swap_sort1.c \
	push_swap_sort2.c \
	push_swap_utils1.c

OBJS=$(SRCS:.c=.o)

HEADER=push_swap.h

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
