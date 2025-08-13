/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execve_op1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:32:55 by rookuma           #+#    #+#             */
/*   Updated: 2025/07/19 17:33:22 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execve_1cmd(t_envp_data *my_envp, t_cmd_cnk *operate)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (operate[0].redirect > 0)
	{
		if (!minishell_redirect_loop(operate, 0))
			return (FALSE);
	}
	minishell_execve(operate, 0, my_envp->envp);
	return (FALSE);
}

int	execve_cmd_single(t_envp_data *my_envp, t_cmd_cnk *operate,
		t_execve_num *num)
{
	pid_t	pid;

	if (check_builtin(operate[0].cmd[0]))
		return (execve_buitlin_1cmd(my_envp, operate, num));
	pid = fork();
	if (pid < 0)
		return (perror_free(operate, "fork", 1));
	if (pid == 0)
	{
		if (!execve_1cmd(my_envp, operate))
			exit(EXIT_FAILURE);
	}
	waitpid(pid, &num->exit_status, 0);
	if (WIFSIGNALED(num->exit_status) && WTERMSIG(num->exit_status) == SIGINT)
		write(1, "\n", 1);
	free_operate(operate, 1);
	sigaction(SIGINT, &num->saved, NULL);
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(num->exit_status))
		return (WEXITSTATUS(num->exit_status));
	if (WIFSIGNALED(num->exit_status))
		return (128 + WTERMSIG(num->exit_status));
	return (EXIT_FAILURE);
}
