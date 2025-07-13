/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:16:34 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/11 12:56:42 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	str_cpy(char *dest, const char *src, int plase)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[plase + i] = src[i];
		i++;
	}
	// printf("strcpy_count %d\n",i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str)
		return (NULL);
	str_cpy(str, s1, 0);
	str_cpy(str, s2, s1_len);
	str[s1_len + s2_len] = '\0';
	return (str);
}

t_envp_data	cd_error_no_such(t_envp_data envp_data, char **args,
		int *exit_status, char *prev_pwd)
{
	free(prev_pwd);
	write(2, "minishell: cd: ", 15);
	write(2, args[1], ft_strlen(args[1]));
	write(2, ": No such file or directory\n", 28);
	*exit_status = 1;
	return (envp_data);
}

t_envp_data	cd_error_many(t_envp_data envp_data, char *prev_pwd,
		int *exit_status)
{
	free(prev_pwd);
	write(2, "minishell: cd: too many arguments\n", 34);
	*exit_status = 1;
	return (envp_data);
}

t_envp_data	ft_cd_help(t_envp_data envp_data, char **args, int *exit_status)
{
	char	*prev_pwd;
	char	*new_pwd;
	char	*joined_new_pwd;
	int		i;

	prev_pwd = ft_doller("OLDPWD=$PWD", envp_data);
	i = 0;
	while (args[i])
		i++;
	if (i > 2)
		return (cd_error_many(envp_data, prev_pwd, exit_status));
	if (!args[1])
	{
		new_pwd = ft_doller("$HOME", envp_data);
		if (chdir(new_pwd) == -1)
		{
			free(prev_pwd);
			free(new_pwd);
			return (cd_error_no_such(envp_data, args, exit_status, prev_pwd));
		}
		free(new_pwd);
	}
	else if (chdir(args[1]) == -1)
		return (cd_error_no_such(envp_data, args, exit_status, prev_pwd));
	envp_data = add_envp(envp_data, prev_pwd);
	new_pwd = getcwd(NULL, 0);
	joined_new_pwd = ft_strjoin("PWD=", new_pwd);
	envp_data = add_envp(envp_data, joined_new_pwd);
	free(joined_new_pwd);
	free(prev_pwd);
	free(new_pwd);
	*exit_status = 0;
	return (envp_data);
}

int	ft_cd(t_envp_data *envp_data, char **args)
{
	int	exit_status;

	exit_status = 0;
	*envp_data = ft_cd_help(*envp_data, args, &exit_status);
	return (exit_status);
}
