/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quort_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:40:09 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/19 17:50:03 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quort_check_start_make_result(char *string, t_quort_check *quort)
{
	if (string[quort->i] == '\"')
	{
		quort->count_quort++;
		quort->w_quarto_flag = 1;
		quort->i++;
		return (1);
	}
	else if (string[quort->i] == '\'')
	{
		quort->count_quort++;
		quort->s_quarto_flag = 1;
		quort->i++;
		return (1);
	}
	return (0);
}

int	quort_check_end_make_result(char *string, t_quort_check *quort)
{
	if (string[quort->i] == '\"' && quort->w_quarto_flag == 1
		&& quort->s_quarto_flag == 0)
	{
		quort->count_quort++;
		quort->w_quarto_flag = 0;
		quort->i++;
		return (1);
	}
	else if (string[quort->i] == '\'' && quort->s_quarto_flag == 1
		&& quort->w_quarto_flag == 0)
	{
		quort->count_quort++;
		quort->s_quarto_flag = 0;
		quort->i++;
		return (1);
	}
	return (0);
}

void	quort_check_make_result(char *string, t_quort_check *quort)
{
	while (string[quort->i] != '\0')
	{
		if (quort->w_quarto_flag == 0 && quort->s_quarto_flag == 0)
		{
			if (quort_check_start_make_result(string, quort) == 1)
				continue ;
		}
		else
		{
			if (quort_check_end_make_result(string, quort) == 1)
				continue ;
		}
		quort->result[quort->i - quort->count_quort] = string[quort->i];
		quort->i++;
	}
}
