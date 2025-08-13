/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_token_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:40:38 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/19 18:36:59 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_token_space(t_count_token *token_info)
{
	if (token_info->i == 0)
	{
		token_info->count--;
	}
	if (token_info->split_flag == 0)
	{
		token_info->count++;
		token_info->split_flag = 1;
		token_info->i += 1;
		return (1);
	}
	else if (token_info->split_flag == 1)
	{
		token_info->split_flag = 1;
		token_info->i += 1;
		return (1);
	}
	return (0);
}

int	count_token_before_symbol(t_count_token *token_info)
{
	if (token_info->i == 0)
		token_info->count--;
	if (token_info->split_flag == 0)
	{
		token_info->count++;
		token_info->token_count++;
		token_info->split_flag = 1;
		token_info->i += 2;
		return (1);
	}
	else if (token_info->split_flag == 1)
	{
		token_info->token_count++;
		token_info->split_flag = 1;
		token_info->i += 2;
		return (1);
	}
	return (0);
}

int	count_token_symbol(t_count_token *token_info)
{
	if (token_info->i == 0)
	{
		token_info->count--;
	}
	if (token_info->split_flag == 0)
	{
		token_info->count++;
		token_info->token_count++;
		token_info->split_flag = 1;
		token_info->i += 1;
		return (1);
	}
	else if (token_info->split_flag == 1)
	{
		token_info->token_count++;
		token_info->split_flag = 1;
		token_info->i += 1;
		return (1);
	}
	return (0);
}

int	count_token_help(char *string, t_count_token *token_info)
{
	if (string[token_info->i] == ' ')
	{
		if (count_token_space(token_info) == 1)
			return (1);
	}
	else if ((string[token_info->i + 1] && ((string[token_info->i] == '>'
					&& string[token_info->i + 1] == '>') || \
					(string[token_info->i] == '<' && string[token_info->i
						+ 1] == '<'))))
	{
		if (count_token_before_symbol(token_info) == 1)
			return (1);
	}
	else if ((string[token_info->i] == '|' || string[token_info->i] == '>'
			|| string[token_info->i] == '<'))
	{
		if (count_token_symbol(token_info) == 1)
			return (1);
	}
	if (string[token_info->i] == '\'')
		token_info->s_quarto_flag = 1;
	if (string[token_info->i] == '\"')
		token_info->w_quarto_flag = 1;
	token_info->split_flag = 0;
	return (0);
}
