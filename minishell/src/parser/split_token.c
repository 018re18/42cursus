/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:26:33 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/19 17:50:54 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_kai_init(t_split *split)
{
	split->splited_pipe_count = 0;
	split->count_flag = 0;
	split->token_count = 0;
	split->split_flag = 0;
	split->count = 0;
	split->i = 0;
	split->s_quarto_flag = 0;
	split->w_quarto_flag = 0;
}

void	add_flag(t_split *split, char *string)
{
	if (string[split->i] == '\'')
	{
		split->s_quarto_flag = 1;
	}
	if (string[split->i] == '\"')
	{
		split->w_quarto_flag = 1;
	}
	split->split_flag = 0;
}

void	last_malloc(t_split *split, char **splited_pipe, char *string)
{
	if (split->split_flag == 0)
	{
		splited_pipe[split->count] = malloc_and_push(string, split->i,
				split->count_flag);
		split->count++;
		split->split_flag = 1;
		split->i += 1;
	}
	splited_pipe[split->count] = NULL;
}

int	split_smbol_and_space(t_split *split, char **splited_pipe, char *string)
{
	int	continue_flag;

	continue_flag = 0;
	if (string[split->i] == ' ')
	{
		if (split_space(split, splited_pipe, string) == 1)
			continue_flag = 1;
	}
	else if ((string[split->i + 1] && ((string[split->i] == '>'
					&& string[split->i + 1] == '>') || (string[split->i] == '<'
					&& string[split->i + 1] == '<'))))
	{
		if (split_smbol_w(split, splited_pipe, string) == 1)
			continue_flag = 1;
	}
	else if ((string[split->i] == '|' || string[split->i] == '>'
			|| string[split->i] == '<'))
	{
		if (split_smbol_s(split, splited_pipe, string) == 1)
			continue_flag = 1;
	}
	return (continue_flag);
}

char	**split_kai(char *string, char **splited_pipe)
{
	t_split	split;

	split_kai_init(&split);
	while (string[split.i] != '\0')
	{
		if (split.s_quarto_flag == 0 && split.w_quarto_flag == 0)
		{
			if (split_smbol_and_space(&split, splited_pipe, string) == 1)
				continue ;
			add_flag(&split, string);
		}
		else if (split.s_quarto_flag == 1)
		{
			if (split.s_quarto_flag == 1 && string[split.i] == '\'')
				split.s_quarto_flag = 0;
		}
		else if (split.w_quarto_flag == 1)
		{
			if (split.w_quarto_flag == 1 && string[split.i] == '\"')
				split.w_quarto_flag = 0;
		}
		split.i++;
	}
	last_malloc(&split, splited_pipe, string);
	return (splited_pipe);
}
