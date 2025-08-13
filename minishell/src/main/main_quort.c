/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_quort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:25:01 by rookuma           #+#    #+#             */
/*   Updated: 2025/07/20 14:26:37 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quort_check_loop(char **splited_token)
{
	int	i;

	i = 0;
	while (splited_token[i])
	{
		splited_token[i] = quort_check(splited_token[i]);
		i++;
	}
}

static t_token	*check_syntax_convert(char **splited_token, int token_count,
		int *exit_status, char *line)
{
	t_token	*token_and_status;
	int		i;

	token_and_status = add_status_each_token(splited_token, token_count);
	free_splited_token(splited_token, token_count);
	if (check_syntax(token_and_status) == 1)
	{
		*exit_status = 2;
		i = 0;
		while (token_and_status[i].str != NULL)
		{
			free(token_and_status[i].str);
			i++;
		}
		free(token_and_status);
		free(line);
		return (NULL);
	}
	return (token_and_status);
}

int	readline_loop_quort(t_token **token_and_status, t_main *m, int *exit_status)
{
	m->splited_token = skip_space(m->splited_token, &(m->token_count));
	quort_check_loop(m->splited_token);
	*token_and_status = check_syntax_convert(m->splited_token, m->token_count,
			exit_status, m->line);
	if (!(*token_and_status))
		return (FALSE);
	return (TRUE);
}
