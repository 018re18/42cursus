/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:31:16 by rookuma           #+#    #+#             */
/*   Updated: 2025/07/20 12:48:03 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_redirect(t_cmd_cnk *operate, int place, int redir_place)
{
	if (operate[place].redir[redir_place].type == input)
		return (input_file(operate, place, redir_place));
	else if (operate[place].redir[redir_place].type == heredoc)
		return (input_heredoc(operate[place].redir[redir_place].filename));
	else if (operate[place].redir[redir_place].type == output)
		return (output_file(operate, place, redir_place));
	else if (operate[place].redir[redir_place].type == add)
		return (output_append(operate, place, redir_place));
	return (TRUE);
}

int	minishell_redirect_loop(t_cmd_cnk *operate, int place)
{
	int	redir_place;

	redir_place = 0;
	while (operate[place].redirect > redir_place)
	{
		if (!process_redirect(operate, place, redir_place))
			return (FALSE);
		redir_place++;
	}
	return (TRUE);
}
