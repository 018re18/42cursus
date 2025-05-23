/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:33:55 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/23 12:37:25 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	*stkdup(int *stka, int argc)
{
	int	*stkcpy;
	int	i;

	stkcpy = (int *)malloc(sizeof(int) * (argc - 1));
	if (!stkcpy)
		return (NULL);
	i = 0;
	while (i < argc - 1)
	{
		stkcpy[i] = stka[i];
		i++;
	}
	return (stkcpy);
}

static void	swap_num(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int	class_num(int *stk, int min, int max)
{
	int	pivot;
	int	s_area;

	pivot = (max + min) / 2;
	swap_num(&stk[max], &stk[pivot]);
	s_area = min - 1;
	while (min < max)
	{
		if (stk[min] < stk[max])
		{
			s_area++;
			swap_num(&stk[s_area], &stk[min]);
		}
		min++;
	}
	swap_num(&stk[s_area + 1], &stk[max]);
	return (s_area + 1);
}

void	ft_quick_sort(int *stk, int min, int max)
{
	int	pivot_place;

	if (min < max)
	{
		pivot_place = class_num(stk, min, max);
		ft_quick_sort(stk, min, pivot_place - 1);
		ft_quick_sort(stk, pivot_place + 1, max);
	}
}

void	get_sortstk_rank(t_stk *a, int argc)
{
	t_stk	cpy;

	cpy.stk = NULL;
	cpy.rank = NULL;
	cpy.stk = stkdup(a->stk, argc);
	if (!cpy.stk)
		return ;
	ft_quick_sort(cpy.stk, 0, argc - 2);
	if (check_same(cpy.stk, argc - 1))
	{
		free(cpy.stk);
		return ;
	}
	sort_rank(&cpy, a, argc - 1);
	free(cpy.stk);
}
