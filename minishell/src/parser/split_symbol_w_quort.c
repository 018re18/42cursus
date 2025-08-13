/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_symbol_w_quort.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:36:21 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/19 17:50:40 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*malloc_and_push(char *string, int i, int count_flag)
{
	char	*result;
	int		j;

	result = (char *)malloc(sizeof(char) * (i - count_flag + 1));
	j = 0;
	while (j < i - count_flag)
	{
		result[j] = string[count_flag + j];
		j++;
	}
	result[j] = '\0';
	return (result);
}

void	split_smbol_w_help_start(t_split *split, char **splited_pipe,
		char *string)
{
	splited_pipe[split->count] = malloc_and_push(string, split->i + 2,
			split->i);
	split->count++;
	split->split_flag = 1;
	split->i += 2;
	split->count_flag = split->i;
}

void	split_smbol_w_help_center(t_split *split, char **splited_pipe,
		char *string)
{
	splited_pipe[split->count] = malloc_and_push(string, split->i,
			split->count_flag);
	split->count++;
	splited_pipe[split->count] = malloc_and_push(string, split->i + 2,
			split->i);
	split->count++;
	split->split_flag = 1;
	split->i += 2;
	split->count_flag = split->i;
}

int	split_smbol_w(t_split *split, char **splited_pipe, char *string)
{
	int	continue_flag;

	continue_flag = 0;
	if (split->i == 0)
	{
		split_smbol_w_help_start(split, splited_pipe, string);
		continue_flag = 1;
	}
	else if (split->split_flag == 0)
	{
		split_smbol_w_help_center(split, splited_pipe, string);
		continue_flag = 1;
	}
	else if (split->split_flag == 1)
	{
		splited_pipe[split->count] = malloc_and_push(string, split->i + 2,
				split->i);
		split->count++;
		split->split_flag = 1;
		split->i += 2;
		split->count_flag = split->i;
		continue_flag = 1;
	}
	return (continue_flag);
}
