/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:07:32 by rookuma           #+#    #+#             */
/*   Updated: 2025/07/19 18:09:23 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	space_check(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0' && string[i] != '\n')
	{
		if (string[i] != ' ' && string[i] != 9)
			return (1);
		i++;
	}
	return (0);
}

void	free_string(char **string)
{
	int	i;

	i = 0;
	while (string[i] != NULL)
	{
		free(string[i]);
		i++;
	}
	free(string);
}

char	**skip_space(char **string, int *token_count)
{
	int		i;
	int		j;
	char	**result;

	i = 0;
	j = 0;
	if (space_check(string[i]) == 0)
		i++;
	else
		return (string);
	while (space_check(string[i]) == 0 || string[i][0] == '|')
		i++;
	*token_count = *token_count - i;
	while (string[j] != NULL)
		j++;
	result = (char **)malloc(sizeof(char *) * j - i + 1);
	j = 0;
	while (string[i] != NULL)
		result[j++] = ft_strdup(string[i++]);
	result[j] = NULL;
	free_string(string);
	return (result);
}

void	free_splited_token(char **splited_token, int token_count)
{
	int	i;

	i = 0;
	while (i < token_count)
	{
		free(splited_token[i]);
		i++;
	}
	free(splited_token);
}

void	write_syntax_error(void)
{
	write(2, "minishell: syntax error near unexpected token `|'\n", 51);
}
