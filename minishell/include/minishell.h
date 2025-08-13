/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:20:50 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/21 14:31:15 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _DEFAULT_SOURCE

# include "get_next_line.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_received_signal;

typedef int						t_fd;

enum
{
	FALSE,
	TRUE
};

typedef struct s_line_status
{
	char						*string;
	int							mode;

}								t_line_status;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND
}								t_token_type;

enum
{
	cmd,
	pipe_status,
	input,
	output,
	heredoc,
	add
};

typedef struct s_main
{
	char						*line;
	int							token_count;
	char						**splited_token;
}								t_main;

typedef struct s_token
{
	char						*str;
	t_token_type				type;
}								t_token;

typedef struct s_cmd_redir
{
	int							type;
	char						*filename;
	char						*limiter;
}								t_cmd_redir;

typedef struct s_cmd_cnk
{
	char						**cmd;
	t_cmd_redir					*redir;
	int							redirect;
}								t_cmd_cnk;

typedef struct s_envp_data
{
	char						**envp;
	int							envp_count;
	int							envp_volume;

}								t_envp_data;

typedef struct s_make_cnk_index
{
	int							line_index;
	int							op_index;
	int							cmd_index;
	int							redir_index;
	int							heredoc_num;
}								t_make_cnk_index;

typedef struct s_builtin_exit_num
{
	int							index;
	int							sign;
	long long					tmp_num;
	long long					arg_num;

}								t_builtin_exit_num;

typedef struct s_heredoc_str
{
	char						*str;
	int							len;
}								t_heredoc_str;

typedef struct s_execve_num
{
	struct sigaction			saved;
	struct sigaction			saved_quit;
	struct sigaction			g_sa;
	int							index;
	int							operate_count;
	int							exit_status;
	int							pipe_fd[2];
	int							tmp_fd;
	pid_t						last_pid;
	int							save_stdin;
	int							save_stdout;
}								t_execve_num;

typedef struct s_count_token
{
	int							i;
	int							s_quarto_flag;
	int							w_quarto_flag;
	int							count;
	int							split_flag;
	int							token_count;
}								t_count_token;

typedef struct s_doller_open
{
	int							i;
	int							s_quort_flag;
	int							w_quort_flag;
	char						*doller_word;
	char						*opened_doller_word;
	char						*result;
	int							char_count;
	int							j;
	int							k;
	char						*string_exit_status;
	char						*result_join;
	char						stop_flag;
	int							stop_flag_int;
	char						*suffix;
}								t_doller_open;

typedef struct s_split
{
	int							i;
	int							s_quarto_flag;
	int							w_quarto_flag;
	int							count;
	int							split_flag;
	int							token_count;
	int							count_flag;
	int							splited_pipe_count;
}								t_split;

typedef struct s_quort_check
{
	char						*result;
	int							count_quort;
	int							w_quarto_flag;
	int							s_quarto_flag;
	int							i;
}								t_quort_check;

typedef struct s_delete_envp
{
	t_envp_data					new_envp_data;
	int							i;
	int							j;
	int							delete_flag;
}								t_delete_envp;

typedef struct s_add_envp
{
	t_envp_data					new_envp_data;
	int							i;
	int							j;
	char						*key;
	char						key_flag;

}								t_add_envp;

typedef struct s_append_envp
{
	t_envp_data					new_envp_data;
	int							i;
	int							j;
	char						*key;
	int							key_flag;
	char						*tmp;
}								t_append_envp;

typedef struct s_doll
{
	char						*key;
	char						*result;
	int							doller_flag;
	int							i;
	int							j;
	int							key_char_count;
	int							envp_count;
	int							flag;

}								t_doll;

typedef struct s_quort_error
{
	int							i;
	int							s_quort_count;
	int							w_quort_count;
	int							s_quort_count_flag;
	int							w_quort_count_flag;
}								t_quort_error;
// add_status_each_token.c

// copy.c

// envp.c

// execve_builtin.c
int								check_builtin(const char *cmd);
int								builtin_execve(t_cmd_cnk *operate, int place,
									t_envp_data *envp, t_execve_num *num);
int								builtin_restore_free(int save_stdin,
									int save_stdout, t_cmd_cnk *operate,
									int status);
int								execve_buitlin_1cmd(t_envp_data *my_envp,
									t_cmd_cnk *operate, t_execve_num *num);

// execve_cmd.c
void							minishell_execve(t_cmd_cnk *operate, int place,
									char **envp);

// execve_free_op.c
void							free_operate(t_cmd_cnk *operate,
									int operate_count);

// execve_input.c
t_fd							input_file(t_cmd_cnk *operate, int place,
									int redir_place);
t_fd							input_heredoc(char *filename);

// execve_main.c
int								execve_main(t_token *line, t_envp_data *my_envp,
									int exit_status);

// execve_op1.c
int								execve_1cmd(t_envp_data *my_envp,
									t_cmd_cnk *operate);
int								execve_cmd_single(t_envp_data *my_envp,
									t_cmd_cnk *operate, t_execve_num *num);

// execve_output.c
t_fd							output_file(t_cmd_cnk *operate, int place,
									int redir_place);
t_fd							output_append(t_cmd_cnk *operate, int place,
									int redir_place);

// execve_path.c
int								get_path(char *cmd, char **envp, char **path);

// execve_pipe.c
void							execve_1cmd_pipe(t_envp_data *my_envp,
									t_cmd_cnk *operate, t_execve_num *num,
									int place);
int								execve_pipeline(t_envp_data *my_envp,
									t_cmd_cnk *operate, t_execve_num *num);

// execve_redir.c
int								minishell_redirect_loop(t_cmd_cnk *operate,
									int place);

