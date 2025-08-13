/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:02:04 by rookuma           #+#    #+#             */
/*   Updated: 2025/07/20 12:48:06 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	input_file_help1(t_cmd_cnk *operate, int place, int redir_place)
{
	if (access(operate[place].redir[redir_place].filename, F_OK) != 0)
	{
		write(2, "minishell: ", 11);
		write(2, operate[place].redir[redir_place].filename,
			ft_strlen(operate[place].redir[redir_place].filename));
		write(2, ": No such file or directory\n", 28);
		close(0);
		return (FALSE);
	}
	return (TRUE);
}

static int	input_file_help2(t_cmd_cnk *operate, int place, int redir_place)
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
		close(0);
		return (FALSE);
	}
	if (access(operate[place].redir[redir_place].filename, R_OK) != 0)
	{
		write(2, "minishell: ", 11);
		write(2, operate[place].redir[redir_place].filename,
			ft_strlen(operate[place].redir[redir_place].filename));
		write(2, ": Permission denied\n", 20);
		close(0);
		return (FALSE);
	}
	return (TRUE);
}

t_fd	input_file(t_cmd_cnk *operate, int place, int redir_place)
{
	int	fd;

	if (!input_file_help1(operate, place, redir_place))
		return (FALSE);
	if (!input_file_help2(operate, place, redir_place))
		return (FALSE);
	fd = open(operate[place].redir[redir_place].filename, O_RDONLY);
	if (fd < 0)
	{
		write(2, "minishell: ", 11);
		write(2, operate[place].redir[redir_place].filename,
			ft_strlen(operate[place].redir[redir_place].filename));
		write(2, ": No such file or directory\n", 28);
		close(0);
		return (FALSE);
	}
	if (dup2(fd, 0) == -1)
	{
		perror("dup2");
		close(fd);
		close(0);
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}

static int	input_here_doc_file_help(char *filename)
{
	if (access(filename, F_OK) != 0)
	{
		write(2, "minishell: ", 11);
		write(2, filename, ft_strlen(filename));
		write(2, ": No such file or directory\n", 28);
		close(0);
		return (FALSE);
	}
	if (access(filename, R_OK) != 0)
	{
		write(2, "minishell: ", 11);
		write(2, filename, ft_strlen(filename));
		write(2, ": Permission denied\n", 20);
		close(0);
		return (FALSE);
	}
	return (TRUE);
}

t_fd	input_heredoc(char *filename)
{
	int	fd;

	if (!input_here_doc_file_help(filename))
		return (FALSE);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		close(0);
		return (FALSE);
	}
	if (dup2(fd, 0) == -1)
	{
		perror("dup2");
		close(fd);
		close(0);
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}
