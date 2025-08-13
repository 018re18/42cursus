/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:37:28 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/19 18:37:21 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_token_init(t_count_token *token_info)
{
	token_info->token_count = 0;
	token_info->split_flag = 0;
	token_info->count = 1;
	token_info->i = 0;
	token_info->s_quarto_flag = 0;
	token_info->w_quarto_flag = 0;
}

void	count_token_reduce(char *string, t_count_token *token_info)
{
	if (string[token_info->i - 1] == '<' || string[token_info->i - 1] == '>'
		|| string[token_info->i - 1] == '|')
		token_info->count--;
	token_info->count = token_info->count + token_info->token_count;
}

int	count_token(char *string)
{
	t_count_token	token_info;

	count_token_init(&token_info);
	while (string[token_info.i] != '\0')
	{
		if (token_info.s_quarto_flag == 0 && token_info.w_quarto_flag == 0)
		{
			if (count_token_help(string, &token_info) == 1)
				continue ;
		}
		else if (token_info.s_quarto_flag == 1)
		{
			if (token_info.s_quarto_flag == 1 && string[token_info.i] == '\'')
				token_info.s_quarto_flag = 0;
		}
		else if (token_info.w_quarto_flag == 1)
		{
			if (token_info.w_quarto_flag == 1 && string[token_info.i] == '\"')
				token_info.w_quarto_flag = 0;
		}
		token_info.i++;
	}
	count_token_reduce(string, &token_info);
	return (token_info.count);
}
