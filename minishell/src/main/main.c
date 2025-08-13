/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:13:40 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/20 14:27:31 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_received_signal = 0;

static int	skip_line_condition(char *line, int *exit_status)
{
	if (g_received_signal == SIGINT)
	{
		*exit_status = 130;
		if (line[0] == '\0')
		{
			g_received_signal = 0;
			free(line);
			return (FALSE);
		}
	}
	if (line == NULL)
	{
		printf("exit\n");
		return (FALSE);
	}
	g_received_signal = 0;
	if (line[0] == '\0' || space_check(line) == 0)
	{
		free(line);
		return (FALSE);
	}
	return (TRUE);
}

static int	readline_exit_ctl(int exit_status, t_main *m)
{
	if (exit_status == 130)
	{
		free(m->line);
		return (FALSE);
	}
	return (TRUE);
}

static int	readline_loop_body(t_main *m, int *exit_status,
		t_envp_data *envp_data)
{
	t_token	*token_and_status;

	if (!skip_line_condition(m->line, exit_status))
		return (FALSE);
	if (*m->line)
		add_history(m->line);
	if (!quort_error(m->line))
	{
		free(m->line);
		return (FALSE);
	}
	if (!readline_loop_syntax(m, *envp_data, exit_status))
		return (FALSE);
	if (!readline_loop_quort(&token_and_status, m, exit_status))
		return (FALSE);
	*exit_status = execve_main(token_and_status, envp_data, *exit_status);
	if (!readline_exit_ctl(*exit_status, m))
		return (FALSE);
	free(m->line);
	return (TRUE);
}

static void	readline_loop(int *exit_status, t_envp_data *envp_data)
{
	t_main	m;

	m.line = readline("minishell> ");
	while (m.line != NULL)
	{
		if (!readline_loop_body(&m, exit_status, envp_data))
		{
			m.line = readline("minishell> ");
			continue ;
		}
		m.line = readline("minishell> ");
	}
}

int	main(int argc, char **argv, char **envp)
{
	int			exit_status;
	t_envp_data	envp_data;

	if (argc > 1)
		return (1);
	if (argv == NULL)
	{
		return (1);
	}
	exit_status = 0;
	set_signal_main();
	envp_data = envp_init(envp);
	readline_loop(&exit_status, &envp_data);
	free_envp(&envp_data);
	return (exit_status);
}
