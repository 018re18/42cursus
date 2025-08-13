/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doll.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:33:54 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/21 14:28:46 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_doller_make_key_capacity(char *token, t_doll *doll)
{
	while (token[doll->i] != '\0')
	{
		if (token[doll->i] == '$')
		{
			doll->j = doll->i;
			while (token[doll->i] != '\0')
			{
				doll->i++;
			}
			doll->key = (char *)malloc(sizeof(char) * (doll->i - doll->j));
			doll->i = doll->j + 1;
			while (token[doll->i] != '\0')
			{
				doll->key[doll->i - doll->j - 1] = token[doll->i];
				doll->i++;
			}
			doll->key[doll->i - doll->j - 1] = '\0';
			doll->doller_flag = 1;
			break ;
		}
		doll->i++;
	}
}

void	ft_doller_make_capacity(char *token, t_envp_data envp_data,
		t_doll *doll)
{
	doll->doller_flag = 0;
	doll->i = 0;
	while (token[doll->i] != '\0')
	{
		if (token[doll->i] == '$')
		{
			while (envp_data.envp[doll->envp_count])
			{
				if (cmp_key(doll->key, envp_data.envp[doll->envp_count]) == 0)
				{
					doll->j = 0;
					while (envp_data.envp[doll->envp_count][doll->j] != '\0')
						doll->j++;
					while (doll->key[doll->key_char_count] != '\0')
						doll->key_char_count++;
					break ;
				}
				doll->envp_count++;
			}
		}
		doll->i++;
	}
	doll->result = (char *)malloc(sizeof(char) * (doll->i + doll->j
				- doll->key_char_count + 1));
}

int	ft_doller_make_result_help(t_envp_data envp_data, t_doll *doll)
{
	if (cmp_key(doll->key, envp_data.envp[doll->envp_count]) == 0)
	{
		doll->j = 0;
		while (envp_data.envp[doll->envp_count][doll->j + doll->key_char_count
			+ 1] != '\0')
		{
			doll->result[doll->i
				+ doll->j] = envp_data.envp[doll->envp_count][doll->j
				+ doll->key_char_count + 1];
			doll->j++;
		}
		doll->doller_flag = 1;
		return (1);
	}
	return (0);
}

void	ft_doller_make_result(char *token, t_envp_data envp_data, t_doll *doll)
{
	while (token[doll->i] != '\0')
	{
		if (token[doll->i] == '$')
		{
			while (envp_data.envp[doll->envp_count])
			{
				if (ft_doller_make_result_help(envp_data, doll) == 1)
					break ;
				doll->envp_count++;
			}
		}
		if (doll->doller_flag == 1)
			break ;
		doll->result[doll->i] = token[doll->i];
		doll->i++;
	}
	doll->result[doll->i + doll->j] = '\0';
}

char	*ft_doller(char *token, t_envp_data envp_data)
{
	t_doll	doll;

	doll.envp_count = 0;
	doll.key_char_count = 0;
	doll.i = 0;
	doll.j = 0;
	doll.doller_flag = 0;
	ft_doller_make_key_capacity(token, &doll);
	ft_doller_make_capacity(token, envp_data, &doll);
	doll.i = 0;
	doll.envp_count = 0;
	ft_doller_make_result(token, envp_data, &doll);
	free(doll.key);
	return (doll.result);
}
