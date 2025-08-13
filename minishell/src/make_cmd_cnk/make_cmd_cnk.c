/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_cnk1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:03:38 by rookuma           #+#    #+#             */
/*   Updated: 2025/07/19 15:58:33 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cnk_index_init(t_make_cnk_index *i)
{
	i->line_index = 0;
	i->op_index = 0;
	i->heredoc_num = 0;
	i->cmd_index = 0;
	i->redir_index = 0;
}

static t_cmd_cnk	*error_cnk_init(t_cmd_cnk *operate, int *status)
{
	free(operate);
	*status = 1;
	return (NULL);
}

static int	process_cmd_cnk(t_token *line, t_cmd_cnk *operate,
		t_make_cnk_index *i, int *status)
{
	if (line[i->line_index].type == cmd)
		return (cnk_cmd(line, operate, i, status));
	else if (line[i->line_index].type == input)
		return (cnk_input(line, operate, i, status));
	else if (line[i->line_index].type == output)
		return (cnk_output(line, operate, i, status));
	else if (line[i->line_index].type == add)
		return (cnk_append(line, operate, i, status));
	else if (line[i->line_index].type == heredoc)
		return (cnk_here_doc(line, operate, i, status));
	else
		return (TRUE);
}

static int	split_cmd_cnk(t_token *line, t_cmd_cnk *operate,
		t_make_cnk_index *i, int *status)
{
	while (line[i->line_index].str != NULL
		&& line[i->line_index].type != pipe_status)
	{
		if (!process_cmd_cnk(line, operate, i, status))
			return (FALSE);
		i->line_index++;
	}
	return (TRUE);
}

t_cmd_cnk	*make_cmd_cnk(t_token *line, int operate_count, int *status)
{
	t_make_cnk_index	i;
	t_cmd_cnk			*operate;

	operate = (t_cmd_cnk *)malloc(sizeof(t_cmd_cnk) * operate_count);
	if (!operate)
		return (NULL);
	cnk_index_init(&i);
	while (line[i.line_index].str != NULL)
	{
		if (!operate_init(line, operate, &i))
			return (error_cnk_init(operate, status));
		i.cmd_index = 0;
		if (!split_cmd_cnk(line, operate, &i, status))
		{
			free_operate(operate, i.op_index + 1);
			return (NULL);
		}
		operate[i.op_index].cmd[i.cmd_index] = NULL;
		if (line[i.line_index].str && line[i.line_index].type == pipe_status)
		{
			i.line_index++;
			i.op_index++;
		}
	}
	return (operate);
}
