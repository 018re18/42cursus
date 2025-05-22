/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:11:39 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/22 19:12:50 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"push_swap.h"

static int	sign(char *str, int *i)
{
	int	j;

	j = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			j = -1;
		(*i)++;
	}
	return (j);
}

int	ft_atoi_sp(char *str, int *error)
{
	t_ati	a;

	a.i = 0;
	a.j = sign(str, &a.i);
	if (!str[a.i])
	{
		*error = 0;
		return (0);
	}
	a.num = 0;
	while (str[a.i])
	{
		if (!('0' <= str[a.i] && str[a.i] <= '9'))
		{
			*error = 0;
			return (0);
		}
		a.num = a.num * 10 + (str[a.i] - '0');
		if (INT_MIN > a.num * a.j || a.num * a.j > INT_MAX)
		{
			return (*error = 0, 0);
		}
		a.i++;
	}
	return ((int)(a.num * a.j));
}

int	*get_stkA(int argc, char **argv)
{
	int	i;
	int	*stkA;
	int	error;

	stkA = (int *)malloc(sizeof(int) * (argc - 1));
	if (!stkA)
		return (NULL);
	i = 1;
	while (i < argc)
	{
		error = 1;
		stkA[i - 1] = ft_atoi_sp(argv[i], &error);
		if (error == 0)
		{
			free(stkA);
			return (NULL);
		}
		i++;
	}
	return (stkA);
}
