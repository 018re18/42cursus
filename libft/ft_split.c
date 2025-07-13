/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:42:15 by rookuma           #+#    #+#             */
/*   Updated: 2025/06/19 18:11:22 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_all(char **str, int plase)
{
	while (plase >= 0)
	{
		free(str[plase]);
		plase--;
	}
	free(str);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;
	int	word;

	i = 0;
	word = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && word == 0)
		{
			word = 1;
			count++;
		}
		else if (s[i] == c)
		{
			word = 0;
		}
		i++;
	}
	return (count);
}

static char	*add(char const *s, char c, int plase)
{
	int		len;
	char	*str;
	int		i;

	len = 0;
	while (s[plase + len] != c && s[plase + len] != '\0')
		len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[plase + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int	split_get(char **str, char const *s, char c, int word)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < word)
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		str[j] = add(s, c, i);
		if (!str[j])
		{
			free_all(str, j);
			return (0);
		}
		j++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	str[j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		word;

	if (s == NULL)
		return (NULL);
	word = count_words(s, c);
	str = (char **)malloc(sizeof(char *) * (word + 1));
	if (!str)
		return (NULL);
	if (!split_get(str, s, c, word))
		return (NULL);
	return (str);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	**result;
// 	int		i;

// 	i = 0;
// 	result = ft_split("Hello world this is 42", ' ');
// 	if (!result)
// 	{
// 		printf("split failed\n");
// 		return (1);
// 	}
// 	while (result[i])
// 	{
// 		printf("result[%d] = %s\n", i, result[i]);
// 		free(result[i]);
// 		i++;
// 	}
// 	free(result);
// 	return (0);
// }
