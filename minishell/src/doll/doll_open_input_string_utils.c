/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doll_open_input_string_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:20:06 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/20 14:12:27 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_al_num(char c)
{
	if (('0' <= c && c <= '9') || ('a' <= c && c <= 'z') || ('A' <= c
			&& c <= 'Z') || (c == '_'))
		return (0);
	return (1);
}

int	doller_open_input_string_doll_only(t_doller_open *doller)
{
	doller->string_exit_status = (char *)malloc(sizeof(char) * 2);
	doller->string_exit_status[0] = '$';
	doller->string_exit_status[1] = '\0';
	while (doller->j < ft_strlen(doller->string_exit_status))
	{
		doller->result[doller->char_count] = \
		doller->string_exit_status[doller->j];
		doller->char_count++;
		doller->j++;
	}
	free(doller->string_exit_status);
	doller->j = 0;
	doller->i = doller->i + 1;
	return (1);
}

int	doller_open_input_string_doll_and_q(int exit_status, t_doller_open *doller)
{
	doller->string_exit_status = ft_itoa(exit_status);
	while (doller->j < ft_strlen(doller->string_exit_status))
	{
		doller->result[doller->char_count] = \
		doller->string_exit_status[doller->j];
		doller->char_count++;
		doller->j++;
	}
	free(doller->string_exit_status);
	doller->j = 0;
	doller->i = doller->i + 2;
	return (1);
}
