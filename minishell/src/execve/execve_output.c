/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execve_output.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:04:31 by rookuma           #+#    #+#             */
/*   Updated: 2025/07/19 16:05:33 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	output_file_help(t_cmd_cnk *operate, int place, int redir_place)
{
	DIR	*dir;

	dir = opendir(operate[place].redir[redir_place].filename);
	if (dir != NULL)
	{
		closedir(dir);
		write(2, "minishell: ", 11);
		write(2, operate[place].redir[redir_place].filename,
			ft_strlen(operate[place].redir[redir_place].filename));
		write(2, ": Is a directory\n", 17);
		close(1);
		return (FALSE);
	}
	if (access(operate[place].redir[redir_place].filename, F_OK) == 0
		&& access(operate[place].redir[redir_place].filename, W_OK) != 0)
	{
		write(2, "minishell: ", 11);
		write(2, operate[place].redir[redir_place].filename,
			ft_strlen(operate[place].redir[redir_place].filename));
		write(2, ": Permission denied\n", 20);
		close(1);
		return (FALSE);
	}
	return (TRUE);
}

t_fd	output_file(t_cmd_cnk *operate, int place, int redir_place)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (!output_file_help(operate, place, redir_place))
		return (FALSE);
	fd = open(operate[place].redir[redir_place].filename, flags, 0644);
	if (fd < 0)
	{
		write(2, "minishell: ", 11);
		write(2, operate[place].redir[redir_place].filename,
			ft_strlen(operate[place].redir[redir_place].filename));
		write(2, ": No such file or directory\n", 28);
		close(1);
		return (FALSE);
	}
	if (dup2(fd, 1) == -1)
	{
		perror("dup2");
		close(fd);
		close(1);
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}

static int	output_append_help(t_cmd_cnk *operate, int place, int redir_place)
{
	DIR	*dir;

	dir = opendir(operate[place].redir[redir_place].filename);
	if (dir != NULL)
	{
		closedir(dir);
		write(2, "minishell: ", 11);
		write(2, operate[place].redir[redir_place].filename,
			ft_strlen(operate[place].redir[redir_place].filename));
		write(2, ": Is a directory\n", 17);
		close(1);
		return (FALSE);
	}
	if (access(operate[place].redir[redir_place].filename, F_OK) == 0
		&& access(operate[place].redir[redir_place].filename, W_OK) != 0)
	{
		write(2, "minishell: ", 11);
		write(2, operate[place].redir[redir_place].filename,
			ft_strlen(operate[place].redir[redir_place].filename));
		write(2, ": Permission denied\n", 20);
		close(1);
		return (FALSE);
	}
	return (TRUE);
}

t_fd	output_append(t_cmd_cnk *operate, int place, int redir_place)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT | O_APPEND;
	if (!output_append_help(operate, place, redir_place))
		return (FALSE);
	fd = open(operate[place].redir[redir_place].filename, flags, 0644);
	if (fd < 0)
	{
		write(2, "minishell: ", 11);
		write(2, operate[place].redir[redir_place].filename,
			ft_strlen(operate[place].redir[redir_place].filename));
		write(2, ": No such file or directory\n", 28);
		close(1);
		return (FALSE);
	}
	if (dup2(fd, 1) == -1)
	{
		perror("dup2");
		close(fd);
		close(1);
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}
