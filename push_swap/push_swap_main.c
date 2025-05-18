/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:04:16 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/18 20:30:54 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	sign(char *str, int *i)
{
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			return (-1);
		(*i)++;
	}
	return (1);
}
int	ft_atoi_sp(char *str, int *error)
{
	int		i;
	int		j;
	long	num;

	i = 0;
	j = sign(str, &i);
	if (!str[i])
	{
		*error = 0;
		return (0);
	}
	num = 0;
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
		{
			*error = 0;
			return (0);
		}
		num = num * 10 + (str[i] - '0');
		if (INT_MIN > num * j || num * j > INT_MAX)
		{
			*error = 0;
			return (0);
		}
		i++;
	}
	return ((int)(num * j));
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

static void	free_all(t_stk *A, t_stk *B)
{
	if (A->stk)
		free(A->stk);
	if (A->rank)
		free(A->rank);
	if (B->stk)
		free(B->stk);
	if (B->rank)
		free(B->rank);
}

int	main(int argc, char **argv)
{
	t_stk	A;
	t_stk	B;
	t_stk	res_stk;

	if (argc <= 1)
		return (0);
	A.stk = get_stkA(argc, argv);
	B.stk = (int *)malloc(sizeof(int) * (argc - 1));
	A.len = argc - 1;
	B.len = 0;
	A.rank = NULL;
	B.rank = NULL;
	if (!A.stk || !B.stk)
	{
		free_all(&A, &B);
		write(2, "Error\n", 6);
		return (-1);
	}
	res_stk = get_sortstk_rank(&A, argc);
	if (!res_stk.stk && !A.rank)
	{
		free_all(&A, &B);
		write(2, "Error\n", 6);
		return (-1);
	}
	B.rank = (int *)malloc(sizeof(int) * (argc - 1));
	if (!B.rank)
	{
		free_all(&A, &B);
		write(2, "Error\n", 6);
		return (-1);
	}
	slice_sort(&A, &B, 0, argc - 2);
	free_all(&A, &B);
	return (0);
}
