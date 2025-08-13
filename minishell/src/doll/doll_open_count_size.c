/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doll_open_count_size.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:55:59 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/20 14:30:33 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	doller_open_count_open_normal_help(char *string, t_doller_open *doller)
{
	doller->j++;
	while (string[doller->i + doller->j] != '\0' && string[doller->i
			+ doller->j] != '\"' && is_al_num(string[doller->i
				+ doller->j]) == 0)
		doller->j++;
	if (string[doller->i + doller->j] == '\"' || is_al_num(string[doller->i
				+ doller->j]) == 1)
	{
		doller->stop_flag = string[doller->i + doller->j];
		doller->stop_flag_int = 1;
		doller->j++;
	}
	doller->doller_word = (char *)malloc(sizeof(char) * (doller->j + 1));
	doller->j = 0;
	doller->doller_word[doller->j] = string[doller->i + doller->j];
	doller->j++;
	while ((string[doller->i + doller->j] != '\0' && string[doller->i
				+ doller->j] != '\"' && is_al_num(string[doller->i
					+ doller->j]) == 0))
	{
		doller->doller_word[doller->j] = string[doller->i + doller->j];
		doller->j++;
	}
	doller->doller_word[doller->j] = '\0';
}

int	doller_open_count_open_normal(char *string, t_envp_data envp_data, \
	t_doller_open *doller)
{
	doller_open_count_open_normal_help(string, doller);
	if (search_envp(doller->doller_word, envp_data) == 0)
	{
		doller->opened_doller_word = ft_doller(doller->doller_word, envp_data);
	}
	else
	{
		doller->opened_doller_word = (char *)malloc(sizeof(char));
		doller->opened_doller_word[0] = '\0';
	}
	doller->k = 0;
	while (doller->opened_doller_word[doller->k] != '\0')
	{
		doller->k++;
		doller->char_count++;
	}
	free(doller->opened_doller_word);
	return (2);
}

int	doller_open_count_open(char *string, t_envp_data envp_data, int exit_status,
		t_doller_open *doller)
{
	if (string[doller->i] == '$')
	{
		doller->j = 0;
		if (!string[doller->i + 1] || (string[doller->i + 1]
				&& is_al_num(string[doller->i + 1]) == 1 && string[doller->i
					+ 1] != '?'))
		{
			doller->char_count = doller->char_count + 1;
			doller->i = doller->i + 1;
			return (1);
		}
		else if (string[doller->i + 1] && string[doller->i + 1] == '?')
		{
			doller->string_exit_status = ft_itoa(exit_status);
			doller->char_count = doller->char_count
				+ ft_strlen(doller->string_exit_status);
			doller->i = doller->i + 2;
			free(doller->string_exit_status);
			return (1);
		}
		else
			return (doller_open_count_open_normal(string, envp_data, doller));
	}
	return (0);
}

void	doller_open_count_quort_check(char *string, t_doller_open *doller)
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

void	doller_open_count_size(char *string, t_envp_data envp_data,
		int exit_status, t_doller_open *doller)
{
	int	break_flag;

	while (string[doller->i] != '\0')
	{
		doller->j = 1;
		if (doller->s_quort_flag == 0)
		{
			break_flag = doller_open_count_open(string, envp_data, exit_status,
					doller);
			if (break_flag == 1)
				continue ;
			else if (break_flag == 2)
				break ;
		}
		doller_open_count_quort_check(string, doller);
		doller->char_count++;
		doller->i = doller->i + doller->j;
	}
	doller->result = (char *)malloc(sizeof(char) * (doller->char_count + 1
				+ doller->stop_flag_int));
}
