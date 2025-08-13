/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doll_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:50:56 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/20 13:35:05 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_envp(char *key, t_envp_data envp_data)
{
	int	i;

	i = 0;
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

void	doller_open_variable_reset(t_doller_open *doller)
{
	doller->k = 0;
	doller->char_count = 0;
	doller->i = 0;
	doller->s_quort_flag = 0;
	doller->w_quort_flag = 0;
}

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
