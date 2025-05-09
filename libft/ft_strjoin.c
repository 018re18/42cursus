/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:38:34 by rookuma           #+#    #+#             */
/*   Updated: 2025/04/30 17:05:11 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	str_cpy(char *dest, const char *src, int plase)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[plase + i] = src[i];
		i++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str)
		return (NULL);
	str_cpy(str, s1, 0);
	str_cpy(str, s2, s1_len);
	str[s1_len + s2_len] = '\0';
	return (str);
}

// #include <stdio.h>

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i] != '\0')
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// int	main(void)
// {
// 	char	*s1;
// 	char	*s2;
// 	char	*joined;

// 	s1 = "42";
// 	s2 = "Tokyo";
// 	joined = ft_strjoin(s1, s2);
// 	if (joined)
// 	{
// 		printf("Joined string: %s\n", joined);
// 		free(joined);
// 	}
// 	else
// 	{
// 		printf("ft_strjoin failed\n");
// 	}
// 	return (0);
// }
