/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:12:33 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/19 15:34:56 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_error(t_execve_num *num, char **cmd)
{
	write(2, "env: '", 6);
	write(2, cmd[1], ft_strlen(cmd[1]));
	write(2, "': No such file or directory\n", 29);
	num->exit_status = 127;
}

t_envp_data	ft_env(t_envp_data envp_data, t_execve_num *num, char **cmd)
{
	int		i;
	char	*key;

	i = 0;
	while (cmd[i])
		i++;
	if (i != 1)
	{
		env_error(num, cmd);
		return (envp_data);
	}
	i = 0;
	while (envp_data.envp[i])
	{
		key = set_key(envp_data.envp[i]);
		if (envp_data.envp[i][ft_strlen(key)] == '=')
		{
			write(1, envp_data.envp[i], ft_strlen(envp_data.envp[i]));
			write(1, "\n", 1);
		}
		free(key);
		i++;
	}
	num->exit_status = 0;
	return (envp_data);
}
