/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:37:28 by kryutaro          #+#    #+#             */
/*   Updated: 2025/07/10 13:53:11 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_init_help(char **envp, t_envp_data *result)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	result->envp_count = i;
	result->envp_volume = i;
	result->envp = (char **)malloc(sizeof(char *) * (i + 1));
}

t_envp_data	envp_init(char **envp)
{
	int			i;
	int			j;
	t_envp_data	result;

	env_init_help(envp, &result);
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '\0')
			j++;
		result.envp[i] = (char *)malloc(sizeof(char) * (j + 1));
		j = 0;
		while (envp[i][j] != '\0')
		{
			result.envp[i][j] = envp[i][j];
			j++;
		}
		result.envp[i][j] = '\0';
		i++;
	}
	result.envp[i] = NULL;
	return (result);
}

int	cmp_key(const char *key, const char *str)
{
	int	i;

	i = 0;
	if (!key || !str)
		return (1);
	while (key[i] != '\0' && str[i] != '\0' && key[i] == str[i])
	{
		i++;
	}
	if (key[i] == '\0' && str[i] == '=')
		return (0);
	return (1);
}

typedef struct s_delete_envp
{
	t_envp_data	new_envp_data;
	int			i;
	int			j;
	int			delete_flag;
}				t_delete_envp;

void	delete_envp_help(t_envp_data prev_envp_data, char *key,
		t_delete_envp *delete)
{
	while (delete->i < prev_envp_data.envp_count)
	{
		delete->j = 0;
		if (cmp_key(key, prev_envp_data.envp[delete->i]) == 0
			&& delete->delete_flag == 0)
		{
			free(prev_envp_data.envp[delete->i]);
			delete->i++;
			delete->delete_flag = 1;
			continue ;
		}
		while (prev_envp_data.envp[delete->i][delete->j] != '\0')
			delete->j++;
		delete->new_envp_data.envp[delete->i
			- delete->delete_flag] = (char *)malloc(sizeof(char) * (delete->j
					+ 1));
		delete->j = 0;
		while (prev_envp_data.envp[delete->i][delete->j] != '\0')
		{
			delete->new_envp_data.envp[delete->i
				- delete->delete_flag][delete->j] = prev_envp_data.envp[delete->i][delete->j];
			delete->j++;
		}
		delete->new_envp_data.envp[delete->i
			- delete->delete_flag][delete->j] = '\0';
		free(prev_envp_data.envp[delete->i]);
		delete->i++;
	}
}

t_envp_data	delete_envp(t_envp_data prev_envp_data, char *key)
{
	t_delete_envp	delete;
	char			*joined_key;
	char			*key_a;

	if (key[0] == '\0')
	{
		return (prev_envp_data);
	}
	joined_key = ft_strjoin("$", key);
	key_a = ft_doller(joined_key, prev_envp_data);
	if (ft_strcmp(joined_key, key_a) == 0)
	{
		free(joined_key);
		free(key_a);
		return (prev_envp_data);
	}
	free(joined_key);
	free(key_a);
	delete.delete_flag = 0;
	delete.new_envp_data.envp = (char **)malloc(sizeof(char *)
			* (prev_envp_data.envp_count));
	delete.i = 0;
	delete_envp_help(prev_envp_data, key, &delete);
	free(prev_envp_data.envp);
	delete.new_envp_data.envp[delete.i - delete.delete_flag] = NULL;
	delete.new_envp_data.envp_count = prev_envp_data.envp_count - 1;
	delete.new_envp_data.envp_volume = prev_envp_data.envp_volume - 1;
	return (delete.new_envp_data);
}

char	*set_key(char *key_and)
{
	int		i;
	char	*key;

	i = 0;
	while (key_and[i] != '\0' && key_and[i] != '=')
		i++;
	key = (char *)malloc(sizeof(char) * i + 1);
	i = 0;
	while (key_and[i] != '\0' && key_and[i] != '=')
	{
		key[i] = key_and[i];
		i++;
	}
	key[i] = '\0';
	i = 0;
	while (key[i] != '\0')
	{
		if (key[i] == '+')
		{
			key[i] = '\0';
		}
		i++;
	}
	return (key);
}

typedef struct s_add_envp
{
	t_envp_data	new_envp_data;
	int			i;
	int			j;
	char		*key;
	char		key_flag;

}				t_add_envp;

void	add_envp_help(t_envp_data *prev_envp_data, char *key_and,
		t_add_envp *add)
{
	while (/*add->i < prev_envp_data->envp_count*/ prev_envp_data->envp[add->i] != NULL)
	{
		// printf("%s\n", prev_envp_data->envp[add->i]);
		if (cmp_key(add->key, prev_envp_data->envp[add->i]) == 0)
			add->key_flag = 1;
		add->j = 0;
		while (prev_envp_data->envp[add->i][add->j] != '\0')
			add->j++;
		add->new_envp_data.envp[add->i] = (char *)malloc(sizeof(char) * (add->j
					+ 1));
		add->j = 0;
		while (prev_envp_data->envp[add->i][add->j] != '\0')
		{
			add->new_envp_data.envp[add->i][add->j] = prev_envp_data->envp[add->i][add->j];
			add->j++;
		}
		add->new_envp_data.envp[add->i][add->j] = '\0';
		free(prev_envp_data->envp[add->i]);
		add->i++;
	}
	add->j = 0;
	while (key_and[add->j] != '\0')
		add->j++;
	add->new_envp_data.envp[add->i] = (char *)malloc(sizeof(char) * (add->j
				+ 1));
	add->j = 0;
}

