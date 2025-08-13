NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Iinclude
LIBS = -lreadline

SRCS= \
	src/builtin/ft_cd.c \
	src/builtin/ft_cd_utils.c \
	src/builtin/ft_echo.c \
	src/builtin/ft_env.c \
	src/builtin/ft_exit_atoi.c \
	src/builtin/ft_exit.c \
	src/builtin/ft_export.c \
	src/builtin/ft_pwd.c \
	src/builtin/ft_unset.c \
	src/doll/doll_open.c \
	src/doll/doll_open_count_size.c \
	src/doll/doll_open_input_string.c \
	src/doll/doll_open_input_string_utils.c \
	src/doll/ft_doll.c \
	src/envp/add_envp.c \
	src/envp/append_envp.c \
	src/envp/delete_envp.c \
	src/envp/envp.c \
	src/envp/free_envp.c \
	src/execve/execve_builtin.c \
	src/execve/execve_cmd.c \
	src/execve/execve_free_op.c \
	src/execve/execve_input.c \
	src/execve/execve_main.c \
	src/execve/execve_op1.c \
	src/execve/execve_output.c \
	src/execve/execve_path.c \
	src/execve/execve_pipe.c \
	src/execve/execve_redir.c \
	src/execve/execve_utils.c \
	src/main/main.c \
	src/main/main_quort.c \
	src/main/main_signal.c \
	src/main/main_syntax.c \
	src/main/main_utils.c \
	src/make_cmd_cnk/heredoc.c \
	src/make_cmd_cnk/make_cmd_cnk.c \
	src/make_cmd_cnk/make_cmd_cnk_prepare.c \
	src/make_cmd_cnk/make_cmd_cnk_redir.c \
	src/make_cmd_cnk/minishell_heredoc_loop.c \
	src/parser/add_status_each_token.c \
	src/parser/count_token.c \
	src/parser/count_token_utils.c \
	src/parser/parser.c \
	src/parser/quort_check.c \
	src/parser/quort_check_utils.c \
	src/parser/quort_error.c \
	src/parser/split_space.c \
	src/parser/split_symbol_s_quort.c \
	src/parser/split_symbol_w_quort.c \
	src/parser/split_token.c \
	src/utils/ft_isdigit.c \
	src/utils/ft_itoa.c \
	src/utils/ft_split.c \
	src/utils/ft_strchr.c \
	src/utils/ft_strcmp.c \
	src/utils/ft_strcpy.c \
	src/utils/ft_strdup.c \
	src/utils/ft_strjoin.c \
	src/utils/ft_strlen.c \
	src/utils/ft_strncmp.c \
	src/utils/get_next_line.c \
	src/utils/get_next_line_utils.c \




OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
