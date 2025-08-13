/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:10:51 by rookuma           #+#    #+#             */
/*   Updated: 2025/07/20 15:07:07 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(const char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (TRUE);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (TRUE);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (TRUE);
	else if (ft_strcmp(cmd, "export") == 0)
		return (TRUE);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (TRUE);
	else if (ft_strcmp(cmd, "env") == 0)
		return (TRUE);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (TRUE);
	else
		return (FALSE);
}

int	builtin_execve(t_cmd_cnk *operate, int place, t_envp_data *envp,
		t_execve_num *num)
{
	int	status;

	status = 0;
	if (ft_strcmp(operate[place].cmd[0], "echo") == 0)
		status = ft_echo(operate[place].cmd);
	else if (ft_strcmp(operate[place].cmd[0], "cd") == 0)
		status = ft_cd(envp, operate[place].cmd);
	else if (ft_strcmp(operate[place].cmd[0], "pwd") == 0)
		status = ft_pwd();
	else if (ft_strcmp(operate[place].cmd[0], "export") == 0)
		status = ft_export(operate[place].cmd, envp);
	else if (ft_strcmp(operate[place].cmd[0], "unset") == 0)
		*envp = ft_unset(operate[place].cmd, *envp);
	else if (ft_strcmp(operate[place].cmd[0], "env") == 0)
		*envp = ft_env(*envp, num, operate[place].cmd);
	else if (ft_strcmp(operate[place].cmd[0], "exit") == 0)
		status = ft_exit(operate, place, num, envp);
	return (status);
}

int	builtin_restore_free(int save_stdin, int save_stdout, t_cmd_cnk *operate,
		int status)
{
	dup2(save_stdin, STDIN_FILENO);
	dup2(save_stdout, STDOUT_FILENO);
	close(save_stdin);
	close(save_stdout);
	free_operate(operate, 1);
	return (status);
}

int	execve_buitlin_1cmd(t_envp_data *my_envp, t_cmd_cnk *operate,
		t_execve_num *num)
{
	int	status;

	num->save_stdin = dup(STDIN_FILENO);
	num->save_stdout = dup(STDOUT_FILENO);
	if (operate[0].redirect > 0)
	{
		if (!minishell_redirect_loop(operate, 0))
			return (builtin_restore_free(num->save_stdin, num->save_stdout,
					operate, 1));
	}
	status = builtin_execve(operate, 0, my_envp, num);
	return (builtin_restore_free(num->save_stdin, num->save_stdout, operate,
			status));
}
