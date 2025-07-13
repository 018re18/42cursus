/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 19:11:22 by kryutaro          #+#    #+#             */
/*   Updated: 2025/06/30 12:19:43 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	char	*start;

	if (!s)
		return (NULL);
	dest = (char *)malloc(ft_strlen(s) + 1);
	if (!dest)
		return (0);
	start = dest;
	while (*s)
	{
		*dest = *s;
		dest++;
		s++;
	}
	*dest = '\0';
	return (start);
}
// o