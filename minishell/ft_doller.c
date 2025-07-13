/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doller.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:54:09 by kryutaro          #+#    #+#             */
/*   Updated: 2025/06/25 17:39:16 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_envp_data
{
	char	**envp;
	int		envp_cokeunt;
	int		envp_volume;
	char	**key;

}			t_envp_data;

char	*ft_doller(char *token, t_envp_data envp_data)
{
	char	*key;
	char	*result;
	int		doller_flag;
	int		i;
	int		j;
	int		key_char_count;
	int		envp_count;

	envp_count = 0;
	key_char_count = 0;
	i = 0;
	doller_flag = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '$')
		{
			j = i;
			while (token[i] != '\0')
			{
				i++;
			}
			key = (char *)malloc(sizeof(char) * (i - j));
			i = j + 1;
			while (token[i] != '\0')
			{
				key[i - j - 1] = token[i];
				i++;
			}
			key[i - j - 1] = '\0';
			doller_flag = 1;
			break ;
		}
		i++;
	}
	doller_flag = 0;
	i = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '$')
		{
			while (envp_data.envp[envp_count])
			{
				if (cmp_key(key, envp_data.envp[envp_count]) == 0)
				{
					j = 0;
					while (envp_data.envp[envp_count][j] != '\0')
					{
						j++;
					}
					while (key[key_char_count] != '\0')
					{
						key_char_count++;
					}
					break ;
				}
				envp_count++;
			}
		}
		i++;
	}
	printf("    %d\n", i + j - key_char_count + 1);
	result = (char *)malloc(sizeof(char) * (i + j - key_char_count + 1));
	i = 0;
	envp_count = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '$')
		{
			while (envp_data.envp[envp_count])
			{
				if (cmp_key(key, envp_data.envp[envp_count]) == 0)
				{
					j = 0;
					while (envp_data.envp[envp_count][j + key_char_count
						+ 1] != '\0')
					{
						result[i + j] = envp_data.envp[envp_count][j
							+ key_char_count + 1];
						j++;
					}
					doller_flag = 1;
					break ;
				}
				envp_count++;
			}
		}
		if (doller_flag == 1)
			break ;
		result[i] = token[i];
		i++;
	}
	return (result);
}
