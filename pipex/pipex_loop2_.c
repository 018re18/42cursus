/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_loop2_.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:19:40 by rookuma           #+#    #+#             */
/*   Updated: 2025/06/13 16:36:18 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex_start_place(int mode)
{
	if (mode == 1)
		return (3);
	else
		return (2);
}

char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	**path;
	char	*path_t;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path[i])
	{
		path_t = ft_strjoin_path(path[i], cmd);
		if (access(path_t, X_OK) == 0)
		{
			free_split(path);
			return (path_t);
		}
		free(path_t);
		i++;
	}
	free_split(path);
	return (NULL);
}

static void	read_choose(char **argv, t_ppx *x, t_loop *l)
{
	int	start;

	start = pipex_start_place(x->mode);
	if (l->i == start)
	{
		if (x->mode == 1)
			x->in_fd = open("here_doc", O_RDONLY);
		else
		{
			if (access(argv[1], R_OK) < 0)
				perror_exit("infile", 1);
			x->in_fd = open(argv[1], O_RDONLY);
		}
		if (x->in_fd < 0)
			perror_exit("infile", 1);
	}
	else
		x->in_fd = l->tmp_fd;
}

static void	write_choose(int argc, char **argv, t_ppx *x, t_loop *l)
{
	if (l->i == argc - 2)
	{
		if (x->mode == 1)
			x->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND,
					0644);
		else
		{
			if (access(argv[argc - 1], F_OK) == 0)
			{
				if (access(argv[argc - 1], W_OK) < 0)
					perror_exit("outfile", 1);
			}
			x->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		}
		if (x->out_fd < 0)
			perror_exit("outfile", 1);
	}
	else
		x->out_fd = x->pipe_fd[1];
}

void	pipex_change_in_out(int argc, char **argv, t_ppx *x, t_loop *l)
{
	read_choose(argv, x, l);
	write_choose(argc, argv, x, l);
	dup2(x->in_fd, 0);
	dup2(x->out_fd, 1);
	close(x->in_fd);
	close(x->out_fd);
	close(x->pipe_fd[0]);
	close(x->pipe_fd[1]);
	if (l->tmp_fd >= 0)
		close(l->tmp_fd);
}
