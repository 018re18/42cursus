/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:58:04 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/19 17:52:29 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error(const char *token)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	write(2, token, ft_strlen(token));
	write(2, "'\n", 2);
	return (1);
}

int	check_syntax(t_token *tokens)
{
	int				i;
	t_token_type	type;

	i = 0;
	while (tokens[i].str)
	{
		type = tokens[i].type;
		if (i == 0 && type == TOKEN_PIPE)
			return (print_error("|"));
		if (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT
			|| type == TOKEN_HEREDOC || type == TOKEN_APPEND)
		{
			if (!tokens[i + 1].str || tokens[i + 1].type != TOKEN_WORD)
				return (print_error("newline"));
		}
		if (type == TOKEN_PIPE && tokens[i + 1].type == TOKEN_PIPE)
			return (print_error("|"));
		if (type == TOKEN_PIPE && tokens[i + 1].str == NULL)
			return (print_error("newline"));
		i++;
	}
	return (0);
}
