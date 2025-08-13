/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:27:19 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/19 18:23:56 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_envp_count(t_envp_data prev_envp_data, t_delete_envp *delete)
{
	while (prev_envp_data.envp[delete->i][delete->j] != '\0')
		delete->j++;
	delete->new_envp_data.envp[delete->i
		- delete->delete_flag] = (char *)malloc(sizeof(char) * (delete->j + 1));
	delete->j = 0;
}

void	delete_envp_help(t_envp_data prev_envp_data, char *key,
		t_delete_envp *delete)
{
	while (delete->i < prev_envp_data.envp_count)
	{
		delete->j = 0;
		if (cmp_key(key, prev_envp_data.envp[delete->i]) == 0
			&& delete->delete_flag == 0)
		{
			free(prev_envp_data.envp[delete->i]);
			delete->i++;
			delete->delete_flag = 1;
			continue ;
		}
		delete_envp_count(prev_envp_data, delete);
		while (prev_envp_data.envp[delete->i][delete->j] != '\0')
		{
			delete->new_envp_data.envp[delete->i - \
				delete->delete_flag][delete->j] = \
				prev_envp_data.envp[delete->i][delete->j];
			delete->j++;
		}
		delete->new_envp_data.envp[delete->i
			- delete->delete_flag][delete->j] = '\0';
		free(prev_envp_data.envp[delete->i]);
		delete->i++;
	}
}

t_envp_data	delete_envp(t_envp_data prev_envp_data, char *key)
{
	t_delete_envp	delete;
	char			*joined_key;
	char			*key_a;

	if (key[0] == '\0')
		return (prev_envp_data);
	joined_key = ft_strjoin("$", key);
	key_a = ft_doller(joined_key, prev_envp_data);
	if (ft_strcmp(joined_key, key_a) == 0)
	{
		free(joined_key);
		return (free(key_a), prev_envp_data);
	}
	free(joined_key);
	free(key_a);
	delete.delete_flag = 0;
	delete.new_envp_data.envp = (char **)malloc(sizeof(char *)
			* (prev_envp_data.envp_count));
	delete.i = 0;
	delete_envp_help(prev_envp_data, key, &delete);
	free(prev_envp_data.envp);
	delete.new_envp_data.envp[delete.i - delete.delete_flag] = NULL;
	delete.new_envp_data.envp_count = prev_envp_data.envp_count - 1;
	delete.new_envp_data.envp_volume = prev_envp_data.envp_volume - 1;
	return (delete.new_envp_data);
}
