/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:21:06 by rookuma           #+#    #+#             */
/*   Updated: 2025/07/19 18:34:14 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_pipe_fd(t_execve_num *num, int place)
{
	if (num->tmp_fd != -1)
	{
		if (dup2(num->tmp_fd, STDIN_FILENO) == -1)
			perror("dup2");
		close(num->tmp_fd);
	}
	if (place != num->operate_count - 1)
	{
		if (dup2(num->pipe_fd[1], STDOUT_FILENO) == -1)
			perror("dup2");
		close(num->pipe_fd[1]);
		close(num->pipe_fd[0]);
	}
}

void	execve_1cmd_pipe(t_envp_data *my_envp, t_cmd_cnk *operate,
		t_execve_num *num, int place)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	set_pipe_fd(num, place);
	if (operate[place].redirect > 0)
	{
		if (!minishell_redirect_loop(operate, place))
			exit(EXIT_FAILURE);
	}
	if (check_builtin(operate[place].cmd[0]))
	{
		num->exit_status = builtin_execve(operate, place, my_envp, num);
		exit(num->exit_status);
	}
	else
	{
		minishell_execve(operate, place, my_envp->envp);
		exit(EXIT_FAILURE);
	}
}

static void	close_move_tmp(t_execve_num *num)
{
	close(num->pipe_fd[1]);
	num->tmp_fd = num->pipe_fd[0];
}

static int	pipeline_loop(t_envp_data *my_envp, t_cmd_cnk *operate,
		t_execve_num *num)
{
	pid_t	pid;

	num->index = 0;
	num->tmp_fd = -1;
	while (num->index < num->operate_count)
	{
		if (num->index != num->operate_count - 1)
			if (pipe(num->pipe_fd) < 0)
				return (perror_free(operate, "pipe", num->operate_count));
		pid = fork();
		if (pid < 0)
			return (perror_free(operate, "fork", num->operate_count));
		if (pid == 0)
			execve_1cmd_pipe(my_envp, operate, num, num->index);
		if (num->index == num->operate_count - 1)
			num->last_pid = pid;
		if (num->tmp_fd != -1)
			close(num->tmp_fd);
		if (num->index != num->operate_count - 1)
			close_move_tmp(num);
		else
			close(num->pipe_fd[0]);
		num->index++;
	}
	return (0);
}

int	execve_pipeline(t_envp_data *my_envp, t_cmd_cnk *operate, t_execve_num *num)
{
	if (pipeline_loop(my_envp, operate, num) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	waitpid(num->last_pid, &num->exit_status, 0);
	if (WIFSIGNALED(num->exit_status) && WTERMSIG(num->exit_status) == SIGINT)
		write(1, "\n", 1);
	sigaction(SIGINT, &num->saved, NULL);
	free_operate(operate, num->operate_count);
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(num->exit_status))
		return (WEXITSTATUS(num->exit_status));
	if (WIFSIGNALED(num->exit_status))
		return (128 + WTERMSIG(num->exit_status));
	return (EXIT_FAILURE);
}
