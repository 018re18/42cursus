/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_slice.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:12:03 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/19 19:23:58 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	search_cnk_num(t_stk *A, int min, int max)
{
	int	i;
	int	j;

	i = 0;
	j = A->len - 1;
	while (i <= j)
	{
		if (min <= A->rank[i] && A->rank[i] <= max)
			return (1);
		if (min <= A->rank[j] && A->rank[j] <= max)
			return (0);
		i++;
		j--;
	}
	return (-1);
}

static void	mv_A_to_B(t_stk *A, t_stk *B, int min, int max, int num)
{
	int	j;
	int	count;
	int	i;

	count = 0;
	while (count < num)
	{
		i = search_cnk_num(A, min, max);
		if (i < 0)
			return ;
		j = 0;
		while (j < A->len)
		{
			if (min <= A->rank[0] && A->rank[0] <= max)
			{
				pb(A, B);
				count++;
				if (B->rank[0] < (max + min) / 2)
					rb(B, 1);
				break ;
			}
			else
			{
				if (i == 1)
					ra(A, 1);
				else
					rra(A, 1);
			}
			j++;
		}
	}
}

static void	sort_A_to_B(t_stk *A, t_stk *B, int cnk_size, int cnk_num)
{
	int	i;
	int	cnk_min;
	int	cnk_max;

	i = 0;
	while (i < cnk_num)
	{
		cnk_min = cnk_size * i;
		cnk_max = cnk_size * (i + 1) - 1;
		mv_A_to_B(A, B, cnk_min, cnk_max, cnk_size);
		i++;
	}
}

static int	search_max_num(t_stk *B, int max)
{
	int	i;
	int	j;

	i = 0;
	j = B->len - 1;
	while (i <= j)
	{
		if (B->rank[i] == max)
			return (1);
		if (B->rank[j] == max)
			return (0);
		i++;
		j--;
	}
	return (-1);
}
static void	sort_B_to_A(t_stk *A, t_stk *B, int max, int num)
{
	int	count;
	int	max_num;
	int	j;
	int	i;

	max_num = max;
	count = 0;
	while (count < num)
	{
		i = search_max_num(B, max_num);
		if (i < 0)
			return ;
		j = 0;
		while (j < B->len)
		{
			if (B->rank[0] == max_num)
			{
				pa(A, B);
				count++;
				max_num--;
				break ;
			}
			else if (i == 1)
				rb(B, 1);
			else
				rrb(B, 1);
			j++;
		}
	}
}

void	slice_sort(t_stk *A, t_stk *B, int min, int max)
{
	int	sort_size;
	int	cnk_size;
	int	cnk_num;

	sort_size = max - min + 1;
	if (sort_size <= 6)
	{
		// mini_slice(A, B, min, max);
		return ;
	}
	else if (sort_size == 100)
		cnk_size = 25;
	else if (sort_size == 500)
		cnk_size = 50;
	else
		return ;
	cnk_num = sort_size / cnk_size;
	sort_A_to_B(A, B, cnk_size, cnk_num);
	sort_B_to_A(A, B, max, sort_size);
}
