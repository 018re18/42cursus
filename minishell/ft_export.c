/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:43:09 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/07 15:13:47 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_identifier(char *identifier)
{
	int	i;

	if (!identifier || identifier[0] == '\0')
		return (FALSE);
	if (!(identifier[0] == '_' || ('A' <= identifier[0] && identifier[0] <= 'Z')
			|| ('a' <= identifier[0] && identifier[0] <= 'z')))
	{
		return (FALSE);
	}
	i = 1;
	while (identifier[i] && identifier[i] != '=')
	{
		if (identifier[i] == '+' && identifier[i + 1] == '=')
			return (3);
		else if (!(identifier[i] == '_' || ('A' <= identifier[i]
					&& identifier[i] <= 'Z') || ('a' <= identifier[i]
					&& identifier[i] <= 'z') || ('0' <= identifier[i]
					&& identifier[i] <= '9')))
		{
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	export_loop(char **args, t_envp_data *envp_data)
{
	int	i;
	int	check_num;
	int	invalid_identifier;

	i = 1;
	invalid_identifier = 0;
	while (args[i])
	{
		check_num = check_identifier(args[i]);
		if (check_num == 3)
		{
			*envp_data = append_envp(*envp_data, args[i]);
		}
		else if (check_num == FALSE)
		{
			invalid_identifier = 1;
			write(2, "minishell: export: `", 20);
			write(2, args[i], ft_strlen(args[i]));
			write(2, "': not a valid identifier\n", 26);
		}
		else
			*envp_data = add_envp(*envp_data, args[i]);
		i++;
	}
	return (invalid_identifier);
}

int	ft_export(char **args, t_envp_data *envp_data)
{
	int		i;
	char	*key;
	int		exit_status;

	if (args[1] == NULL)
	{
		i = 0;
		*envp_data = envp_line_up(*envp_data);
		while (envp_data->envp[i] != NULL)
		{
			if (ft_strncmp(envp_data->envp[i], "_=", 2) != 0)
			{
				key = set_key(envp_data->envp[i]);
				printf("declare -x %s=\"", key);
				printf("%s\"\n", &envp_data->envp[i][ft_strlen(key) + 1]);
				free(key);
			}
			i++;
		}
		exit_status = 0;
	}
	else
		exit_status = export_loop(args, envp_data);
	return (exit_status);
}
