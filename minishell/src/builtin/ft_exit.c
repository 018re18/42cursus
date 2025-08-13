/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:46:10 by rookuma           #+#    #+#             */
/*   Updated: 2025/07/21 14:49:39 by kryutaro         ###   ########.fr       */
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

static void	exit_error_null(void)
{
	write(2, "minishell: exit: : numeric argument required\n", 45);
	exit(2);
}

static void	free_cnk_envp_dup2(t_cmd_cnk *operate, t_envp_data *envp_data,
		t_execve_num *num)
{
	free_operate(operate, 1);
	free_envp(envp_data);
	dup2(num->save_stdin, STDIN_FILENO);
	dup2(num->save_stdout, STDOUT_FILENO);
	close(num->save_stdin);
	close(num->save_stdout);
}

int	ft_exit(t_cmd_cnk *operate, int place, t_execve_num *num,
		t_envp_data *envp_data)
{
	int				argc;
	long long		arg_num;
	unsigned char	exit_num;

	argc = count_arg(operate[place].cmd);
	if (num->operate_count == 1)
		write(1, "exit\n", 5);
	if (argc == 1)
	{
		if (num->operate_count == 1)
			free_cnk_envp_dup2(operate, envp_data, num);
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
		free_cnk_envp_dup2(operate, envp_data, num);
	exit(exit_num);
}
