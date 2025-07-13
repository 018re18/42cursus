/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:43:44 by kryutaro          #+#    #+#             */
/*   Updated: 2025/06/19 11:29:33 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*substring_copy(const char *s, int start, int end)
{
	char	*new_str;
	int		i;
	int		len;

	i = 0;
	len = end - start;
	if (!s || start < 0 || end <= start)
		return (NULL);
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	while (start < end)
		new_str[i++] = s[start++];
	new_str[i] = '\0';
	return (new_str);
}

static void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

static char	**extract_words(const char *s, char c, char **result)
{
	int	i;
	int	start;
	int	idx;

	i = 0;
	start = 0;
	idx = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			start = i;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			result[idx++] = substring_copy(s, start, i + 1);
			if (!result[idx - 1])
			{
				free_array(result);
				return (NULL);
			}
		}
		i++;
	}
	result[idx] = NULL;
	return (result);
}

char	**ft_split(const char *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!result)
		return (NULL);
	return (extract_words(s, c, result));
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	str[] = "haaaahhaaahhaahhahahah";
// 	char	c;
// 	int		i;
// 	char	**pp;

// 	c = 'h';
// 	printf("%d\n", countword(str, c));
// 	i = 0;
// 	pp = ft_split(str, c);
// 	while (i < 7)
// 	{
// 		printf("%s\n", pp[i]);
// 		i++;
// 	}
// }
