/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execve.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:20:57 by rookuma           #+#    #+#             */
/*   Updated: 2025/07/13 17:24:52 by kryutaro         ###   ########.fr       */
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

int	make_operate(t_token *line, t_cmd_cnk **operate, int operate_count,int *status)
{
	int	i;

	*operate = make_cmd_cnk(line, operate_count,status);
	i = 0;
	while (line[i].str)
	{
		free(line[i].str);
		i++;
	}
	free(line);
	if (!*operate)
	{
		return (FALSE);
	}
	return (TRUE);
}

void	free_operate_cmd(t_cmd_cnk *operate, int i)
{
	int	j;

	j = 0;
	while (operate[i].cmd[j])
	{
		free(operate[i].cmd[j]);
		j++;
	}
	free(operate[i].cmd);
}

void	free_operate_redir(t_cmd_cnk *operate, int i)
{
	int	j;

	j = 0;
	while (operate[i].redirect > j)
	{
		if (operate[i].redir[j].type == heredoc)
		{
			unlink(operate[i].redir[j].filename);
			free(operate[i].redir[j].filename);
			free(operate[i].redir[j].limiter);
		}
		else
			free(operate[i].redir[j].filename);
		j++;
	}
	free(operate[i].redir);
}

void	free_operate(t_cmd_cnk *operate, int operate_count)
{
	int	i;

	i = 0;
	while (i < operate_count)
	{
		if (operate[i].cmd)
			free_operate_cmd(operate, i);
		if (operate[i].redir)
			free_operate_redir(operate, i);
		i++;
	}
	free(operate);
}

int	perror_free(t_cmd_cnk *operate, char *err, int operate_count)
{
	perror(err);
	free_operate(operate, operate_count);
	return (EXIT_FAILURE);
}

int	input_file_help1(t_cmd_cnk *operate, int place, int redir_place)
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

int	input_file_help2(t_cmd_cnk *operate, int place, int redir_place)
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

static t_fd	input_file(t_cmd_cnk *operate, int place, int redir_place)
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

int	input_here_doc_file_help(char *filename)
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

static t_fd	input_here_doc_file(char *filename)
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

int	output_file_help(t_cmd_cnk *operate, int place, int redir_place)
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

static t_fd	output_file(t_cmd_cnk *operate, int place, int redir_place)
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

int	output_append_help(t_cmd_cnk *operate, int place, int redir_place)
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

static t_fd	output_append(t_cmd_cnk *operate, int place, int redir_place)
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

static void	ft_strcpy_path(char *dest, const char *src, int plase)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[plase + i] = src[i];
		i++;
	}
}

static char	*ft_strjoin_path(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 2));
	if (!str)
		return (NULL);
	ft_strcpy_path(str, s1, 0);
	str[s1_len] = '/';
	ft_strcpy_path(str, s2, s1_len + 1);
	str[s1_len + s2_len + 1] = '\0';
	return (str);
}

static void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	check_path(char *cmd, char **path, char **all_path)
{
	int		i;
	char	*test_path;

	i = 0;
	while (all_path[i])
	{
		test_path = ft_strjoin_path(all_path[i], cmd);
		if (!test_path)
			return (1);
		if (access(test_path, F_OK) == 0)
		{
			if (access(test_path, X_OK) == 0)
			{
				*path = test_path;
				return (0);
			}
			free(test_path);
			return (126);
		}
		free(test_path);
		i++;
	}
	return (127);
}

int	get_path(char *cmd, char **envp, char **path)
{
	int		i;
	int		exit_judge;
	char	**all_path;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (127);
	all_path = ft_split(envp[i] + 5, ':');
	if (!all_path)
		return (1);
	exit_judge = check_path(cmd, path, all_path);
	free_split(all_path);
	return (exit_judge);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			return ((char *)(s + i));
		}
		i++;
	}
	if ((char)c == '\0')
	{
		return ((char *)(s + i));
	}
	return (NULL);
}

