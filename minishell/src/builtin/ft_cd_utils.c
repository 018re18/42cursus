/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:27:59 by rookuma           #+#    #+#             */
/*   Updated: 2025/07/29 13:32:11 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_count_arg(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

static t_envp_data	cd_error_no_such(t_envp_data envp_data, int *exit_status,
		char *prev_pwd)
{
	free(prev_pwd);
	write(2, "minishell: cd: ", 15);
	write(2, ": No such file or directory\n", 28);
	*exit_status = 1;
	return (envp_data);
}

static t_envp_data	cd_error_many(t_envp_data envp_data, char *prev_pwd,
		int *exit_status)
{
	free(prev_pwd);
	write(2, "minishell: cd: too many arguments\n", 34);
	*exit_status = 1;
	return (envp_data);
}

static t_envp_data	update_pwd(t_envp_data envp_data, char *prev_pwd)
{
	char	*new_pwd;
	char	*joined_new_pwd;

	envp_data = add_envp(envp_data, prev_pwd);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (envp_data);
	joined_new_pwd = ft_strjoin("PWD=", new_pwd);
	free(new_pwd);
	envp_data = add_envp(envp_data, joined_new_pwd);
	free(joined_new_pwd);
	return (envp_data);
}

t_envp_data	ft_cd_help(t_envp_data envp_data, char **args, int *exit_status)
{
	char	*prev_pwd;
	char	*new_pwd;
	int		count_arg;

	prev_pwd = doller_open_help("OLDPWD=$PWD", envp_data, *exit_status);
	count_arg = cd_count_arg(args);
	if (count_arg > 2)
		return (cd_error_many(envp_data, prev_pwd, exit_status));
	if (!args[1])
	{
		new_pwd = ft_doller("$HOME", envp_data);
		if (chdir(new_pwd) == -1)
		{
			free(new_pwd);
			return (cd_error_no_such(envp_data, exit_status, prev_pwd));
		}
		free(new_pwd);
	}
	else if (chdir(args[1]) == -1)
		return (cd_error_no_such(envp_data, exit_status, prev_pwd));
	envp_data = update_pwd(envp_data, prev_pwd);
	free(prev_pwd);
	*exit_status = 0;
	return (envp_data);
}
