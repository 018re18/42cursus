/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quort_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:38:26 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/19 18:32:52 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quort_check_init(t_quort_check *quort)
{
	quort->result = NULL;
	quort->count_quort = 0;
	quort->w_quarto_flag = 0;
	quort->s_quarto_flag = 0;
	quort->i = 0;
}

void	quort_check_delete_count(char *string, t_quort_check *quort)
{
	while (string[quort->i] != '\0')
	{
		if (quort->s_quarto_flag == 0 && quort->w_quarto_flag == 0)
		{
			if (string[quort->i] == '\'')
			{
				quort->count_quort++;
				quort->s_quarto_flag = 1;
			}
			if (string[quort->i] == '\"')
			{
				quort->count_quort++;
				quort->w_quarto_flag = 1;
			}
		}
		else
		{
			if (string[quort->i] == '\"' && quort->s_quarto_flag == 1)
				quort->w_quarto_flag = 0;
			if (string[quort->i] == '\'' && quort->w_quarto_flag == 1)
				quort->s_quarto_flag = 0;
		}
		quort->i++;
	}
}

char	*quort_check(char *string)
{
	t_quort_check	quort;

	quort_check_init(&quort);
	quort_check_delete_count(string, &quort);
	quort.result = (char *)malloc(sizeof(char) * (quort.i - quort.count_quort
				* 2 + 1));
	quort.i = 0;
	quort.count_quort = 0;
	quort.w_quarto_flag = 0;
	quort.s_quarto_flag = 0;
	quort_check_make_result(string, &quort);
	quort.result[quort.i - quort.count_quort] = '\0';
	free(string);
	return (quort.result);
}
