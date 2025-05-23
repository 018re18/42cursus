/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:04:16 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/23 13:26:58 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	*ft_memset(int *s, int c, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		s[i] = c;
		i++;
	}
	return (s);
}

static void	free_all(t_stk *a, t_stk *b)
{
	if (a->stk)
		free(a->stk);
	if (a->rank)
		free(a->rank);
	if (b->stk)
		free(b->stk);
	if (b->rank)
		free(b->rank);
}

int	prepare(int argc, char **argv, t_stk *a, t_stk *b)
{
	a->stk = get_stka(argc, argv);
	b->stk = (int *)malloc(sizeof(int) * (argc - 1));
	if (!a->stk || !b->stk)
	{
		free_all(a, b);
		write(2, "Error\n", 6);
		return (-1);
	}
	a->len = argc - 1;
	b->len = 0;
	a->rank = NULL;
	b->rank = NULL;
	get_sortstk_rank(a, argc);
	b->rank = (int *)malloc(sizeof(int) * (argc - 1));
	if (!a->rank || !b->rank)
	{
		free_all(a, b);
		write(2, "Error\n", 6);
		return (-1);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_stk	a;
	t_stk	b;
	t_res	res;
	int		pre;

	if (argc <= 1)
		return (0);
	pre = prepare(argc, argv, &a, &b);
	if (pre < 0)
		return (-1);
	res.place = 0;
	ft_memset(res.result, 0, 8000);
	res.min = 0;
	res.max = argc - 2;
	slice_sort(&a, &b, &res);
	check_rrr(res.result);
	put_res(res.result);
	free_all(&a, &b);
	return (0);
}