// execve_utils.c
int								count_all_cmd(t_token *line);
int								write_cmd_error(t_token *line,
									t_execve_num *num);
int								perror_free(t_cmd_cnk *operate, char *err,
									int operate_count);
int								check_directory(char *path);

// free_envp.c

// ft_cd.c
int								ft_cd(t_envp_data *envp_data, char **args);

// ft_cd_utils.c
t_envp_data						ft_cd_help(t_envp_data envp_data, char **args,
									int *exit_status);

// ft_doller.c

// ft_echo.c
int								ft_echo(char **cmd_and_option);

// ft_env.c
t_envp_data						ft_env(t_envp_data envp_data, t_execve_num *num,
									char **cmd);

// ft_exit_atoi.c
void							free_cnk_envp(t_cmd_cnk *operate,
									t_envp_data *envp_data);
long long						exit_atoi(t_cmd_cnk *operate, int place,
									t_execve_num *num, t_envp_data *envp_data);

// ft_exit.c
int								count_arg(char **arg);
int								ft_exit(t_cmd_cnk *operate, int place,
									t_execve_num *num, t_envp_data *envp_data);

// ft_export.c
int								ft_export(char **args, t_envp_data *envp_data);

// ft_isdigit.c
int								ft_isdigit(int c);

// ft_itoa.c
char							*ft_itoa(int n);

// ft_pwd.c
int								ft_pwd(void);

// ft_split.c
char							**ft_split(const char *s, char c);

//  ft_strchr.c
char							*ft_strchr(const char *s, int c);

//  ft_strcmp.c
int								ft_strcmp(const char *s1, const char *s2);

//  ft_strcpy.c
char							*ft_strcpy(char *dest, const char *src);

// ft_strdup.c
char							*ft_strdup(const char *s);

// ft_strjoin.c
char							*ft_strjoin(char const *s1, char const *s2);

// ft_strlen.c
int								ft_strlen(const char *c);

// ft_strncmp.c
int								ft_strncmp(const char *s1, const char *s2,
									size_t n);

//  ft_unset.c
t_envp_data						ft_unset(char **args, t_envp_data envp_data);

// heredoc_loop.c
int								here_doc_loop(t_cmd_cnk *operate,
									t_make_cnk_index *i, int fd);

// heredoc.c
int								make_here_doc(t_cmd_cnk *operate,
									t_make_cnk_index *i, int *status);

// main_quort.c
int								readline_loop_quort(t_token **token_and_status,
									t_main *m, int *exit_status);
// main_signal.c
void							set_signal_main(void);

// main.syntax.c
int								readline_loop_syntax(t_main *m,
									t_envp_data envp_data, int *exit_status);

// main_utils.c
int								space_check(char *string);
void							free_string(char **string);
char							**skip_space(char **string, int *token_count);
void							free_splited_token(char **splited_token,
									int token_count);
void							write_syntax_error(void);

// make_cmd_cnk_prepare.c
int								operate_init(t_token *line, t_cmd_cnk *operate,
									t_make_cnk_index *i);

// make_cmd_cnk_redir.c
int								cnk_cmd(t_token *line, t_cmd_cnk *operate,
									t_make_cnk_index *i, int *status);
int								cnk_input(t_token *line, t_cmd_cnk *operate,
									t_make_cnk_index *i, int *status);
int								cnk_output(t_token *line, t_cmd_cnk *operate,
									t_make_cnk_index *i, int *status);
int								cnk_append(t_token *line, t_cmd_cnk *operate,
									t_make_cnk_index *i, int *status);
int								cnk_here_doc(t_token *line, t_cmd_cnk *operate,
									t_make_cnk_index *i, int *status);

// make_cmd_cnk1.c
t_cmd_cnk						*make_cmd_cnk(t_token *line, int operate_count,
									int *status);

t_token							*add_status_each_token(char **splited_token,
									int token_count);
int								check_syntax(t_token *tokens);
char							**split_kai(char *string, char **splited_pipe);
char							*quort_check(char *string);
int								count_token(char *string);
t_envp_data						envp_init(char **envp);
char							*ft_doller(char *token, t_envp_data envp_data);
char							**doller_open(char **splited_token,
									t_envp_data envp_data, int exit_status);
int								quort_error(char *string);
t_envp_data						add_envp(t_envp_data prev_envp_data,
									char *key_and);
t_envp_data						delete_envp(t_envp_data prev_envp_data,
									char *key);
char							*set_key(char *key_and);
t_envp_data						append_envp(t_envp_data prev_envp_data,
									char *key_and);
t_envp_data						envp_line_up(t_envp_data envp_data);
void							free_envp(t_envp_data *envp_data);
int								cmp_key(const char *key, const char *str);

int								count_token_help(char *string,
									t_count_token *token_info);

void							doller_open_count_size(char *string,
									t_envp_data envp_data, int exit_status,
									t_doller_open *doller);

int								is_al_num(char c);
int								search_envp(char *key, t_envp_data envp_data);
void							doller_open_input(char *string,
									t_envp_data envp_data, int exit_status,
									t_doller_open *doller);
int								doller_open_input_string_doll_only(\
	t_doller_open *doller);
int								doller_open_input_string_doll_and_q(int \
exit_status, t_doller_open *doller);
char							*doller_open_help(char *string, t_envp_data \
	envp_data, int exit_status);
int								split_space(t_split *split, char **splited_pipe,
									char *string);
int								split_smbol_s(t_split *split,
									char **splited_pipe, char *string);
int								split_smbol_w(t_split *split,
									char **splited_pipe, char *string);
char							*malloc_and_push(char *string, int i,
									int count_flag);
void							quort_check_make_result(char *string,
									t_quort_check *quort);

#endif
