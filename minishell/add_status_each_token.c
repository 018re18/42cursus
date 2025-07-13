/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_status_each_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:19:46 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/10 18:07:02 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// typedef enum e_token_type
// {
// 	TOKEN_WORD,
// 	TOKEN_PIPE,
// 	TOKEN_REDIRECT_IN,
// 	TOKEN_REDIRECT_OUT,
// 	TOKEN_HEREDOC,
// 	TOKEN_APPEND
// }					t_token_type;

// typedef struct s_token
// {
// 	char			*str;
// 	t_token_type	type;
// }					t_token;

int	add_status_each_token_init(t_token **result, int token_count)
{
	int i = 0;
	*result = (t_token *)malloc(sizeof(t_token) * (token_count + 1));
	if (!*result)
		return (-1);
	while(i <= token_count){
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
		// printf("%s\n",result[i].str);
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

// t_token	*input_cmd_check(t_token *result, int token_count)
// {
// 	int i = 0;
// 	while (i < token_count)
// 	{
// 		if (i == 0)
// 		{
// 			result[i].type = TOKEN_CMD;
// 		}
// 		else if (result[i].type == TOKEN_PIPE)
// 		{
// 			result[i + 1].type = TOKEN_CMD;
// 		}
// 		i++;
// 	}
// 	return (result);
// }