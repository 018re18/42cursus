/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:37:28 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/19 17:48:43 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_init_help(char **envp, t_envp_data *result)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	result->envp_count = i;
	result->envp_volume = i;
	result->envp = (char **)malloc(sizeof(char *) * (i + 1));
}

t_envp_data	envp_init(char **envp)
{
	int			i;
	int			j;
	t_envp_data	result;

	env_init_help(envp, &result);
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '\0')
			j++;
		result.envp[i] = (char *)malloc(sizeof(char) * (j + 1));
		j = 0;
		while (envp[i][j] != '\0')
		{
			result.envp[i][j] = envp[i][j];
			j++;
		}
		result.envp[i][j] = '\0';
		i++;
	}
	result.envp[i] = NULL;
	return (result);
}

int	cmp_key(const char *key, const char *str)
{
	int	i;

	i = 0;
	if (!key || !str)
		return (1);
	while (key[i] != '\0' && str[i] != '\0' && key[i] == str[i])
	{
		i++;
	}
	if (key[i] == '\0' && str[i] == '=')
		return (0);
	return (1);
}

char	*set_key(char *key_and)
{
	int		i;
	char	*key;

	i = 0;
	while (key_and[i] != '\0' && key_and[i] != '=')
		i++;
	key = (char *)malloc(sizeof(char) * i + 1);
	i = 0;
	while (key_and[i] != '\0' && key_and[i] != '=')
	{
		key[i] = key_and[i];
		i++;
	}
	key[i] = '\0';
	i = 0;
	while (key[i] != '\0')
	{
		if (key[i] == '+')
		{
			key[i] = '\0';
		}
		i++;
	}
	return (key);
}

t_envp_data	envp_line_up(t_envp_data envp_data)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (envp_data.envp[i] != NULL)
	{
		j = i + 1;
		while (envp_data.envp[j] != NULL)
		{
			if (ft_strcmp(envp_data.envp[i], envp_data.envp[j]) > 0)
			{
				tmp = envp_data.envp[j];
				envp_data.envp[j] = envp_data.envp[i];
				envp_data.envp[i] = tmp;
			}
			j++;
		}
		i++;
	}
	return (envp_data);
}
