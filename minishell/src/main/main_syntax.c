/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:18:54 by rookuma           #+#    #+#             */
/*   Updated: 2025/07/20 13:05:03 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**parse_and_expand(char *line, t_envp_data envp_data, int status,
		int *token_count)
{
	char	**splited_token;

	*token_count = count_token(line);
	splited_token = (char **)malloc(sizeof(char *) * (*token_count + 1));
	if (!splited_token)
		return (NULL);
	splited_token = split_kai(line, splited_token);
	splited_token = doller_open(splited_token, envp_data, status);
	return (splited_token);
}

static void	check_syntax_first_init(int *flag, int *pipe_flag, int *i, int mode)
{
	if (mode == 0)
	{
		*flag = 1;
		*pipe_flag = 0;
	}
	else
	{
		*flag = 0;
		*i = 1;
	}
}

static int	check_syntax_first(char **splited_token)
{
	int	i;
	int	flag;
	int	pipe_flag;

	check_syntax_first_init(&flag, &pipe_flag, &i, 0);
	if ((space_check(splited_token[0]) == 0))
	{
		check_syntax_first_init(&flag, &pipe_flag, &i, 1);
		while (splited_token[i] != NULL)
		{
			if (!(space_check(splited_token[i]) == 0
					|| splited_token[i][0] == '|'))
				flag = 1;
			if (splited_token[i][0] == '|' && pipe_flag == 1)
				write_syntax_error();
			if (splited_token[i][0] == '|')
				pipe_flag = 1;
			else
				pipe_flag = 0;
			i++;
		}
		if (splited_token[i - 1][0] == '|' && pipe_flag == 1)
			write_syntax_error();
	}
	return (flag);
}

int	readline_loop_syntax(t_main *m, t_envp_data envp_data, int *exit_status)
{
	m->splited_token = parse_and_expand(m->line, envp_data, *exit_status,
			&(m->token_count));
	if (check_syntax_first(m->splited_token) == 0)
	{
		free_splited_token(m->splited_token, m->token_count);
		free(m->line);
		return (FALSE);
	}
	return (TRUE);
}
