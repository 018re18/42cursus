/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execve_free_op.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:00:22 by rookuma           #+#    #+#             */
/*   Updated: 2025/07/19 16:00:56 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_operate_cmd(t_cmd_cnk *operate, int i)
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

static void	free_operate_redir(t_cmd_cnk *operate, int i)
{
	int	j;

	j = 0;
	while (operate[i].redirect + 1 > j)
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
