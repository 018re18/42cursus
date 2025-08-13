/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execve_path.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:18:30 by rookuma           #+#    #+#             */
/*   Updated: 2025/07/19 17:19:20 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_strcpy_path(char *dest, const char *src, int plase)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[plase + i] = src[i];
		i++;
	}
}

static char	*ft_strjoin_path(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 2));
	if (!str)
		return (NULL);
	ft_strcpy_path(str, s1, 0);
	str[s1_len] = '/';
	ft_strcpy_path(str, s2, s1_len + 1);
	str[s1_len + s2_len + 1] = '\0';
	return (str);
}

static void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static int	check_path(char *cmd, char **path, char **all_path)
{
	int		i;
	char	*test_path;

	i = 0;
	while (all_path[i])
	{
		test_path = ft_strjoin_path(all_path[i], cmd);
		if (!test_path)
			return (1);
		if (access(test_path, F_OK) == 0)
		{
			if (access(test_path, X_OK) == 0)
			{
				*path = test_path;
				return (0);
			}
			free(test_path);
			return (126);
		}
		free(test_path);
		i++;
	}
	return (127);
}

int	get_path(char *cmd, char **envp, char **path)
{
	int		i;
	int		exit_judge;
	char	**all_path;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (127);
	all_path = ft_split(envp[i] + 5, ':');
	if (!all_path)
		return (1);
	exit_judge = check_path(cmd, path, all_path);
	free_split(all_path);
	return (exit_judge);
}
