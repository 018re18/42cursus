/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:53:48 by rookuma           #+#    #+#             */
/*   Updated: 2025/04/30 14:51:15 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	char			*str;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

// #include <ctype.h>
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

// char	to_upper_even(unsigned int i, char c)
// {
// 	if (i % 2 == 0 && c >= 'a' && c <= 'z')
// 		return (c - 32); // 小文字→大文字
// 	return (c);
// }

// int	main(void)
// {
// 	char	*input;
// 	char	*result;

// 	input = "libft_is_fun";
// 	result = ft_strmapi(input, to_upper_even);
// 	if (result)
// 	{
// 		printf("Original: %s\n", input);
// 		printf("Mapped  : %s\n", result);
// 		free(result);
// 	}
// 	else
// 	{
// 		printf("ft_strmapi failed\n");
// 	}
// 	return (0);
// }
