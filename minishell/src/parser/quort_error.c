/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quort_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:24:35 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/19 18:33:26 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quort_error_count(char *string, t_quort_error *quort)
{
	while (string[quort->i] != '\0')
	{
		if (quort->s_quort_count_flag == 0 && quort->w_quort_count_flag == 0)
		{
			if (string[quort->i] == '\"')
			{
				quort->w_quort_count++;
				quort->w_quort_count_flag = 1;
			}
			if (string[quort->i] == '\'')
			{
				quort->s_quort_count++;
				quort->s_quort_count_flag = 1;
			}
		}
		else
		{
			if (quort->w_quort_count_flag == 1 && string[quort->i] == '\"')
				quort->w_quort_count_flag = 0;
			if (quort->s_quort_count_flag == 1 && string[quort->i] == '\'')
				quort->s_quort_count_flag = 0;
		}
		quort->i++;
	}
}

int	quort_error(char *string)
{
	t_quort_error	quort;

	quort.s_quort_count_flag = 0;
	quort.w_quort_count_flag = 0;
	quort.i = 0;
	quort.s_quort_count = 0;
	quort.w_quort_count = 0;
	quort_error_count(string, &quort);
	if (quort.s_quort_count_flag == 0 && quort.w_quort_count_flag == 0)
	{
		return (TRUE);
	}
	else
	{
		if (quort.s_quort_count_flag != 0)
		{
			write(2, "minishell: syntax error near unexpected token\'\n", 47);
		}
		if (quort.w_quort_count_flag != 0)
		{
			write(2, "minishell: syntax error near unexpected token\"\n", 47);
		}
		return (FALSE);
	}
}
