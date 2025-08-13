/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_status_each_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:19:46 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/20 13:50:33 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_status_each_token_init(t_token **result, int token_count)
{
	int	i;

	i = 0;
	*result = (t_token *)malloc(sizeof(t_token) * (token_count + 1));
	if (!*result)
		return (-1);
	while (i <= token_count)
	{
		(*result)[i].str = NULL;
		(*result)[i].type = -1;
		i++;
	}
	return (0);
}

t_token	*add_status_each_token(char **splited_token, int token_count)
{
	t_token	*result;
	int		i;

	if (add_status_each_token_init(&result, token_count) == -1)
		return (NULL);
	i = 0;
	while (i < token_count)
	{
		result[i].str = ft_strdup(splited_token[i]);
		if (ft_strcmp(result[i].str, ">>") == 0)
			result[i].type = TOKEN_APPEND;
		else if (ft_strcmp(result[i].str, "<<") == 0)
			result[i].type = TOKEN_HEREDOC;
		else if (ft_strcmp(result[i].str, "<") == 0)
			result[i].type = TOKEN_REDIRECT_IN;
		else if (ft_strcmp(result[i].str, ">") == 0)
			result[i].type = TOKEN_REDIRECT_OUT;
		else if (ft_strcmp(result[i].str, "|") == 0)
			result[i].type = TOKEN_PIPE;
		else
			result[i].type = TOKEN_WORD;
		i++;
	}
	return (result);
}
