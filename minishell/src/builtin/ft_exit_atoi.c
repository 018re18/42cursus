/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_atoi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:37:22 by rookuma           #+#    #+#             */
/*   Updated: 2025/07/19 19:00:14 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_atoi_sign(t_cmd_cnk *operate, int place,
		t_builtin_exit_num *exit_n)
{
	int	sign;

	sign = 1;
	if (operate[place].cmd[1][exit_n->index] == '+'
		|| operate[place].cmd[1][exit_n->index] == '-')
	{
		if (operate[place].cmd[1][exit_n->index] == '-')
			sign = -1;
		exit_n->index++;
	}
	return (sign);
}

static void	exit_atoi_init(t_cmd_cnk *operate, int place,
		t_builtin_exit_num *exit_n)
{
	exit_n->index = 0;
	exit_n->sign = exit_atoi_sign(operate, place, exit_n);
	exit_n->arg_num = 0;
}

static void	write_exit_error(t_cmd_cnk *operate, int place)
{
	write(2, "minishell: exit: ", 17);
	write(2, operate[place].cmd[1], ft_strlen(operate[place].cmd[1]));
	write(2, ": numeric argument required\n", 28);
}

void	free_cnk_envp(t_cmd_cnk *operate, t_envp_data *envp_data)
{
	free_operate(operate, 1);
	free_envp(envp_data);
}

long long	exit_atoi(t_cmd_cnk *operate, int place, t_execve_num *num,
		t_envp_data *envp_data)
{
	t_builtin_exit_num	exit_n;

	exit_atoi_init(operate, place, &exit_n);
	while (operate[place].cmd[1][exit_n.index])
	{
		if (!ft_isdigit(operate[place].cmd[1][exit_n.index]))
		{
			write_exit_error(operate, place);
			if (num->operate_count == 1)
				free_cnk_envp(operate, envp_data);
			exit(2);
		}
		exit_n.tmp_num = exit_n.arg_num;
		exit_n.arg_num = exit_n.arg_num * 10
			+ (operate[place].cmd[1][exit_n.index] - '0');
		if (exit_n.arg_num / 10 != exit_n.tmp_num)
		{
			write_exit_error(operate, place);
			if (num->operate_count == 1)
				free_cnk_envp(operate, envp_data);
			exit(2);
		}
		exit_n.index++;
	}
	return (exit_n.arg_num * exit_n.sign);
}
