/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_heredoc1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:37:49 by rookuma           #+#    #+#             */
/*   Updated: 2025/07/11 12:39:32 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//りみたーで止まらない
//呼んだあとにfilenameのfreeとunlinkしないとだめ

// void	ctr_back_slash_here_doc_handler(int signum)
// {
// 	(void)signum;
// 	rl_replace_line("Quit (core dumped)\n", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }

extern volatile sig_atomic_t	g_received_signal;

void	ctr_c_here_doc_handler(int signum)
{
	g_received_signal = signum;
	write(STDOUT_FILENO, "\n", 1);
}

char	*make_here_doc_filename(int place)
{
	char	*num;
	char	*filename;

	num = ft_itoa(place);
	if (!num)
		return (NULL);
	filename = ft_strjoin("/tmp/here_doc_tmp_", num);
	free(num);
	if (!filename)
		return (NULL);
	return (filename);
}

int	open_here_doc(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		free(filename);
		exit(1);
	}
	return (fd);
}

void	write_heredoc_error(t_cmd_cnk *operate, int place, int redir_place,
		int len)
{
	write(2, "bash: warning: here-document delimited by end-of-file (wanted `",
		63);
	write(2, operate[place].redir[redir_place].limiter, len);
	write(2, "')\n", 3);
}

void	here_doc_loop(t_cmd_cnk *operate, int place, int redir_place, int fd)
{
	char	*str;
	int		len;

	len = ft_strlen(operate[place].redir[redir_place].limiter);
	while (1)
	{
		write(1, "> ", 2);
		str = get_next_line(0);
		if (!str)
		{
			write_heredoc_error(operate, place, redir_place, len);
			break ;
		}
		if (str[ft_strlen(str) - 1] == '\n')
			str[ft_strlen(str) - 1] = '\0';
		if (ft_strcmp(str, operate[place].redir[redir_place].limiter) == 0)
		{
			free(str);
			break ;
		}
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
}

char	*make_here_doc(t_cmd_cnk *operate, int place, int redir_place)
{
	char				*filename;
	int					fd;
	struct sigaction	g_sa;
	struct sigaction	saved_int;
	struct sigaction	saved_quit;

	sigaction(SIGINT, NULL, &saved_int);
	sigaction(SIGQUIT, NULL, &saved_quit);
	g_sa.sa_handler = ctr_c_here_doc_handler;
	sigemptyset(&g_sa.sa_mask);
	g_sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &g_sa, NULL);
	g_sa.sa_handler = SIG_IGN;
	sigemptyset(&g_sa.sa_mask);
	g_sa.sa_flags = 0;
	sigaction(SIGQUIT, &g_sa, NULL);
	filename = make_here_doc_filename(place);
	if (!filename)
		return (NULL);
	fd = open_here_doc(filename);
	here_doc_loop(operate, place, redir_place, fd);
	close(fd);
	g_received_signal = 0;
	sigaction(SIGINT, &saved_int, NULL);
	sigaction(SIGQUIT, &saved_quit, NULL);
	return (filename);
}
