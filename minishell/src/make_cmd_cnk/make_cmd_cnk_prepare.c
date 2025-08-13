/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_cnk_prepare.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:55:22 by rookuma           #+#    #+#             */
/*   Updated: 2025/07/19 15:56:38 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_cmd_option(t_token *line, int start)
{
	int	count;

	count = 0;
	while (line[start].str != NULL && line[start].type != pipe_status)
	{
		if (line[start].type == cmd)
			count++;
		start++;
	}
	return (count);
}

static int	count_redirect(t_token *line, int start)
{
	int	count;

	count = 0;
	while (line[start].str != NULL && line[start].type != pipe_status)
	{
		if (line[start].type == input || line[start].type == output
			|| line[start].type == heredoc || line[start].type == add)
			count++;
		start++;
	}
	return (count);
}

static void	prepare_op_cmd(t_cmd_cnk *operate, int j, int cmd_option_count)
{
	int	k;

	k = 0;
	while (k < cmd_option_count)
	{
		operate[j].cmd[k] = NULL;
		k++;
	}
}

static void	prepare_redir(t_cmd_cnk *operate, int j, int redir_count)
{
	int	k;

	k = 0;
	while (k < redir_count)
	{
		operate[j].redir[k].type = -1;
		operate[j].redir[k].filename = NULL;
		operate[j].redir[k].limiter = NULL;
		k++;
	}
}

int	operate_init(t_token *line, t_cmd_cnk *operate, t_make_cnk_index *i)
{
	int	cmd_option_count;
	int	redir_count;

	cmd_option_count = count_cmd_option(line, i->line_index);
	operate[i->op_index].cmd = malloc(sizeof(char *) * (cmd_option_count + 1));
	if (!operate[i->op_index].cmd)
		return (FALSE);
	prepare_op_cmd(operate, i->op_index, cmd_option_count + 1);
	redir_count = count_redirect(line, i->line_index);
	operate[i->op_index].redir = malloc(sizeof(t_cmd_redir) * (redir_count
				+ 1));
	if (!operate[i->op_index].redir)
	{
		free(operate[i->op_index].cmd);
		return (FALSE);
	}
	prepare_redir(operate, i->op_index, redir_count + 1);
	operate[i->op_index].redirect = 0;
	i->cmd_index = 0;
	i->redir_index = 0;
	return (TRUE);
}
