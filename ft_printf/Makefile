NAME=libftprintf.a

CC=cc
CFLAGS=-Wall -Wextra -Werror

SRCS=ft_printf.c \
		ft_printf_utils1.c \
		ft_printf_utils2.c


OBJS = $(SRCS:.c=.o)


HEADER = ft_printf.h

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all


.PHONY: all clean fclean re
