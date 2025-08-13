/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execve_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:28:14 by rookuma           #+#    #+#             */
/*   Updated: 2025/07/19 17:28:59 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_all_cmd(t_token *line)
{
	int	i;
	int	count;

	if (!line[0].str || line[0].str[0] == '\0')
		return (0);
	i = 0;
	count = 1;
	while (line[i].str != NULL)
	{
		if (line[i].type == pipe_status)
			count++;
		i++;
	}
	return (count);
}

int	write_cmd_error(t_token *line, t_execve_num *num)
{
	int	i;

	write(2, "minishell: : command not found\n", 31);
	sigaction(SIGINT, &num->saved, NULL);
	sigaction(SIGQUIT, &num->saved_quit, NULL);
	i = 0;
	while (line[i].str)
	{
		free(line[i].str);
		i++;
	}
	free(line);
	return (127);
}

int	perror_free(t_cmd_cnk *operate, char *err, int operate_count)
{
	perror(err);
	free_operate(operate, operate_count);
	return (EXIT_FAILURE);
}

int	check_directory(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir != NULL)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}
