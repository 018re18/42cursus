/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:46:10 by rookuma           #+#    #+#             */
/*   Updated: 2025/07/13 16:30:07 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_arg(char **arg)
{
	int	argc;

	argc = 0;
	while (arg[argc])
		argc++;
	return (argc);
}

int	exit_atoi_sign(t_cmd_cnk *operate, int place, t_builtin_exit_num *exit_n)
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

void	exit_atoi_init(t_cmd_cnk *operate, int place,
		t_builtin_exit_num *exit_n)
{
	exit_n->index = 0;
	exit_n->sign = exit_atoi_sign(operate, place, exit_n);
	exit_n->arg_num = 0;
}

void	write_exit_error(t_cmd_cnk *operate, int place)
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

int	ft_isdigit(int c)
{
	if (48 <= c && c <= 57)
	{
		return (TRUE);
	}
	return (FALSE);
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

void	exit_error_null(void)
{
	write(2, "minishell: exit: : numeric argument required\n", 45);
	exit(2);
	// exit(255);
}

int	ft_exit(t_cmd_cnk *operate, int place, t_execve_num *num,
		t_envp_data *envp_data)
{
	int				argc;
	long long		arg_num;
	unsigned char	exit_num;

	argc = count_arg(operate[place].cmd);
	if (num->operate_count == 1)
		printf("exit\n");
	if (argc == 1)
	{
		if (num->operate_count == 1)
			free_cnk_envp(operate, envp_data);
		exit(num->exit_status);
	}
	if (operate[place].cmd[1][0] == '\0')
		exit_error_null();
	arg_num = exit_atoi(operate, place, num, envp_data);
	if (argc > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	exit_num = (unsigned char)arg_num;
	if (num->operate_count == 1)
		free_cnk_envp(operate, envp_data);
	exit(exit_num);
}
