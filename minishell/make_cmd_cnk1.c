/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_cnk1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:03:38 by rookuma           #+#    #+#             */
/*   Updated: 2025/07/13 15:23:14 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cnk_index_init(t_make_cnk_index *i)
{
	i->line_index = 0;
	i->op_index = 0;
	i->heredoc_num = 0;
	i->cmd_index = 0;
	i->redir_index = 0;
}

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

int	count_redirect(t_token *line, int start)
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

void	prepare_op_cmd(t_cmd_cnk *operate, int j, int cmd_option_count)
{
	int	k;

	k = 0;
	while (k < cmd_option_count)
	{
		operate[j].cmd[k] = NULL;
		k++;
	}
}

void	prepare_redir(t_cmd_cnk *operate, int j, int redir_count)
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

int	cnk_cmd(t_token *line, t_cmd_cnk *operate, t_make_cnk_index *i,int *status)
{
	operate[i->op_index].cmd[i->cmd_index] = ft_strdup(line[i->line_index].str);
	if (!operate[i->op_index].cmd[i->cmd_index])
	{
		*status=1;
		return (FALSE);
	}
	i->cmd_index++;
	return (TRUE);
}

int	cnk_input(t_token *line, t_cmd_cnk *operate, t_make_cnk_index *i,int *status)
{
	operate[i->op_index].redir[i->redir_index].type = input;
	i->line_index++;
	operate[i->op_index].redir[i->redir_index].filename = ft_strdup(line[i->line_index].str);
	if (!operate[i->op_index].redir[i->redir_index].filename)
	{
		*status=1;
		return (FALSE);
	}
	operate[i->op_index].redirect++;
	i->redir_index++;
	return (TRUE);
}

int	cnk_output(t_token *line, t_cmd_cnk *operate, t_make_cnk_index *i,int *status)
{
	operate[i->op_index].redir[i->redir_index].type = output;
	i->line_index++;
	operate[i->op_index].redir[i->redir_index].filename = ft_strdup(line[i->line_index].str);
	if (!operate[i->op_index].redir[i->redir_index].filename)
	{
		*status=1;
		return (FALSE);
	}
	operate[i->op_index].redirect++;
	i->redir_index++;
	return (TRUE);
}

int	cnk_append(t_token *line, t_cmd_cnk *operate, t_make_cnk_index *i,int *status)
{
	operate[i->op_index].redir[i->redir_index].type = add;
	i->line_index++;
	operate[i->op_index].redir[i->redir_index].filename = ft_strdup(line[i->line_index].str);
	if (!operate[i->op_index].redir[i->redir_index].filename)
	{
		*status=1;
		return (FALSE);
	}
	operate[i->op_index].redirect++;
	i->redir_index++;
	return (TRUE);
}

int	cnk_here_doc(t_token *line, t_cmd_cnk *operate, t_make_cnk_index *i,int *status)
{
	operate[i->op_index].redir[i->redir_index].type = heredoc;
	i->line_index++;
	operate[i->op_index].redir[i->redir_index].limiter = ft_strdup(line[i->line_index].str);
	if (!operate[i->op_index].redir[i->redir_index].limiter)
	{
		*status=1;
		return (FALSE);
	}
	if(!make_here_doc(operate,i->heredoc_num, i->redir_index,status))
		return FALSE;
	operate[i->op_index].redirect++;
	i->heredoc_num++;
	i->redir_index++;
	return (TRUE);
}

int	process_cmd_cnk(t_token *line, t_cmd_cnk *operate, t_make_cnk_index *i,int *status)
{
	if (line[i->line_index].type == cmd)
		return (cnk_cmd(line, operate, i,status));
	else if (line[i->line_index].type == input)
		return (cnk_input(line, operate, i,status));
	else if (line[i->line_index].type == output)
		return (cnk_output(line, operate, i,status));
	else if (line[i->line_index].type == add)
		return (cnk_append(line, operate, i,status));
	else if (line[i->line_index].type == heredoc)
		return (cnk_here_doc(line, operate, i,status));
	else
		return (TRUE);
}

int	split_cmd_cnk(t_token *line, t_cmd_cnk *operate, t_make_cnk_index *i,int *status)
{
	while (line[i->line_index].str != NULL
		&& line[i->line_index].type != pipe_status)
	{
	if(!process_cmd_cnk(line, operate, i,status))
			return FALSE;
		i->line_index++;
	}
	return (TRUE);
}

t_cmd_cnk *error_cnk_init( t_cmd_cnk *operate,int *status)
{
	free(operate);
	*status=1;
	return (NULL);
}

t_cmd_cnk	*make_cmd_cnk(t_token *line, int operate_count,int *status)
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
			return error_cnk_init(operate,status);
		i.cmd_index = 0;
		if (!split_cmd_cnk(line, operate, &i,status))
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
