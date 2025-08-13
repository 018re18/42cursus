/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:32:45 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/20 14:08:46 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_envp_check_key(t_envp_data prev_envp_data,
		t_append_envp *append)
{
	while (prev_envp_data.envp[append->i] != NULL)
	{
		if (cmp_key(append->key, prev_envp_data.envp[append->i]) == 0)
		{
			append->key_flag = append->i;
		}
		append->j = 0;
		while (prev_envp_data.envp[append->i][append->j] != '\0')
			append->j++;
		append->new_envp_data.envp[append->i] = (char *)malloc(sizeof(char)
				* (append->j + 1));
		append->j = 0;
		while (prev_envp_data.envp[append->i][append->j] != '\0')
		{
			append->new_envp_data.envp[append->i][append->j] = \
			prev_envp_data.envp[append->i][append->j];
			append->j++;
		}
		append->new_envp_data.envp[append->i][append->j] = '\0';
		free(prev_envp_data.envp[append->i]);
		append->i++;
	}
}

void	append_envp_write(char *key_and,
		t_append_envp *append)
{
	if (append->key_flag != -1)
	{
		append->tmp = ft_strjoin(append->new_envp_data.envp[append->key_flag],
				&key_and[ft_strlen(append->key) + 2]);
		free(append->new_envp_data.envp[append->key_flag]);
		append->new_envp_data.envp[append->key_flag] = append->tmp;
	}
	else
	{
		append->j = 0;
		while (key_and[append->j] != '\0')
			append->j++;
		append->new_envp_data.envp[append->i] = (char *)malloc(sizeof(char)
				* (append->j + 1));
		append->j = 0;
		while (key_and[append->j] != '\0')
		{
			append->new_envp_data.envp[append->i][append->j] = \
			key_and[append->j];
			append->j++;
		}
		append->new_envp_data.envp[append->i][append->j] = '\0';
		append->i++;
	}
}

t_envp_data	append_envp(t_envp_data prev_envp_data, char *key_and)
{
	t_append_envp	append;

	append.key_flag = -1;
	append.key = set_key(key_and);
	append.new_envp_data.envp = (char **)malloc(sizeof(char *)
			* (prev_envp_data.envp_count + 1));
	append.i = 0;
	append_envp_check_key(prev_envp_data, &append);
	append_envp_write(key_and, &append);
	free(prev_envp_data.envp);
	append.new_envp_data.envp[append.i] = NULL;
	append.new_envp_data.envp_count = prev_envp_data.envp_count;
	append.new_envp_data.envp_volume = prev_envp_data.envp_volume;
	free(append.key);
	return (append.new_envp_data);
}
