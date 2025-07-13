/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:20:50 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/13 15:17:43 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

extern struct sigaction	g_sa;

typedef int				t_fd;

enum
{
	FALSE,
	TRUE
};
// enum {cmd ,option,pipe,input,output,here_doc,add};

typedef struct s_line_status
{
	char				*string;
	int					mode;

}						t_line_status;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND
}						t_token_type;

enum
{
	cmd,
	pipe_status,
	input,
	output,
	heredoc,
	add
};

typedef struct s_token
{
	char				*str;
	t_token_type		type;
}						t_token;

typedef struct s_cmd_redir
{
	int					type;
	char				*filename;
	char				*limiter;
}						t_cmd_redir;

typedef struct s_cmd_cnk
{
	char				**cmd;
	t_cmd_redir			*redir;
	int					redirect;
}						t_cmd_cnk;

typedef struct s_envp_data
{
	char				**envp;
	int					envp_count;
	int					envp_volume;
	// char	**key;

}						t_envp_data;

typedef struct s_make_cnk_index
{
	int					line_index;
	int					op_index;
	int					cmd_index;
	int					redir_index;
	int					heredoc_num;
}						t_make_cnk_index;

typedef struct s_builtin_exit_num
{
	int					index;
	int					sign;
	long long			tmp_num;
	long long			arg_num;

}						t_builtin_exit_num;

typedef struct s_execve_num
{
	struct sigaction	saved;
	struct sigaction	saved_quit;
	struct sigaction	g_sa;
	int					index;
	int					operate_count;
	int					exit_status;
	int					pipe_fd[2];
	int					tmp_fd;
	pid_t				last_pid;
}						t_execve_num;

char					**ft_split(const char *s, char c);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strcpy(char *dest, const char *src);
size_t					ft_strlen(const char *c);
char					*ft_strdup(const char *s);
int						ft_strcmp(const char *s1, const char *s2);
t_token					*add_status_each_token(char **splited_token,
							int token_count);
int						check_syntax(t_token *tokens);
int						count_all_cmd(t_token *line);
int						execve_main(t_token *line, t_envp_data *my_envp,
							int exit_status);
// char					*make_here_doc(t_cmd_cnk *operate, int place);
int						ft_strcmp(const char *s1, const char *s2);
t_cmd_cnk				*make_cmd_cnk(t_token *line, int operate_count);
char					*make_here_doc(t_cmd_cnk *operate, int place,
							int redir_place);
char					**split_kai(char *string, char **splited_pipe);
char					*quort_check(char *string);
int						count_token(char *string);
t_envp_data				envp_init(char **envp);
char					*ft_doller(char *token, t_envp_data envp_data);
char					**doller_open(char **splited_token,
							t_envp_data envp_data, int exit_status);
int						ft_echo(char **cmd_and_option);
int						ft_pwd(t_envp_data *envp_data);
int						ft_exit(t_cmd_cnk *operate, int place,
							t_execve_num *num, t_envp_data *envp_data);
char					*ft_itoa(int n);
int						quort_error(char *string);
void					ctr_c_handler(int signum);
void					ctr_back_slash_handler(int signum);
int						ft_cd(t_envp_data *envp_data, char **args);
char					*ft_strjoin(char const *s1, char const *s2);
t_envp_data				add_envp(t_envp_data prev_envp_data, char *key_and);
t_envp_data				delete_envp(t_envp_data prev_envp_data, char *key);
t_envp_data				ft_env(t_envp_data envp_data, t_execve_num *num,
							char **cmd);
int						ft_export(char **args, t_envp_data *envp_data);
t_envp_data				ft_unset(char **args, t_envp_data envp_data);
char					*set_key(char *key_and);
t_envp_data				append_envp(t_envp_data prev_envp_data, char *key_and);
t_envp_data				envp_line_up(t_envp_data envp_data);
void					free_envp(t_envp_data *envp_data);
void					free_operate(t_cmd_cnk *operate, int operate_count);
int						count_arg(char **arg);
int						cmp_key(const char *key, const char *str);

// t_token	*input_cmd_check(t_token *result, int token_count);

#endif
