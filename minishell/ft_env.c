/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:12:33 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/10 13:24:09 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp_data	ft_env(t_envp_data envp_data, t_execve_num *num, char **cmd)
{
	int		i;
	char	*key;

	i = 0;
	while (cmd[i])
		i++;
	if (i != 1)
	{
		write(2, "env: '", 6);
		write(2, cmd[1], ft_strlen(cmd[1]));
		write(2, "': No such file or directory\n", 29);
		num->exit_status = 127;
		return (envp_data);
	}
	i = 0;
	while (envp_data.envp[i])
	{
		key = set_key(envp_data.envp[i]);
		if (envp_data.envp[i][ft_strlen(key)] == '=')
			printf("%s\n", envp_data.envp[i]);
		free(key);
		i++;
	}
	num->exit_status = 0;
	return (envp_data);
}