static int	prepare_path(t_cmd_cnk *operate, int place, char **envp,
		char **cmd_path)
{
	int	exit_judge;
	DIR	*dir;

	if (ft_strchr(operate[place].cmd[0], '/'))
	{
		*cmd_path = ft_strdup(operate[place].cmd[0]);
		if (!*cmd_path)
			return (1);
		dir = opendir(*cmd_path);
		if (dir != NULL)
		{
			closedir(dir);
			write(2, "minishell: ", 11);
			write(2, *cmd_path, ft_strlen(*cmd_path));
			write(2, ": Is a directory\n", 17);
			return (400);
		}
		if (access(*cmd_path, F_OK) == 0)
		{
			if (access(*cmd_path, X_OK) != 0)
			{
				free(*cmd_path);
				return (126);
			}
		}
		else
		{
			free(*cmd_path);
			closedir(dir);
			write(2, "minishell: ", 11);
			write(2, *cmd_path, ft_strlen(*cmd_path));
			write(2, ": No such file or directory\n", 28);
			return (500);
		}
		return (0);
	}
	exit_judge = get_path(operate[place].cmd[0], envp, cmd_path);
	return (exit_judge);
}

void	check_exit_judge(t_cmd_cnk *operate, int place, char *cmd_path,
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

static void	minishell_execve(t_cmd_cnk *operate, int place, char **envp)
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
		status = ft_pwd(envp);
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

int	minishell_redirect_loop(t_cmd_cnk *operate, int place)
{
	int	redir_place;

	redir_place = 0;
	while (operate[place].redirect > redir_place)
	{
		if (operate[place].redir[redir_place].type == input)
		{
			if (!input_file(operate, place, redir_place))
				return (FALSE);
		}
		else if (operate[place].redir[redir_place].type == heredoc)
		{
			if (!input_here_doc_file(operate[place].redir[redir_place].filename))
				return (FALSE);
		}
		else if (operate[place].redir[redir_place].type == output)
		{
			if (!output_file(operate, place, redir_place))
				return (FALSE);
		}
		else if (operate[place].redir[redir_place].type == add)
		{
			if (!output_append(operate, place, redir_place))
				return (FALSE);
		}
		redir_place++;
	}
	return (TRUE);
}

int	execve_buitlin_1cmd(t_envp_data *my_envp, t_cmd_cnk *operate,
		t_execve_num *num)
{
	int	save_stdin;
	int	save_stdout;
	int	status;

	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	if (operate[0].redirect > 0)
	{
		if (!minishell_redirect_loop(operate, 0))
			return (builtin_restore_free(save_stdin, save_stdout, operate, 1));
	}
	status = builtin_execve(operate, 0, my_envp, num);
	return (builtin_restore_free(save_stdin, save_stdout, operate, status));
}

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

void	execve_1cmd_pipe(t_envp_data *my_envp, t_cmd_cnk *operate,
		t_execve_num *num, int place)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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

void	close_move_tmp(t_execve_num *num)
{
	close(num->pipe_fd[1]);
	num->tmp_fd = num->pipe_fd[0];
}

int	pipeline_loop(t_envp_data *my_envp, t_cmd_cnk *operate, t_execve_num *num)
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

int	execve_main(t_token *line, t_envp_data *my_envp, int exit_status)
{
	t_execve_num	num;
	t_cmd_cnk		*operate;
	int				result;
	int status;

	num.exit_status = exit_status;
	sigaction(SIGINT, NULL, &num.saved);
	sigaction(SIGQUIT, NULL, &num.saved_quit);
	num.g_sa.sa_handler = SIG_IGN;
	sigemptyset(&num.g_sa.sa_mask);
	num.g_sa.sa_flags = 0;
	sigaction(SIGINT, &num.g_sa, NULL);
	sigaction(SIGQUIT, &num.g_sa, NULL);
	status=0;
	num.operate_count = count_all_cmd(line);
	if (num.operate_count == 0)
	{
		write(2, "minishell: : command not found\n", 31);
		sigaction(SIGINT, &num.saved, NULL);
		sigaction(SIGQUIT, &num.saved_quit, NULL);
		return (127);
	}
	if (!make_operate(line, &operate, num.operate_count,&status))
	{
		sigaction(SIGINT, &num.saved, NULL);
		sigaction(SIGQUIT, &num.saved_quit, NULL);
		return (status);
	}
	if (num.operate_count == 1)
		result = execve_cmd_single(my_envp, operate, &num);
	else
		result = execve_pipeline(my_envp, operate, &num);
	sigaction(SIGINT, &num.saved, NULL);
	sigaction(SIGQUIT, &num.saved_quit, NULL);
	return (result);
}
