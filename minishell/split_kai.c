/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_kai.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:19:02 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/08 14:48:02 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_count_token
{
	int		i;
	int		s_quarto_flag;
	int		w_quarto_flag;
	int		count;
	int		split_flag;
	int		token_count;
}			t_count_token;

void	count_token_init(t_count_token *token_info)
{
	token_info->token_count = 0;
	token_info->split_flag = 0;
	token_info->count = 1;
	token_info->i = 0;
	token_info->s_quarto_flag = 0;
	token_info->w_quarto_flag = 0;
}

int	count_token_space(t_count_token *token_info)
{
	if (token_info->i == 0)
	{
		token_info->count--;
	}
	if (token_info->split_flag == 0)
	{
		token_info->count++;
		token_info->split_flag = 1;
		token_info->i += 1;
		return (1);
	}
	else if (token_info->split_flag == 1)
	{
		token_info->split_flag = 1;
		token_info->i += 1;
		return (1);
	}
	return (0);
}

int	count_token_before_symbol(t_count_token *token_info)
{
	if (token_info->i == 0)
	{
		token_info->count--;
	}
	if (token_info->split_flag == 0)
	{
		token_info->count++;
		token_info->token_count++;
		token_info->split_flag = 1;
		token_info->i += 2;
		return (1);
	}
	else if (token_info->split_flag == 1)
	{
		token_info->token_count++;
		token_info->split_flag = 1;
		token_info->i += 2;
		return (1);
	}
	return (0);
}

int	count_token_symbol(t_count_token *token_info)
{
	if (token_info->i == 0)
	{
		token_info->count--;
	}
	if (token_info->split_flag == 0)
	{
		token_info->count++;
		token_info->token_count++;
		token_info->split_flag = 1;
		token_info->i += 1;
		return (1);
	}
	else if (token_info->split_flag == 1)
	{
		token_info->token_count++;
		token_info->split_flag = 1;
		token_info->i += 1;
		return (1);
	}
	return (0);
}

int	count_token_help(char *string, t_count_token *token_info)
{
	if (string[token_info->i] == ' ')
	{
		if (count_token_space(token_info) == 1)
			return (1);
	}
	else if ((string[token_info->i + 1] && ((string[token_info->i] == '>'
					&& string[token_info->i + 1] == '>')
				|| (string[token_info->i] == '<' && string[token_info->i
					+ 1] == '<'))))
	{
		if (count_token_before_symbol(token_info) == 1)
			return (1);
	}
	else if ((string[token_info->i] == '|' || string[token_info->i] == '>'
			|| string[token_info->i] == '<'))
	{
		if (count_token_symbol(token_info) == 1)
			return (1);
	}
	if (string[token_info->i] == '\'')
		token_info->s_quarto_flag = 1;
	if (string[token_info->i] == '\"')
		token_info->w_quarto_flag = 1;
	token_info->split_flag = 0;
	return (0);
}

void	count_token_reduce(char *string, t_count_token *token_info)
{
	if (string[token_info->i - 1] == '<' || string[token_info->i - 1] == '>'
		|| string[token_info->i - 1] == '|')
		token_info->count--;
	token_info->count = token_info->count + token_info->token_count;
}

int	count_token(char *string)
{
	t_count_token	token_info;

	count_token_init(&token_info);
	while (string[token_info.i] != '\0')
	{
		if (token_info.s_quarto_flag == 0 && token_info.w_quarto_flag == 0)
		{
			if (count_token_help(string, &token_info) == 1)
				continue ;
		}
		else if (token_info.s_quarto_flag == 1)
		{
			if (token_info.s_quarto_flag == 1 && string[token_info.i] == '\'')
				token_info.s_quarto_flag = 0;
		}
		else if (token_info.w_quarto_flag == 1)
		{
			if (token_info.w_quarto_flag == 1 && string[token_info.i] == '\"')
				token_info.w_quarto_flag = 0;
		}
		token_info.i++;
	}
	count_token_reduce(string,&token_info);
	return (token_info.count);
}

char	*malloc_and_push(char *string, int i, int count_flag)
{
	char	*result;
	int		j;

	result = (char *)malloc(sizeof(char) * (i - count_flag + 1));
	j = 0;
	while (j < i - count_flag)
	{
		result[j] = string[count_flag + j];
		j++;
	}
	result[j] = '\0';
	return (result);
}

