/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:52:16 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/19 18:33:57 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_option_n(char **cmd_and_option, int argc, int *i)
{
	int	n_flag;
	int	skip_n;

	n_flag = 0;
	while (*i < argc && cmd_and_option[*i][0] == '-'
		&& cmd_and_option[*i][1] == 'n')
	{
		skip_n = 2;
		while (cmd_and_option[*i][skip_n] == 'n')
			skip_n++;
		if (cmd_and_option[*i][skip_n] != '\0')
			break ;
		(*i)++;
		n_flag = 1;
	}
	return (n_flag);
}

int	ft_echo(char **cmd_and_option)
{
	int	argc;
	int	i;
	int	n_flag;

	argc = count_arg(cmd_and_option);
	i = 1;
	n_flag = check_option_n(cmd_and_option, argc, &i);
	while (i < argc)
	{
		write(1, cmd_and_option[i], ft_strlen(cmd_and_option[i]));
		if (i < argc - 1)
			write(1, " ", 1);
		i++;
	}
	if (n_flag == 0)
		write(1, "\n", 1);
	return (0);
}
