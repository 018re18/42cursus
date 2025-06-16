/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_loop1_.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:40:16 by rookuma           #+#    #+#             */
/*   Updated: 2025/06/14 11:38:36 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*prepare_path(char ***cmd, int i, char **argv, char **envp)
{
	char	**pre_cmd;
	char	*path;

	pre_cmd = ft_split(argv[i], ' ');
	if (!pre_cmd || !pre_cmd[0])
	{
		write(2, ": command not found", 19);
		free_split(pre_cmd);
		write(2, "\n", 1);
		exit(127);
	}
	if (pre_cmd[0][0] == '/')
	{
		path = pre_cmd[0];
		if (access(path, X_OK) != 0)
			path = NULL;
	}
	else
		path = get_path(pre_cmd[0], envp);
	*cmd = pre_cmd;
	return (path);
}

static void	pipex_execve(int i, char **argv, char **envp)
{
	char	**cmd;
	char	*path;

	path = prepare_path(&cmd, i, argv, envp);
	if (!path)
	{
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, ": command not found", 19);
		free_split(cmd);
		write(2, "\n", 1);
		exit(127);
	}
	execve(path, cmd, envp);
	if (path != cmd[0])
		free(path);
	free_split(cmd);
	perror_exit("execve", 1);
}

static int	pipex_wait(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (EXIT_FAILURE);
}

int	pipex_loop(int argc, char **argv, char **envp, t_ppx *x)
{
	t_loop	l;

	l.tmp_fd = -1;
	l.i = pipex_start_place(x->mode);
	while (l.i < argc - 1)
	{
		if (pipe(x->pipe_fd) < 0)
			perror_exit("pipe", 1);
		l.pid = fork();
		if (l.pid < 0)
			perror_exit("fork", 1);
		if (l.pid == 0)
		{
			pipex_change_in_out(argc, argv, x, &l);
			pipex_execve(l.i, argv, envp);
		}
		close(x->pipe_fd[1]);
		if (l.tmp_fd >= 0)
			close(l.tmp_fd);
		l.tmp_fd = x->pipe_fd[0];
		l.i++;
	}
	return (pipex_wait(l.pid));
}
