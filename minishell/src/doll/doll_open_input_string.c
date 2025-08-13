/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doll_open_input_string.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:17:47 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/20 14:32:06 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	doller_open_input_string_normal_help(t_doller_open *doller)
{
	if (doller->opened_doller_word[0] == '$'
		&& doller->opened_doller_word[1] != '\0')
	{
		free(doller->opened_doller_word);
		doller->opened_doller_word = (char *)malloc(sizeof(char));
		doller->opened_doller_word[0] = '\0';
	}
	doller->k = 0;
	while (doller->opened_doller_word[doller->k] != '\0')
	{
		doller->result[doller->char_count] = \
		doller->opened_doller_word[doller->k];
		doller->char_count++;
		doller->k++;
	}
	if (doller->stop_flag != 0)
	{
		doller->result[doller->char_count] = doller->stop_flag;
		doller->char_count++;
	}
}

int	doller_open_input_string_normal(char *string, t_envp_data envp_data, \
	t_doller_open *doller)
{
	doller->j++;
	while (string[doller->i + doller->j] != '\0' && string[doller->i
			+ doller->j] != '\"' && is_al_num(string[doller->i
				+ doller->j]) == 0)
	{
		doller->j++;
	}
	doller->opened_doller_word = NULL;
	if (search_envp(doller->doller_word, envp_data) == 0)
	{
		doller->opened_doller_word = ft_doller(doller->doller_word, envp_data);
	}
	else
	{
		doller->opened_doller_word = (char *)malloc(sizeof(char));
		doller->opened_doller_word[0] = '\0';
	}
	free(doller->doller_word);
	doller_open_input_string_normal_help(doller);
	free(doller->opened_doller_word);
	return (2);
}

int	doller_open_input_string(char *string, t_envp_data envp_data,
		int exit_status, t_doller_open *doller)
{
	int	return_num;

	return_num = 0;
	if (string[doller->i] == '$')
	{
		doller->j = 0;
		if (!string[doller->i + 1] || (string[doller->i + 1]
				&& is_al_num(string[doller->i + 1]) == 1 && \
				string[doller->i + 1] != '?'))
		{
			return_num = doller_open_input_string_doll_only(doller);
		}
		else if (string[doller->i + 1] && string[doller->i + 1] == '?')
		{
			return_num = doller_open_input_string_doll_and_q(exit_status, \
				doller);
		}
		else
		{
			return_num = doller_open_input_string_normal(string, envp_data, \
				doller);
		}
	}
	return (return_num);
}

void	doller_open_input_string_quort_check(char *string, \
	t_doller_open *doller)
{
	if (string[doller->i] == '\'' && doller->w_quort_flag == 0)
	{
		if (doller->s_quort_flag == 0)
		{
			doller->s_quort_flag = 1;
		}
		else if (doller->s_quort_flag == 1)
		{
			doller->s_quort_flag = 0;
		}
	}
	if (string[doller->i] == '\"' && doller->s_quort_flag == 0)
	{
		if (doller->w_quort_flag == 0)
		{
			doller->w_quort_flag = 1;
		}
		else if (doller->w_quort_flag == 1)
		{
			doller->w_quort_flag = 0;
		}
	}
}

void	doller_open_input(char *string, t_envp_data envp_data, int exit_status,
		t_doller_open *doller)
{
	int	break_flag;

	while (string[doller->i] != '\0')
	{
		doller->j = 1;
		if (doller->s_quort_flag == 0)
		{
			break_flag = doller_open_input_string(string, envp_data,
					exit_status, doller);
			if (break_flag == 1)
				continue ;
			if (break_flag == 2)
				break ;
		}
		doller_open_input_string_quort_check(string, doller);
		doller->result[doller->char_count] = string[doller->i];
		doller->char_count++;
		doller->i = doller->i + doller->j;
	}
}
