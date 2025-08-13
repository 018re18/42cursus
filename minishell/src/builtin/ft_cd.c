/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:16:34 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/28 18:59:52 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_envp_data *envp_data, char **args)
{
	int	exit_status;

	exit_status = 0;
	*envp_data = ft_cd_help(*envp_data, args, &exit_status);
	return (exit_status);
}
