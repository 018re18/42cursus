/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:43:14 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/02 17:21:48 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp_data	ft_unset( char **args,t_envp_data envp_data)
{
	int	i;
	if (!args[1] || args[1][0] == '\0')
		return (envp_data);
	i = 1;
	while (args[i])
	{
		envp_data = delete_envp(envp_data, args[i]);
		i++;
	}
	return (envp_data);
}
