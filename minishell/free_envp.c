/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:06:08 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/10 13:32:32 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp(t_envp_data *envp_data)
{
	int	i;

	if (envp_data == NULL)
	{
		return ;
	}
	i = 0;
	while (envp_data->envp[i])
	{
		free(envp_data->envp[i]);
		i++;
	}
	free(envp_data->envp);
}
