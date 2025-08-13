/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:29:41 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/21 14:29:58 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_envp_help(t_envp_data *prev_envp_data, char *key_and, t_add_envp *a)
{
	while (prev_envp_data->envp[a->i] != NULL)
	{
		if (cmp_key(a->key, prev_envp_data->envp[a->i]) == 0)
			a->key_flag = 1;
		a->j = 0;
		while (prev_envp_data->envp[a->i][a->j] != '\0')
			a->j++;
		a->new_envp_data.envp[a->i] = (char *)malloc(sizeof(char) * (a->j + 1));
		a->j = 0;
		while (prev_envp_data->envp[a->i][a->j] != '\0')
		{
			a->new_envp_data.envp[a->i][a->j]
				= prev_envp_data->envp[a->i][a->j];
			a->j++;
		}
		a->new_envp_data.envp[a->i][a->j] = '\0';
		free(prev_envp_data->envp[a->i]);
		a->i++;
	}
	a->j = 0;
	while (key_and[a->j] != '\0')
		a->j++;
	a->new_envp_data.envp[a->i] = (char *)malloc(sizeof(char) * (a->j + 1));
	a->j = 0;
}

t_envp_data	add_envp(t_envp_data prev_envp_data, char *key_and)
{
	t_add_envp	add;

	add.key_flag = 0;
	add.key = set_key(key_and);
	add.new_envp_data.envp = (char **)malloc(sizeof(char *)
			* (prev_envp_data.envp_count + 2));
	add.i = 0;
	add_envp_help(&prev_envp_data, key_and, &add);
	while (key_and[add.j] != '\0')
	{
		add.new_envp_data.envp[add.i][add.j] = key_and[add.j];
		add.j++;
	}
	add.new_envp_data.envp[add.i][add.j] = '\0';
	add.i++;
	free(prev_envp_data.envp);
	add.new_envp_data.envp[add.i] = NULL;
	add.new_envp_data.envp_count = prev_envp_data.envp_count + 1;
	add.new_envp_data.envp_volume = prev_envp_data.envp_volume + 1;
	if (add.key_flag == 1)
	{
		add.new_envp_data = delete_envp(add.new_envp_data, add.key);
	}
	free(add.key);
	return (add.new_envp_data);
}
