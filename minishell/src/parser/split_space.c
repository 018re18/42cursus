/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:29:41 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/19 17:50:32 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_space_help(t_split *split, char **splited_pipe, char *string)
{
	splited_pipe[split->count] = malloc_and_push(string, split->i,
			split->count_flag);
	split->count++;
	split->split_flag = 1;
	split->i += 1;
	split->count_flag = split->i;
}

int	split_space(t_split *split, char **splited_pipe, char *string)
{
	int	continue_flag;

	continue_flag = 0;
	if (split->i == 0)
	{
		split->split_flag = 1;
		split->i += 1;
		split->count_flag = split->i;
		continue_flag = 1;
	}
	else if (split->split_flag == 0)
	{
		split_space_help(split, splited_pipe, string);
		continue_flag = 1;
	}
	else if (split->split_flag == 1)
	{
		split->split_flag = 1;
		split->i += 1;
		split->count_flag = split->i;
		continue_flag = 1;
	}
	return (continue_flag);
}
