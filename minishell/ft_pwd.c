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
	char *string;

	string = ft_doller("$PWD", *envp_data);
	write(1,string,ft_strlen(string));
	write(1,"\n",1);
	free(string);
	return (0);
}
