/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:13:40 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/13 16:53:47 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
// ヘッダーの前かどこかにこれを追加
void rl_replace_line(const char *text, int clear_undo);
#include <signal.h>
#include <unistd.h>

// struct sigaction	sa_int;
volatile sig_atomic_t	g_received_signal = 0;

void	ctr_c_handler(int signum)
{
	g_received_signal = signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ctr_back_slash_handler(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	space_check(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0' && string[i] != '\n')
	{
		if (string[i] != ' ' && string[i] != 9)
			return (1);
		i++;
	}
	return (0);
}

char	**skip_space(char **string, int *token_count)
{
	int		i;
	int		j;
	char	**result;

	i = 0;
	j = 0;
	if (space_check(string[i]) == 0)
	{
		i++;
	}
	else
	{
		return (string);
	}
	while (space_check(string[i]) == 0 || string[i][0] == '|')
	{
		i++;
	}
	*token_count = *token_count - i;
	// if(i == 0){
	// 	return (string);
	// }
	while (string[j] != NULL)
	{
		j++;
	}
	result = (char **)malloc(sizeof(char *) * j - i + 1);
	j = 0;
	while (string[i] != NULL)
	{
		result[j] = ft_strdup(string[i]);
		j++;
		i++;
	}
	result[j] = NULL;
	i = 0;
	while (string[i] != NULL)
	{
		free(string[i]);
		i++;
	}
	free(string);
	return (result);
}

int	main(int argc, char **argv, char **envp)
{
	char				*line;
	int					exit_status;
	int					i;
	char				*string;
	int					token_count;
	char				**splited_token;
	char				*prev_pwd;
	t_token				*token_and_status;
	t_envp_data			envp_data;
	struct sigaction	g_sa;
	int					flag;
	int					pipe_flag;
	int					j;
	char				*tmp;

	exit_status = 0;
	// char	**line_splietd;
	i = 0;
	// signal(SIGINT, ctr_c_handler);
	// signal(SIGQUIT, SIG_IGN);
	g_sa.sa_handler = ctr_c_handler;
	sigemptyset(&g_sa.sa_mask);
	g_sa.sa_flags = 0;
	sigaction(SIGINT, &g_sa, NULL);
	g_sa.sa_handler = ctr_back_slash_handler;
	sigemptyset(&g_sa.sa_mask);
	g_sa.sa_flags = 0;
	sigaction(SIGQUIT, &g_sa, NULL);
	envp_data = envp_init(envp);
	while ((line = readline("minishell> ")) != NULL)
	{
		if (g_received_signal == SIGINT)
		{
			exit_status = 130;
			if (line[0] == '\0')
			{
				g_received_signal = 0;
				free(line);
				continue ;
			}
		}
		if (line == NULL)
		{
			printf("exit\n");
		}
		// if (ft_strcmp(line, "") == 0)
		// {
		// 	continue ;
		// }
		g_received_signal = 0;
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		if (space_check(line) == 0)
		{
			continue ;
		}
		if (*line)
			add_history(line);
		// i++;
		// string = NULL;
		// string = quort_check(line);
		if (quort_error(line) == FALSE)
		{
			continue ;
		}
		token_count = count_token(line); // string > line
		// printf("%d\n",token_count);
		splited_token = (char **)malloc(sizeof(char *) * (token_count + 1));
		splited_token = split_kai(line, splited_token); // string > line
		splited_token = doller_open(splited_token, envp_data, exit_status);
		// while (splited_token[i])
		// {
		// 	i++;
		// }
		flag = 1;
		pipe_flag = 0;
		if ((space_check(splited_token[0]) == 0))
		{
			flag = 0;
			i = 1;
			while (splited_token[i] != NULL)
			{
				if (!(space_check(splited_token[i]) == 0
						|| splited_token[i][0] == '|'))
					flag = 1;
				if (splited_token[i][0] == '|' && pipe_flag == 1)
				{
					write(2,
						"minishell: syntax error near unexpected token `|'\n",
						51);
				}
				if (splited_token[i][0] == '|')
				{
					pipe_flag = 1;
				}
				i++;
			}
			if (splited_token[i - 1][0] == '|' && pipe_flag == 1)
			{
				write(2, "minishell: syntax error near unexpected token `|'\n",
					51);
			}
		}
		if (flag == 0)
		{
			for (int i = 0; i < token_count; i++)
			{
				free(splited_token[i]);
			}
			free(splited_token);
			free(line);
			continue ;
		}
		splited_token = skip_space(splited_token, &token_count);
		i = 0;
		while (splited_token[i])
		{
			splited_token[i] = quort_check(splited_token[i]);
			i++;
		}
		i = 0;
		token_and_status = add_status_each_token(splited_token, token_count);
		i = 0;
		// while (token_and_status[i].str != NULL)
		// {
		// 	printf("%s\n", token_and_status[i].str);
		// 	// free(token_and_status[i].str);
		// 	i++;
		// }
		for (int i = 0; i < token_count; i++)
		{
			free(splited_token[i]);
		}
		free(splited_token);
		if (check_syntax(token_and_status) == 1)
		{
			exit_status = 2;
			i = 0;
			while (token_and_status[i].str != NULL)
			{
				free(token_and_status[i].str);
				i++;
			}
			free(token_and_status);
			free(line);
			continue ;
		}
		// envp_data = envp_init(envp);
		exit_status = execve_main(token_and_status, &envp_data, exit_status);
		if(exit_status==130)
		{
			free(line);
			continue ;
		}
		
		// if (token_and_status)
		// {
		// 	while (token_and_status[i].str != NULL)
		// 	{
		// 		free(token_and_status[i].str);
		// 		i++;
		// 	}
		// 	free(token_and_status);
		// }
		// printf("%d", exit_status);
		free(line);
	}
	// i = 0;
	free_envp(&envp_data);
	// free(line);
	return (exit_status);
}