// char	*malloc_and_push(char *string, int i, int count_flag)
// {
// 	char	*result;
// 	int		j;
// 	int		len;

// 	len = i - count_flag;
// 	if (len <= 0)
// 		return (ft_strdup("")); // or NULL, depending on what your logic needs

// 	result = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!result)
// 		return (NULL);
// 	j = 0;
// 	while (j < len)
// 	{
// 		result[j] = string[count_flag + j];
// 		j++;
// 	}
// 	result[j] = '\0';
// 	return (result);
// }
int	search_envp(char *key, t_envp_data envp_data)
{
	int	i;

	i = 0;
	// printf("%s",key);
	while (envp_data.envp[i])
	{
		if (cmp_key(&key[1], envp_data.envp[i]) == 0)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_al_num(char c)
{
	if (('0' <= c && c <= '9') || ('a' <= c && c <= 'z') || ('A' <= c
			&& c <= 'Z') || (c == '_'))
		return (0);
	return (1);
}

typedef struct s_doller_open
{
	int		i;
	int		s_quort_flag;
	int		w_quort_flag;
	char	*doller_word;
	char	*opened_doller_word;
	char	*result;
	int		char_count;
	int		j;
	int		k;
	char	*string_exit_status;
	char	*result_join;
	char	stop_flag;
	int		stop_flag_int;
	char	*suffix;
}			t_doller_open;

void	doller_open_help_init(t_doller_open *doller)
{
	doller->stop_flag = 0;
	doller->stop_flag_int = 0;
	doller->w_quort_flag = 0;
	doller->k = 0;
	doller->char_count = 0;
	doller->i = 0;
	doller->s_quort_flag = 0;
}

void	doller_open_count_open_normal_help(char *string, t_envp_data envp_data,
		int exit_status, t_doller_open *doller)
{
	doller->j++;
	while (string[doller->i + doller->j] != '\0' && string[doller->i
		+ doller->j] != '\"' && is_al_num(string[doller->i + doller->j]) == 0)
		doller->j++;
	if (string[doller->i + doller->j] == '\"' || is_al_num(string[doller->i
			+ doller->j]) == 1)
	{
		doller->stop_flag = string[doller->i + doller->j];
		doller->stop_flag_int = 1;
		doller->j++;
	}
	doller->doller_word = (char *)malloc(sizeof(char) * (doller->j + 1));
	doller->j = 0;
	doller->doller_word[doller->j] = string[doller->i + doller->j];
	doller->j++;
	while ((string[doller->i + doller->j] != '\0' && string[doller->i
			+ doller->j] != '\"' && is_al_num(string[doller->i
				+ doller->j]) == 0))
	{
		doller->doller_word[doller->j] = string[doller->i + doller->j];
		doller->j++;
	}
	doller->doller_word[doller->j] = '\0';
}

int	doller_open_count_open_normal(char *string, t_envp_data envp_data,
		int exit_status, t_doller_open *doller)
{
	doller_open_count_open_normal_help(string, envp_data, exit_status, doller);
	if (search_envp(doller->doller_word, envp_data) == 0)
	{
		doller->opened_doller_word = ft_doller(doller->doller_word, envp_data);
	}
	else
	{
		doller->opened_doller_word = (char *)malloc(sizeof(char));
		doller->opened_doller_word[0] = '\0';
	}
	doller->k = 0;
	while (doller->opened_doller_word[doller->k] != '\0')
	{
		doller->k++;
		doller->char_count++;
	}
	free(doller->opened_doller_word);
	return (2);
}

int	doller_open_count_open(char *string, t_envp_data envp_data, int exit_status,
		t_doller_open *doller)
{
	if (string[doller->i] == '$')
	{
		doller->j = 0;
		if (!string[doller->i + 1] || (string[doller->i + 1]
				&& is_al_num(string[doller->i + 1]) == 1 && string[doller->i
				+ 1] != '?'))
		{
			doller->char_count = doller->char_count + 1;
			doller->i = doller->i + 1;
			return (1);
		}
		else if (string[doller->i + 1] && string[doller->i + 1] == '?')
		{
			doller->string_exit_status = ft_itoa(exit_status);
			doller->char_count = doller->char_count
				+ ft_strlen(doller->string_exit_status);
			doller->i = doller->i + 2;
			free(doller->string_exit_status);
			return (1);
		}
		else
			return (doller_open_count_open_normal(string, envp_data,
					exit_status, doller));
	}
	return (0);
}
void	doller_open_count_quort_check(char *string, t_doller_open *doller)
{
	if (string[doller->i] == '\'' && doller->w_quort_flag == 0)
	{
		if (doller->s_quort_flag == 0)
		{
			doller->s_quort_flag = 1;
		}
		else if (doller->s_quort_flag == 1)
		{
			doller->s_quort_flag = 0;
		}
	}
	if (string[doller->i] == '\"' && doller->s_quort_flag == 0)
	{
		if (doller->w_quort_flag == 0)
		{
			doller->w_quort_flag = 1;
		}
		else if (doller->w_quort_flag == 1)
		{
			doller->w_quort_flag = 0;
		}
	}
}

void	doller_open_variable_reset(t_doller_open *doller)
{
	doller->k = 0;
	doller->char_count = 0;
	doller->i = 0;
	doller->s_quort_flag = 0;
	doller->w_quort_flag = 0;
}

void	doller_open_count_size(char *string, t_envp_data envp_data,
		int exit_status, t_doller_open *doller)
{
	int	break_flag;

	while (string[doller->i] != '\0')
	{
		doller->j = 1;
		if (doller->s_quort_flag == 0)
		{
			break_flag = doller_open_count_open(string, envp_data, exit_status,
					doller);
			if (break_flag == 1)
				continue ;
			else if (break_flag == 2)
				break ;
		}
		doller_open_count_quort_check(string, doller);
		doller->char_count++;
		doller->i = doller->i + doller->j;
	}
	doller->result = (char *)malloc(sizeof(char) * (doller->char_count + 1
				+ doller->stop_flag_int));
}
int	doller_open_input_string_doll_only(char *string, t_envp_data envp_data,
		int exit_status, t_doller_open *doller)
{
	doller->string_exit_status = (char *)malloc(sizeof(char) * 2);
	doller->string_exit_status[0] = '$';
	doller->string_exit_status[1] = '\0';
	while (doller->j < ft_strlen(doller->string_exit_status))
	{
		doller->result[doller->char_count] = doller->string_exit_status[doller->j];
		doller->char_count++;
		doller->j++;
	}
	free(doller->string_exit_status);
	doller->j = 0;
	doller->i = doller->i + 1;
	return (1);
}

int	doller_open_input_string_doll_and_q(char *string, t_envp_data envp_data,
		int exit_status, t_doller_open *doller)
{
	doller->string_exit_status = ft_itoa(exit_status);
	while (doller->j < ft_strlen(doller->string_exit_status))
	{
		doller->result[doller->char_count] = doller->string_exit_status[doller->j];
		doller->char_count++;
		doller->j++;
	}
	free(doller->string_exit_status);
	doller->j = 0;
	doller->i = doller->i + 2;
	return (1);
}

void	doller_open_input_string_normal_help(char *string,
		t_envp_data envp_data, int exit_status, t_doller_open *doller)
{
	if (doller->opened_doller_word[0] == '$'
		&& doller->opened_doller_word[1] != '\0')
	{
		free(doller->opened_doller_word);
		doller->opened_doller_word = (char *)malloc(sizeof(char));
		doller->opened_doller_word[0] = '\0';
	}
	doller->k = 0;
	while (doller->opened_doller_word[doller->k] != '\0')
	{
		doller->result[doller->char_count] = doller->opened_doller_word[doller->k];
		doller->char_count++;
		doller->k++;
	}
	if (doller->stop_flag != 0)
	{
		doller->result[doller->char_count] = doller->stop_flag;
		doller->char_count++;
	}
}

int	doller_open_input_string_normal(char *string, t_envp_data envp_data,
		int exit_status, t_doller_open *doller)
{
	doller->j++;
	while (string[doller->i + doller->j] != '\0' && string[doller->i
		+ doller->j] != '\"' && is_al_num(string[doller->i + doller->j]) == 0)
	{
		doller->j++;
	}
	doller->opened_doller_word = NULL;
	if (search_envp(doller->doller_word, envp_data) == 0)
	{
		doller->opened_doller_word = ft_doller(doller->doller_word, envp_data);
	}
	else
	{
		doller->opened_doller_word = (char *)malloc(sizeof(char));
		doller->opened_doller_word[0] = '\0';
	}
	free(doller->doller_word);
	doller_open_input_string_normal_help(string, envp_data, exit_status,
		doller);
	free(doller->opened_doller_word);
	return (2);
}

int	doller_open_input_string(char *string, t_envp_data envp_data,
		int exit_status, t_doller_open *doller)
{
	int	return_num;

	return_num = 0;
	if (string[doller->i] == '$')
	{
		doller->j = 0;
		if (!string[doller->i + 1] || (string[doller->i + 1]
				&& is_al_num(string[doller->i + 1]) == 1 && string[doller->i
				+ 1] != '?')) //
		{
			return_num = doller_open_input_string_doll_only(string, envp_data,
					exit_status, doller);
		}
		else if (string[doller->i + 1] && string[doller->i + 1] == '?')
		{
			return_num = doller_open_input_string_doll_and_q(string, envp_data,
					exit_status, doller);
		}
		else
		{
			return_num = doller_open_input_string_normal(string, envp_data,
					exit_status, doller);
		}
	}
	return (return_num);
}

void	doller_open_input_string_quort_check(char *string,
		t_envp_data envp_data, int exit_status, t_doller_open *doller)
{
	if (string[doller->i] == '\'' && doller->w_quort_flag == 0)
	{
		if (doller->s_quort_flag == 0)
		{
			doller->s_quort_flag = 1;
		}
		else if (doller->s_quort_flag == 1)
		{
			doller->s_quort_flag = 0;
		}
	}
	if (string[doller->i] == '\"' && doller->s_quort_flag == 0)
	{
		if (doller->w_quort_flag == 0)
		{
			doller->w_quort_flag = 1;
		}
		else if (doller->w_quort_flag == 1)
		{
			doller->w_quort_flag = 0;
		}
	}
}

void	doller_open_input(char *string, t_envp_data envp_data, int exit_status,
		t_doller_open *doller)
{
	int	break_flag;

	while (string[doller->i] != '\0')
	{
		doller->j = 1;
		if (doller->s_quort_flag == 0)
		{
			break_flag = doller_open_input_string(string, envp_data,
					exit_status, doller);
			if (break_flag == 1)
				continue ;
			if (break_flag == 2)
				break ;
		}
		doller_open_input_string_quort_check(string, envp_data, exit_status,
			doller);
		doller->result[doller->char_count] = string[doller->i];
		doller->char_count++;
		doller->i = doller->i + doller->j;
	}
}

char	*doller_open_help(char *string, t_envp_data envp_data, int exit_status)
{
	t_doller_open	doller;

	doller_open_help_init(&doller);
	if (string == NULL)
		return (NULL);
	doller_open_count_size(string, envp_data, exit_status, &doller);
	doller_open_variable_reset(&doller);
	doller_open_input(string, envp_data, exit_status, &doller);
	doller.result[doller.char_count] = '\0';
	if (string[doller.i] != '\0')
		doller.i++;
	while (string[doller.i] != '\0' && string[doller.i] != '\"'
		&& is_al_num(string[doller.i]) == 0)
		doller.i++;
	if (string[doller.i] != '\0' && (string[doller.i] == '\"'
			|| is_al_num(string[doller.i]) == 1))
		doller.i++;
	if (string[doller.i] == '\0')
		doller.suffix = "";
	else
		doller.suffix = &string[doller.i];
	doller.result_join = ft_strjoin(doller.result, doller.suffix);
	free(doller.result);
	return (doller.result_join);
}

char	**doller_open(char **splited_token, t_envp_data envp_data,
		int exit_status)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = (char *)malloc(sizeof(char));
	tmp[0] = '\0';
	i = 0;
	j = 0;
	while (splited_token[i] != NULL)
	{
		j = 0;
		while (ft_strcmp(splited_token[i], tmp) != 0)
		{
			free(tmp);
			tmp = splited_token[i];
			splited_token[i] = doller_open_help(splited_token[i], envp_data,
					exit_status);
			j++;
		}
		i++;
	}
	free(tmp);
	return (splited_token);
}

typedef struct s_quort_error
{
	int		i;
	int		s_quort_count;
	int		w_quort_count;
	int		s_quort_count_flag;
	int		w_quort_count_flag;
}			t_quort_error;

void	quort_error_count(char *string, t_quort_error *quort)
{
	while (string[quort->i] != '\0')
	{
		if (quort->s_quort_count_flag == 0 && quort->w_quort_count_flag == 0)
		{
			if (string[quort->i] == '\"')
			{
				quort->w_quort_count++;
				quort->w_quort_count_flag = 1;
			}
			if (string[quort->i] == '\'')
			{
				quort->s_quort_count++;
				quort->s_quort_count_flag = 1;
			}
		}
		else
		{
			if (quort->w_quort_count_flag == 1 && string[quort->i] == '\"')
				quort->w_quort_count_flag = 0;
			if (quort->s_quort_count_flag == 1 && string[quort->i] == '\'')
				quort->s_quort_count_flag = 0;
		}
		quort->i++;
	}
}

int	quort_error(char *string)
{
	t_quort_error	quort;

	quort.s_quort_count_flag = 0;
	quort.w_quort_count_flag = 0;
	quort.i = 0;
	quort.s_quort_count = 0;
	quort.w_quort_count = 0;
	quort_error_count(string, &quort);
	if (quort.s_quort_count_flag == 0 && quort.w_quort_count_flag == 0)
	{
		return (TRUE);
	}
	else
	{
		if (quort.s_quort_count_flag != 0)
		{
			write(2, "minishell: syntax error near unexpected token\'\n", 47);
		}
		if (quort.w_quort_count_flag != 0)
		{
			write(2, "minishell: syntax error near unexpected token\"\n", 47);
		}
		return (FALSE);
	}
}

typedef struct s_split
{
	int		i;
	int		s_quarto_flag;
	int		w_quarto_flag;
	int		count;
	int		split_flag;
	int		token_count;
	int		count_flag;
	int		splited_pipe_count;
}			t_split;

void	split_kai_init(t_split *split)
{
	split->splited_pipe_count = 0;
	split->count_flag = 0;
	split->token_count = 0;
	split->split_flag = 0;
	split->count = 0;
	split->i = 0;
	split->s_quarto_flag = 0;
	split->w_quarto_flag = 0;
}

void	split_space_help(t_split *split, char **splited_pipe, char *string)
{
	splited_pipe[split->count] = malloc_and_push(string, split->i,
			split->count_flag);
	split->count++;
	split->split_flag = 1;
	split->i += 1;
	split->count_flag = split->i;
}

int	split_space(t_split *split, char **splited_pipe, char *string)
{
	int	continue_flag;

	continue_flag = 0;
	if (split->i == 0)
	{
		split->split_flag = 1;
		split->i += 1;
		split->count_flag = split->i;
		continue_flag = 1;
	}
	else if (split->split_flag == 0)
	{
		split_space_help(split, splited_pipe, string);
		continue_flag = 1;
	}
	else if (split->split_flag == 1)
	{
		split->split_flag = 1;
		split->i += 1;
		split->count_flag = split->i;
		continue_flag = 1;
	}
	return (continue_flag);
}

void	split_smbol_w_help_start(t_split *split, char **splited_pipe,
		char *string)
{
	splited_pipe[split->count] = malloc_and_push(string, split->i + 2,
			split->i);
	split->count++;
	split->split_flag = 1;
	split->i += 2;
	split->count_flag = split->i;
}

void	split_smbol_w_help_center(t_split *split, char **splited_pipe,
		char *string)
{
	splited_pipe[split->count] = malloc_and_push(string, split->i,
			split->count_flag);
	split->count++;
	splited_pipe[split->count] = malloc_and_push(string, split->i + 2,
			split->i);
	split->count++;
	split->split_flag = 1;
	split->i += 2;
	split->count_flag = split->i;
}

int	split_smbol_w(t_split *split, char **splited_pipe, char *string)
{
	int	continue_flag;

	continue_flag = 0;
	if (split->i == 0)
	{
		split_smbol_w_help_start(split, splited_pipe, string);
		continue_flag = 1;
	}
	else if (split->split_flag == 0)
	{
		split_smbol_w_help_center(split, splited_pipe, string);
		continue_flag = 1;
	}
	else if (split->split_flag == 1)
	{
		splited_pipe[split->count] = malloc_and_push(string, split->i + 2,
				split->i);
		split->count++;
		split->split_flag = 1;
		split->i += 2;
		split->count_flag = split->i;
		continue_flag = 1;
	}
	return (continue_flag);
}

void	split_smbol_s_help_start(t_split *split, char **splited_pipe,
		char *string)
{
	splited_pipe[split->count] = malloc_and_push(string, split->i + 1,
			split->i);
	split->count++;
	split->split_flag = 1;
	split->i += 1;
	split->count_flag = split->i;
}

void	split_smbol_s_help_center(t_split *split, char **splited_pipe,
		char *string)
{
	splited_pipe[split->count] = malloc_and_push(string, split->i,
			split->count_flag);
	split->count++;
	splited_pipe[split->count] = malloc_and_push(string, split->i + 1,
			split->i);
	split->count++;
	split->split_flag = 1;
	split->i += 1;
	split->count_flag = split->i;
}

int	split_smbol_s(t_split *split, char **splited_pipe, char *string)
{
	int	continue_flag;

	continue_flag = 0;
	if (split->i == 0)
	{
		split_smbol_s_help_start(split, splited_pipe, string);
		continue_flag = 1;
	}
	else if (split->split_flag == 0)
	{
		split_smbol_s_help_center(split, splited_pipe, string);
		continue_flag = 1;
	}
	else if (split->split_flag == 1)
	{
		splited_pipe[split->count] = malloc_and_push(string, split->i + 1,
				split->i);
		split->count++;
		split->split_flag = 1;
		split->i += 1;
		split->count_flag = split->i;
		continue_flag = 1;
	}
	return (continue_flag);
}

void	add_flag(t_split *split, char *string)
{
	if (string[split->i] == '\'')
	{
		split->s_quarto_flag = 1;
	}
	if (string[split->i] == '\"')
	{
		split->w_quarto_flag = 1;
	}
	split->split_flag = 0;
}

void	last_malloc(t_split *split, char **splited_pipe, char *string)
{
	if (split->split_flag == 0)
	{
		splited_pipe[split->count] = malloc_and_push(string, split->i,
				split->count_flag);
		split->count++;
		split->split_flag = 1;
		split->i += 1;
	}
	splited_pipe[split->count] = NULL;
}

int	split_smbol_and_space(t_split *split, char **splited_pipe, char *string)
{
	int	continue_flag;

	continue_flag = 0;
	if (string[split->i] == ' ')
	{
		if (split_space(split, splited_pipe, string) == 1)
			continue_flag = 1;
	}
	else if ((string[split->i + 1] && ((string[split->i] == '>'
					&& string[split->i + 1] == '>') || (string[split->i] == '<'
					&& string[split->i + 1] == '<'))))
	{
		if (split_smbol_w(split, splited_pipe, string) == 1)
			continue_flag = 1;
	}
	else if ((string[split->i] == '|' || string[split->i] == '>'
			|| string[split->i] == '<'))
	{
		if (split_smbol_s(split, splited_pipe, string) == 1)
			continue_flag = 1;
	}
	return (continue_flag);
}

char	**split_kai(char *string, char **splited_pipe)
{
	t_split	split;

	split_kai_init(&split);
	while (string[split.i] != '\0')
	{
		if (split.s_quarto_flag == 0 && split.w_quarto_flag == 0)
		{
			if (split_smbol_and_space(&split, splited_pipe, string) == 1)
				continue ;
			add_flag(&split, string);
		}
		else if (split.s_quarto_flag == 1)
		{
			if (split.s_quarto_flag == 1 && string[split.i] == '\'')
				split.s_quarto_flag = 0;
		}
		else if (split.w_quarto_flag == 1)
		{
			if (split.w_quarto_flag == 1 && string[split.i] == '\"')
				split.w_quarto_flag = 0;
		}
		split.i++;
	}
	last_malloc(&split, splited_pipe, string);
	return (splited_pipe);
}

typedef struct s_quort_check
{
	char	*result;
	int		count_quort;
	int		w_quarto_flag;
	int		s_quarto_flag;
	int		i;
}			t_quort_check;

void	quort_check_init(t_quort_check *quort)
{
	quort->result = NULL;
	quort->count_quort = 0;
	quort->w_quarto_flag = 0;
	quort->s_quarto_flag = 0;
	quort->i = 0;
}

void	quort_check_delete_count(char *string, t_quort_check *quort)
{
	while (string[quort->i] != '\0')
	{
		if (quort->s_quarto_flag == 0 && quort->w_quarto_flag == 0)
		{
			if (string[quort->i] == '\'')
			{
				quort->count_quort++;
				quort->s_quarto_flag = 1;
			}
			if (string[quort->i] == '\"')
			{
				quort->count_quort++;
				quort->w_quarto_flag = 1;
			}
		}
		else
		{
			if (string[quort->i] == '\"' && quort->s_quarto_flag == 1)
				quort->w_quarto_flag = 0;
			if (string[quort->i] == '\'' && quort->w_quarto_flag == 1)
				quort->s_quarto_flag = 0;
		}
		quort->i++;
	}
}

int	quort_check_start_make_result(char *string, t_quort_check *quort)
{
	if (string[quort->i] == '\"')
	{
		quort->count_quort++;
		quort->w_quarto_flag = 1;
		quort->i++;
		return (1);
	}
	else if (string[quort->i] == '\'')
	{
		quort->count_quort++;
		quort->s_quarto_flag = 1;
		quort->i++;
		return (1);
	}
	return (0);
}

int	quort_check_end_make_result(char *string, t_quort_check *quort)
{
	if (string[quort->i] == '\"' && quort->w_quarto_flag == 1
		&& quort->s_quarto_flag == 0)
	{
		quort->count_quort++;
		quort->w_quarto_flag = 0;
		quort->i++;
		return (1);
	}
	else if (string[quort->i] == '\'' && quort->s_quarto_flag == 1
		&& quort->w_quarto_flag == 0)
	{
		quort->count_quort++;
		quort->s_quarto_flag = 0;
		quort->i++;
		return (1);
	}
	return (0);
}

void	quort_check_make_result(char *string, t_quort_check *quort)
{
	while (string[quort->i] != '\0')
	{
		if (quort->w_quarto_flag == 0 && quort->s_quarto_flag == 0)
		{
			if (quort_check_start_make_result(string, quort) == 1)
				continue ;
		}
		else
		{
			if (quort_check_end_make_result(string, quort) == 1)
				continue ;
		}
		quort->result[quort->i - quort->count_quort] = string[quort->i];
		quort->i++;
	}
}

char	*quort_check(char *string)
{
	t_quort_check	quort;

	quort_check_init(&quort);
	quort_check_delete_count(string, &quort);
	quort.result = (char *)malloc(sizeof(char) * (quort.i - quort.count_quort
				* 2 + 1)); //
	quort.i = 0;
	quort.count_quort = 0;
	quort.w_quarto_flag = 0;
	quort.s_quarto_flag = 0;
	quort_check_make_result(string, &quort);
	quort.result[quort.i - quort.count_quort] = '\0';
	free(string);
	return (quort.result);
}

// int	main(void)
// {
// 	char	string_origin[] = "";
// 	char	*string;
// 	int		token_count;
// 	char	**splited_token;
// 	t_token	*token_and_status;

// 	string = NULL;
// 	string = quort_check(string_origin);
// 	token_count = count_token(string);
// 	// printf("%d\n", token_count);
// 	splited_token = (char **)malloc(sizeof(char *) * (token_count + 1));
// 	splited_token = split_kai(string, splited_token);
// 	free(string);
// 	token_and_status = add_status_each_token(splited_token, token_count);
// 	for (int i = 0; i < token_count; i++)
// 	{
// 		// printf("%s\n", splited_token[i]);
// 		free(splited_token[i]);
// 	}
// 	free(splited_token);
// 	check_syntax(token_and_status);
// 	// token_and_status = input_cmd_check(token_and_status, token_count);
// 	for (int i = 0; i < token_count; i++)
// 	{
// 		printf("aa%saa", token_and_status[i].str);
// 		free(token_and_status[i].str);
// 		// printf("%d\n", token_and_status[i].type);
// 	}
// 	free(token_and_status);
// 	// printf("%d", token_count);
// 	return (0);
// }
