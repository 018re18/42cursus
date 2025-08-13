/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:37:49 by rookuma           #+#    #+#             */
/*   Updated: 2025/07/19 18:32:24 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ctr_c_here_doc_handler(int signum)
{
	g_received_signal = signum;
	write(STDOUT_FILENO, "\n", 1);
}

static void	here_doc_signal(struct sigaction *saved_int,
		struct sigaction *saved_quit)
{
	struct sigaction	g_sa;

	sigaction(SIGINT, NULL, saved_int);
	sigaction(SIGQUIT, NULL, saved_quit);
	g_sa.sa_handler = ctr_c_here_doc_handler;
	sigemptyset(&g_sa.sa_mask);
	g_sa.sa_flags = 0;
	sigaction(SIGINT, &g_sa, NULL);
	g_sa.sa_handler = SIG_IGN;
	sigemptyset(&g_sa.sa_mask);
	g_sa.sa_flags = 0;
	sigaction(SIGQUIT, &g_sa, NULL);
}

static char	*make_here_doc_filename(int place)
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

static int	open_here_doc(char *filename)
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

int	make_here_doc(t_cmd_cnk *operate, t_make_cnk_index *i, int *status)
{
	char				*filename;
	int					fd;
	struct sigaction	saved_int;
	struct sigaction	saved_quit;

	here_doc_signal(&saved_int, &saved_quit);
	filename = make_here_doc_filename(i->heredoc_num);
	if (!filename)
	{
		*status = 1;
		return (FALSE);
	}
	operate[i->op_index].redir[i->redir_index].filename = filename;
	fd = open_here_doc(operate[i->op_index].redir[i->redir_index].filename);
	*status = here_doc_loop(operate, i, fd);
	close(fd);
	g_received_signal = 0;
	sigaction(SIGINT, &saved_int, NULL);
	sigaction(SIGQUIT, &saved_quit, NULL);
	if (*status == 130)
		return (FALSE);
	return (TRUE);
}
