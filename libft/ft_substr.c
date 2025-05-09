/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:25:43 by rookuma           #+#    #+#             */
/*   Updated: 2025/04/30 17:05:42 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*str_res(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 1);
	if (!(str))
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	unsigned int	l;

	if (!s)
		return (NULL);
	l = ft_strlen(s);
	if (l < start)
	{
		return (str_res());
	}
	if (len > (l - start))
		len = l - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
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
// 	char	*str;
// 	char	*sub;

// 	str = "Hello, 42Tokyo!";
// 	sub = ft_substr(str, 7, 6);
// 	if (sub)
// 	{
// 		printf("Original : %s\n", str);
// 		printf("Substring: %s\n", sub); // Expected: "42Tokyo"
// 		free(sub);
// 	}
// 	else
// 	{
// 		printf("ft_substr failed\n");
// 	}
// 	// 範囲外の start
// 	sub = ft_substr(str, 50, 5);
// 	if (sub)
// 	{
// 		printf("Out of range start: \"%s\"\n", sub); // Expected: ""
// 		free(sub);
// 	}
// 	else
// 	{
// 		printf("ft_substr (out of range) failed\n");
// 	}
// 	return (0);
// }
