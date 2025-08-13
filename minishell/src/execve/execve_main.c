/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:20:57 by rookuma           #+#    #+#             */
/*   Updated: 2025/07/21 17:27:44 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_execve_signal(t_execve_num *num)
{
	sigaction(SIGINT, NULL, &num->saved);
	sigaction(SIGQUIT, NULL, &num->saved_quit);
	num->g_sa.sa_handler = SIG_IGN;
	sigemptyset(&num->g_sa.sa_mask);
	num->g_sa.sa_flags = 0;
	sigaction(SIGINT, &num->g_sa, NULL);
	sigaction(SIGQUIT, &num->g_sa, NULL);
}

static int	make_operate(t_token *line, t_cmd_cnk **operate, int operate_count,
		int *status)
{
	int	i;

	*operate = make_cmd_cnk(line, operate_count, status);
	i = 0;
	while (line[i].str)
	{
		free(line[i].str);
		i++;
	}
	free(line);
	if (!*operate)
	{
		return (FALSE);
	}
	return (TRUE);
}

int	execve_main(t_token *line, t_envp_data *my_envp, int exit_status)
{
	t_execve_num	num;
	t_cmd_cnk		*operate;
	int				result;
	int				status;

	set_execve_signal(&num);
	num.exit_status = exit_status;
	status = 0;
	num.operate_count = count_all_cmd(line);
	if (num.operate_count == 0)
		return (write_cmd_error(line, &num));
	if (!make_operate(line, &operate, num.operate_count, &status))
	{
		sigaction(SIGINT, &num.saved, NULL);
		sigaction(SIGQUIT, &num.saved_quit, NULL);
		return (status);
	}
	if (num.operate_count == 1)
		result = execve_cmd_single(my_envp, operate, &num);
	else
		result = execve_pipeline(my_envp, operate, &num);
	sigaction(SIGINT, &num.saved, NULL);
	sigaction(SIGQUIT, &num.saved_quit, NULL);
	return (result);
}