t_envp_data	add_envp(t_envp_data prev_envp_data, char *key_and)
{
	t_add_envp	add;

	add.key_flag = 0;
	add.key = set_key(key_and);
	add.new_envp_data.envp = (char **)malloc(sizeof(char *)
			* (prev_envp_data.envp_count + 2));
	add.i = 0;
	add_envp_help(&prev_envp_data, key_and, &add);
	while (key_and[add.j] != '\0')
	{
		add.new_envp_data.envp[add.i][add.j] = key_and[add.j];
		add.j++;
	}
	add.new_envp_data.envp[add.i][add.j] = '\0';
	add.i++;
	free(prev_envp_data.envp);
	add.new_envp_data.envp[add.i] = NULL;
	add.new_envp_data.envp_count = prev_envp_data.envp_count + 1;
	add.new_envp_data.envp_volume = prev_envp_data.envp_volume + 1;
	if (add.key_flag == 1)
	{
		add.new_envp_data = delete_envp(add.new_envp_data, add.key);
	}
	free(add.key);
	return (add.new_envp_data);
}
typedef struct s_append_envp
{
	t_envp_data	new_envp_data;
	int			i;
	int			j;
	char		*key;
	char		key_flag;
	char		*tmp;
}				t_append_envp;

void	append_envp_check_key(t_envp_data prev_envp_data, char *key_and,
		t_append_envp *append)
{
	while (prev_envp_data.envp[append->i] != NULL)
	{
		if (cmp_key(append->key, prev_envp_data.envp[append->i]) == 0)
		{
			append->key_flag = append->i;
		}
		append->j = 0;
		while (prev_envp_data.envp[append->i][append->j] != '\0')
			append->j++;
		append->new_envp_data.envp[append->i] = (char *)malloc(sizeof(char)
				* (append->j + 1));
		append->j = 0;
		while (prev_envp_data.envp[append->i][append->j] != '\0')
		{
			append->new_envp_data.envp[append->i][append->j] = prev_envp_data.envp[append->i][append->j];
			append->j++;
		}
		append->new_envp_data.envp[append->i][append->j] = '\0';
		free(prev_envp_data.envp[append->i]);
		append->i++;
	}
}

void	append_envp_write(t_envp_data prev_envp_data, char *key_and,
		t_append_envp *append)
{
	if (append->key_flag != -1)
	{
		append->tmp = ft_strjoin(append->new_envp_data.envp[append->key_flag],
				&key_and[ft_strlen(append->key) + 2]);
		free(append->new_envp_data.envp[append->key_flag]);
		append->new_envp_data.envp[append->key_flag] = append->tmp;
	}
	else
	{
		append->j = 0;
		while (key_and[append->j] != '\0')
			append->j++;
		append->new_envp_data.envp[append->i] = (char *)malloc(sizeof(char)
				* (append->j + 1));
		append->j = 0;
		while (key_and[append->j] != '\0')
		{
			append->new_envp_data.envp[append->i][append->j] = key_and[append->j];
			append->j++;
		}
		append->new_envp_data.envp[append->i][append->j] = '\0';
		append->i++;
	}
}

t_envp_data	append_envp(t_envp_data prev_envp_data, char *key_and)
{
	t_append_envp	append;

	append.key_flag = -1;
	append.key = set_key(key_and);
	append.new_envp_data.envp = (char **)malloc(sizeof(char *)
			* (prev_envp_data.envp_count + 1));
	append.i = 0;
	append_envp_check_key(prev_envp_data, key_and, &append);
	append_envp_write(prev_envp_data, key_and, &append);
	free(prev_envp_data.envp);
	append.new_envp_data.envp[append.i] = NULL;
	append.new_envp_data.envp_count = prev_envp_data.envp_count;
	append.new_envp_data.envp_volume = prev_envp_data.envp_volume;
	free(append.key);
	return (append.new_envp_data);
}

typedef struct s_doll
{
	char		*key;
	char		*result;
	int			doller_flag;
	int			i;
	int			j;
	int			key_char_count;
	int			envp_count;
	int			flag;

}				t_doll;

