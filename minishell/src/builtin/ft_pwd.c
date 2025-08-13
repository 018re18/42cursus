/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:25:33 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/28 19:17:42 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*string;

	string = getcwd(NULL, 0);
	if (string == NULL)
	{
		return (0);
	}
	write(1, string, ft_strlen(string));
	write(1, "\n", 1);
	free(string);
	return (0);
}
