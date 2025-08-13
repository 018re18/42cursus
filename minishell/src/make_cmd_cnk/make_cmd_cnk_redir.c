/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_cnk_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:51:35 by rookuma           #+#    #+#             */
/*   Updated: 2025/07/25 12:29:52 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cnk_cmd(t_token *line, t_cmd_cnk *operate, t_make_cnk_index *i, int *status)
{
	operate[i->op_index].cmd[i->cmd_index] = ft_strdup(line[i->line_index].str);
	if (!operate[i->op_index].cmd[i->cmd_index])
	{
		*status = 1;
		return (FALSE);
	}
	i->cmd_index++;
	return (TRUE);
}

int	cnk_input(t_token *line, t_cmd_cnk *operate, t_make_cnk_index *i,
		int *status)
{
	operate[i->op_index].redir[i->redir_index].type = input;
	i->line_index++;
	operate[i->op_index].redir[i->redir_index].filename = \
	ft_strdup(line[i->line_index].str);
	if (!operate[i->op_index].redir[i->redir_index].filename)
	{
		*status = 1;
		return (FALSE);
	}
	operate[i->op_index].redirect++;
	i->redir_index++;
	return (TRUE);
}

int	cnk_output(t_token *line, t_cmd_cnk *operate, t_make_cnk_index *i,
		int *status)
{
	operate[i->op_index].redir[i->redir_index].type = output;
	i->line_index++;
	operate[i->op_index].redir[i->redir_index].filename = \
	ft_strdup(line[i->line_index].str);
	if (!operate[i->op_index].redir[i->redir_index].filename)
	{
		*status = 1;
		return (FALSE);
	}
	operate[i->op_index].redirect++;
	i->redir_index++;
	return (TRUE);
}

int	cnk_append(t_token *line, t_cmd_cnk *operate, t_make_cnk_index *i,
		int *status)
{
	operate[i->op_index].redir[i->redir_index].type = add;
	i->line_index++;
	operate[i->op_index].redir[i->redir_index].filename = \
	ft_strdup(line[i->line_index].str);
	if (!operate[i->op_index].redir[i->redir_index].filename)
	{
		*status = 1;
		return (FALSE);
	}
	operate[i->op_index].redirect++;
	i->redir_index++;
	return (TRUE);
}

int	cnk_here_doc(t_token *line, t_cmd_cnk *operate, t_make_cnk_index *i,
		int *status)
{
	operate[i->op_index].redir[i->redir_index].type = heredoc;
	i->line_index++;
	operate[i->op_index].redir[i->redir_index].limiter = \
	ft_strdup(line[i->line_index].str);
	if (!operate[i->op_index].redir[i->redir_index].limiter)
	{
		*status = 1;
		return (FALSE);
	}
	if (!make_here_doc(operate, i, status))
		return (FALSE);
	operate[i->op_index].redirect++;
	i->heredoc_num++;
	i->redir_index++;
	return (TRUE);
}