void	ft_doller_make_key_capacity(char *token, t_doll *doll)
{
	while (token[doll->i] != '\0')
	{
		if (token[doll->i] == '$')
		{
			doll->j = doll->i;
			while (token[doll->i] != '\0')
			{
				doll->i++;
			}
			doll->key = (char *)malloc(sizeof(char) * (doll->i - doll->j));
			doll->i = doll->j + 1;
			while (token[doll->i] != '\0')
			{
				doll->key[doll->i - doll->j - 1] = token[doll->i];
				doll->i++;
			}
			doll->key[doll->i - doll->j - 1] = '\0';
			doll->doller_flag = 1;
			break ;
		}
		doll->i++;
	}
}

void	ft_doller_make_capacity(char *token, t_envp_data envp_data,
		t_doll *doll)
{
	doll->doller_flag = 0;
	doll->i = 0;
	while (token[doll->i] != '\0')
	{
		if (token[doll->i] == '$')
		{
			while (envp_data.envp[doll->envp_count])
			{
				if (cmp_key(doll->key, envp_data.envp[doll->envp_count]) == 0)
				{
					doll->j = 0;
					while (envp_data.envp[doll->envp_count][doll->j] != '\0')
						doll->j++;
					while (doll->key[doll->key_char_count] != '\0')
						doll->key_char_count++;
					break ;
				}
				doll->envp_count++;
			}
		}
		doll->i++;
	}
	doll->result = (char *)malloc(sizeof(char) * (doll->i + doll->j
				- doll->key_char_count + 1));
}

int	ft_doller_make_result_help(char *token, t_envp_data envp_data, t_doll *doll)
{
	if (cmp_key(doll->key, envp_data.envp[doll->envp_count]) == 0)
	{
		doll->j = 0;
		while (envp_data.envp[doll->envp_count][doll->j + doll->key_char_count
			+ 1] != '\0')
		{
			doll->result[doll->i
				+ doll->j] = envp_data.envp[doll->envp_count][doll->j
				+ doll->key_char_count + 1];
			doll->j++;
		}
		doll->doller_flag = 1;
		return (1);
	}
	return (0);
}

void	ft_doller_make_result(char *token, t_envp_data envp_data, t_doll *doll)
{
	while (token[doll->i] != '\0')
	{
		if (token[doll->i] == '$')
		{
			while (envp_data.envp[doll->envp_count])
			{
				if (ft_doller_make_result_help(token, envp_data, doll) == 1)
					break ;
				doll->envp_count++;
			}
		}
		if (doll->doller_flag == 1)
			break ;
		doll->result[doll->i] = token[doll->i];
		doll->i++;
	}
	doll->result[doll->i + doll->j] = '\0';
}

char	*ft_doller(char *token, t_envp_data envp_data)
{
	t_doll	doll;

	doll.envp_count = 0;
	doll.key_char_count = 0;
	doll.i = 0;
	doll.doller_flag = 0;
	ft_doller_make_key_capacity(token, &doll);
	ft_doller_make_capacity(token, envp_data, &doll);
	doll.i = 0;
	doll.envp_count = 0;
	ft_doller_make_result(token, envp_data, &doll);
	free(doll.key);
	return (doll.result);
}

t_envp_data	envp_line_up(t_envp_data envp_data)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (envp_data.envp[i] != NULL)
	{
		j = i + 1;
		while (envp_data.envp[j] != NULL)
		{
			if (ft_strcmp(envp_data.envp[i], envp_data.envp[j]) > 0)
			{
				tmp = envp_data.envp[j];
				envp_data.envp[j] = envp_data.envp[i];
				envp_data.envp[i] = tmp;
			}
			j++;
		}
		i++;
	}
	return (envp_data);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_envp_data	envp_data;
// 	int			i;
// 	char		*key_and;

// 	i = 0;
// 	envp_data = envp_init(envp);
// 	// envp_data = delete_envp(envp_data, "TERM");
// 	envp_data = apend_envp(envp_data, "TERN=ospaohugasifsidsaoid");
// 	// i = 0;
// 	// while (envp_data.envp[i])
// 	// {
// 	// 	printf("%s\n", envp_data.envp[i]);
// 	// 	free(envp_data.envp[i]);
// 	// 	i++;
// 	// }
// 	// free(envp_data.envp);
// 	// key_and = ft_doller("aaaa$OLDPWD", envp_data);
// 	// printf("%s", key_and);
// 	while (envp_data.envp[i])
// 	{
// 		printf("%s\n",envp_data.envp[i]);
// 		free(envp_data.envp[i]);
// 		i++;
// 	}
// 	free(envp_data.envp);
// 	// free(key_and);
// 	return (0);
// }
