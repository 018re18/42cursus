/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_heredoc_loop.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:40:02 by rookuma           #+#    #+#             */
/*   Updated: 2025/07/21 17:32:36 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_return_ctrlc(t_cmd_cnk *operate, t_make_cnk_index *i)
{
	g_received_signal = 0;
	unlink(operate[i->op_index].redir[i->redir_index].filename);
	return (130);
}

static void	write_heredoc_error(t_cmd_cnk *operate, int place, int redir_place,
		int len)
{
	write(2,
		"minishell: warning: here-document delimited by end-of-file (wanted `",
		68);
	write(2, operate[place].redir[redir_place].limiter, len);
	write(2, "')\n", 3);
}

static void	here_doc_write_tmp(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
	free(str);
}

int	here_doc_loop(t_cmd_cnk *operate, t_make_cnk_index *i, int fd)
{
	t_heredoc_str	str;

	str.len = ft_strlen(operate[i->op_index].redir[i->redir_index].limiter);
	while (1)
	{
		write(1, "> ", 2);
		str.str = get_next_line(0);
		if (g_received_signal == SIGINT)
			return (heredoc_return_ctrlc(operate, i));
		if (!str.str)
		{
			write_heredoc_error(operate, i->op_index, i->redir_index, str.len);
			break ;
		}
		if (str.str[ft_strlen(str.str) - 1] == '\n')
			str.str[ft_strlen(str.str) - 1] = '\0';
		if (ft_strcmp(str.str,
				operate[i->op_index].redir[i->redir_index].limiter) == 0)
		{
			free(str.str);
			break ;
		}
		here_doc_write_tmp(fd, str.str);
	}
	return (0);
}
