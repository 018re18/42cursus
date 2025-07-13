/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:25:33 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/10 13:13:44 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_envp_data *envp_data)
{
	char *string = ft_doller("$PWD", *envp_data);
	printf("%s", string);
	printf("\n");
	free(string);
	return (0);
}
