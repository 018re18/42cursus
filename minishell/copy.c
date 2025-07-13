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

char	*doller_open_help(char *string, t_envp_data envp_data, int exit_status)
{
	t_doller_open doller;

	doller.stop_flag = 0;
	doller.stop_flag_int = 0;
	doller.w_quort_flag = 0;
	doller.k = 0;
	doller.char_count = 0;
	doller.i = 0;
	doller.s_quort_flag = 0;
	if (string == NULL)
	{
		return (NULL);
	}
	while (string[doller.i] != '\0')
	{
		doller.j = 1;
		if (doller.s_quort_flag == 0)
		{
			if (string[doller.i] == '$')
			{
				doller.j = 0;
				if (string[doller.i + 1] && is_al_num(string[doller.i + 1]) == 1) //
				{
					doller.char_count = doller.char_count + 1;
					doller.i = doller.i + 1;
					continue ;
				}
				if (string[doller.i + 1] && string[doller.i + 1] == '?')
				{
					doller.string_exit_status = ft_itoa(exit_status);
					doller.char_count = doller.char_count + ft_strlen(doller.string_exit_status);
					doller.i = doller.i + 2;
					free(doller.string_exit_status);
					continue ;
				}
				else
				{
					doller.j++;
					while (string[doller.i + doller.j] != '\0' && string[doller.i + doller.j] != '\"'
						&& is_al_num(string[doller.i + doller.j]) == 0)
					{
						doller.j++;
					}
					if (string[doller.i + doller.j] == '\"' || is_al_num(string[doller.i + doller.j]) == 1)
					{
						doller.stop_flag = string[doller.i + doller.j];
						doller.stop_flag_int = 1;
						doller.j++;
					}
					doller.doller_word = (char *)malloc(sizeof(char) * (doller.j + 1));
					doller.j = 0;
					doller.doller_word[doller.j] = string[doller.i + doller.j];
					doller.j++;
					while ((string[doller.i + doller.j] != '\0' && string[doller.i + doller.j] != '\"'
							&& is_al_num(string[doller.i + doller.j]) == 0))
					{
						doller.doller_word[doller.j] = string[doller.i + doller.j];
						doller.j++;
					}
					doller.doller_word[doller.j] = '\0';
					if (search_envp(doller.doller_word, envp_data) == 0)
					{
						doller.opened_doller_word = ft_doller(doller.doller_word, envp_data);
					}
					else
					{
						doller.opened_doller_word = (char *)malloc(sizeof(char));
						doller.opened_doller_word[0] = '\0';
					}
					doller.k = 0;
					while (doller.opened_doller_word[doller.k] != '\0')
					{
						doller.k++;
						doller.char_count++;
					}
					free(doller.opened_doller_word);
					break ;
				}
			}
		}
		if (string[doller.i] == '\'' && doller.w_quort_flag == 0)
		{
			if (doller.s_quort_flag == 0)
			{
				doller.s_quort_flag = 1;
			}
			else if (doller.s_quort_flag == 1)
			{
				doller.s_quort_flag = 0;
			}
		}
		if (string[doller.i] == '\"' && doller.s_quort_flag == 0)
		{
			if (doller.w_quort_flag == 0)
			{
				doller.w_quort_flag = 1;
			}
			else if (doller.w_quort_flag == 1)
			{
				doller.w_quort_flag = 0;
			}
		}
		doller.char_count++;
		doller.i = doller.i + doller.j;
	}
	doller.result = (char *)malloc(sizeof(char) * (doller.char_count + 1 + doller.stop_flag_int));
	doller.k = 0;
	doller.char_count = 0;
	doller.i = 0;
	doller.s_quort_flag = 0;
	doller.w_quort_flag = 0;
	while (string[doller.i] != '\0')
	{
		doller.j = 1;
		if (doller.s_quort_flag == 0)
		{
			if (string[doller.i] == '$')
			{
				doller.j = 0;
				if (string[doller.i + 1] && is_al_num(string[doller.i + 1]) == 1) //
				{
					doller.string_exit_status = (char *)malloc(sizeof(char) * 2);
					doller.string_exit_status[0] = '$';
					doller.string_exit_status[1] = '\0';
					while (doller.j < ft_strlen(doller.string_exit_status))
					{
						doller.result[doller.char_count] = doller.string_exit_status[doller.j];
						doller.char_count++;
						doller.j++;
					}
					free(doller.string_exit_status);
					doller.j = 0;
					doller.i = doller.i + 1;
					continue ;
				}
				if (string[doller.i + 1] && string[doller.i + 1] == '?')
				{
					doller.string_exit_status = ft_itoa(exit_status);
					while (doller.j < ft_strlen(doller.string_exit_status))
					{
						doller.result[doller.char_count] = doller.string_exit_status[doller.j];
						//なんかふりーわすれてそう
						doller.char_count++;
						doller.j++;
					}
					free(doller.string_exit_status);
					doller.j = 0;
					doller.i = doller.i + 2;
					continue ;
				}
				else
				{
					doller.j++;
					while (string[doller.i + doller.j] != '\0' && string[doller.i + doller.j] != '\"'
						&& is_al_num(string[doller.i + doller.j]) == 0)
					{
						doller.j++;
					}
					doller.opened_doller_word = NULL;
					if (search_envp(doller.doller_word, envp_data) == 0)
					{
						doller.opened_doller_word = ft_doller(doller.doller_word, envp_data);
					}
					else
					{
						doller.opened_doller_word = (char *)malloc(sizeof(char));
						doller.opened_doller_word[0] = '\0';
					}
					free(doller.doller_word);
					if (doller.opened_doller_word[0] == '$'
						&& doller.opened_doller_word[1] != '\0')
					{
						free(doller.opened_doller_word);
						doller.opened_doller_word = (char *)malloc(sizeof(char));
						doller.opened_doller_word[0] = '\0';
					}
					doller.k = 0;
					while (doller.opened_doller_word[doller.k] != '\0')
					{
						doller.result[doller.char_count] = doller.opened_doller_word[doller.k];
						doller.char_count++;
						doller.k++;
					}
					if (doller.stop_flag != 0)
					{
						doller.result[doller.char_count] = doller.stop_flag;
						doller.char_count++;
					}
					free(doller.opened_doller_word);
					break ;
				}
			}
		}
		if (string[doller.i] == '\'' && doller.w_quort_flag == 0)
		{
			if (doller.s_quort_flag == 0)
			{
				doller.s_quort_flag = 1;
			}
			else if (doller.s_quort_flag == 1)
			{
				doller.s_quort_flag = 0;
			}
		}
		if (string[doller.i] == '\"' && doller.s_quort_flag == 0)
		{
			if (doller.w_quort_flag == 0)
			{
				doller.w_quort_flag = 1;
			}
			else if (doller.w_quort_flag == 1)
			{
				doller.w_quort_flag = 0;
			}
		}
		doller.result[doller.char_count] = string[doller.i];
		doller.char_count++;
		doller.i = doller.i + doller.j;
	}
	doller.result[doller.char_count] = '\0';
	if (string[doller.i] != '\0')
		doller.i++;
	while (string[doller.i] != '\0' && string[doller.i] != '\"' && is_al_num(string[doller.i]) == 0)
		doller.i++;
	if (string[doller.i] != '\0' && (string[doller.i] == '\"' || is_al_num(string[doller.i]) == 1))
		doller.i++;
	if (string[doller.i] == '\0')
		doller.suffix = "";
	else
		doller.suffix = &string[doller.i];
	doller.result_join = ft_strdoller.join(doller.result, doller.suffix);
	free(doller.result);
	return (doller.result_join);
}