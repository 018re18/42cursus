/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 00:00:00 by kryutaro          #+#    #+#             */
/*   Updated: 2026/06/11 00:00:00 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

int	ft_isspace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_streq(char *a, char *b)
{
	int	i;

	i = 0;
	while (a[i] && b[i] && a[i] == b[i])
		i++;
	return (a[i] == '\0' && b[i] == '\0');
}

char	*ft_strdup(char *str)
{
	char	*copy;
	int		i;

	copy = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	i = -1;
	while (str[++i])
		copy[i] = str[i];
	copy[i] = '\0';
	return (copy);
}
