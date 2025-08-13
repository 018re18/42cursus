/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execve_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:24:55 by rookuma           #+#    #+#             */
/*   Updated: 2025/07/19 17:26:04 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	path_directory_error(char **cmd_path)
{
	write(2, "minishell: ", 11);
	write(2, *cmd_path, ft_strlen(*cmd_path));
	write(2, ": Is a directory\n", 17);
	return (400);
}

static int	path_no_such_error(char **cmd_path)
{
	write(2, "minishell: ", 11);
	write(2, *cmd_path, ft_strlen(*cmd_path));
	write(2, ": No such file or directory\n", 28);
	free(*cmd_path);
	return (500);
}

static int	prepare_path(t_cmd_cnk *operate, int place, char **envp,
		char **cmd_path)
{
	int	exit_judge;

	if (ft_strchr(operate[place].cmd[0], '/'))
	{
		*cmd_path = ft_strdup(operate[place].cmd[0]);
		if (!*cmd_path)
			return (1);
		if (check_directory(*cmd_path))
			return (path_directory_error(cmd_path));
		if (access(*cmd_path, F_OK) == 0)
		{
			if (access(*cmd_path, X_OK) != 0)
			{
				free(*cmd_path);
				return (126);
			}
		}
		else
			return (path_no_such_error(cmd_path));
		return (0);
	}
	exit_judge = get_path(operate[place].cmd[0], envp, cmd_path);
	return (exit_judge);
}

static void	check_exit_judge(t_cmd_cnk *operate, int place, char *cmd_path,
		int exit_judge)
{
	if (exit_judge == 127)
	{
		write(2, operate[place].cmd[0], ft_strlen(operate[place].cmd[0]));
		write(2, ": command not found\n", 20);
	}
	else if (exit_judge == 126)
	{
		write(2, "minishell: ", 11);
		write(2, cmd_path, ft_strlen(cmd_path));
		write(2, ": Permission denied\n", 20);
	}
	else if (exit_judge == 400)
		exit_judge = 126;
	else if (exit_judge == 500)
		exit_judge = 127;
	exit(exit_judge);
}

void	minishell_execve(t_cmd_cnk *operate, int place, char **envp)
{
	char	*cmd_path;
	int		exit_judge;

	if (operate[place].cmd[0] == NULL || operate[place].cmd[0][0] == '\0')
	{
		write(2, "minishell: : command not found\n", 31);
		exit(127);
	}
	exit_judge = prepare_path(operate, place, envp, &cmd_path);
	if (exit_judge != 0)
		check_exit_judge(operate, place, cmd_path, exit_judge);
	execve(cmd_path, operate[place].cmd, envp);
	if (cmd_path != operate[place].cmd[0])
		free(cmd_path);
	perror("execve");
	exit(1);
}
