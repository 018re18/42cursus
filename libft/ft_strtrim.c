/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:47:41 by rookuma           #+#    #+#             */
/*   Updated: 2025/04/30 17:05:33 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char s1, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (s1 == set[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		first;
	int		last;
	int		i;
	char	*res;

	if (s1 == NULL || set == NULL)
		return (NULL);
	first = 0;
	while (s1[first] != '\0' && check(s1[first], set) == 1)
		first++;
	last = ft_strlen(s1);
	while (last > first && check(s1[last - 1], set) == 1)
		last--;
	res = (char *)malloc(sizeof(char) * (last - first + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (first < last)
	{
		res[i] = s1[first];
		i++;
		first++;
	}
	res[i] = '\0';
	return (res);
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
// 	char	*set;
// 	char	*trimmed;

// 	s1 = "  \t\n42Tokyo\t \n ";
// 	set = " \n\t";
// 	trimmed = ft_strtrim(s1, set);
// 	if (trimmed)
// 	{
// 		printf("Original : \"%s\"\n", s1);
// 		printf("Trimmed  : \"%s\"\n", trimmed);
// 		free(trimmed);
// 	}
// 	else
// 	{
// 		printf("ft_strtrim failed\n");
// 	}
// 	return (0);
// }
