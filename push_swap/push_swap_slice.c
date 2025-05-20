/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_slice.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:12:03 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/20 20:47:55 by rookuma          ###   ########.fr       */
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

static void	sort_sA(t_stk *A)
{
	int	a;
	int	b;
	int	c;

	if (A->len < 2)
		return ;
	if (A->len == 2)
	{
		if (A->rank[0] > A->rank[1])
			sa(A, 1);
		return ;
	}
	a = A->rank[0];
	b = A->rank[1];
	c = A->rank[2];
	if (a > b && a > c)
		ra(A, 1);
	else if (b > a && b > c)
		rra(A, 1);
	if (A->rank[0] > A->rank[1])
		sa(A, 1);
}

static void	sort_sB(t_stk *B)
{
	int	a;
	int	b;
	int	c;

	if (B->len < 2)
		return ;
	if (B->len == 2)
	{
		if (B->rank[0] < B->rank[1])
			sb(B, 1);
		return ;
	}
	a = B->rank[0];
	b = B->rank[1];
	c = B->rank[2];
	if (a < b && a < c)
		rb(B, 1);
	else if (b < a && b < c)
		rrb(B, 1);
	if (B->rank[0] < B->rank[1])
		sb(B, 1);
}

static void	mini_slice(t_stk *A, t_stk *B, int size)
{
	int	i;
	int	j;
	int	k;

	if (size <= 3)
	{
		sort_sA(A);
		return ;
	}
	i = size - 3;
	k = 0;
	while (i > 0)
	{
		j = 0;
		while (j < A->len && A->rank[j] != k)
			j++;
		if (j <= A->len / 2)
		{
			while (j > 0)
			{
				ra(A, 1);
				j--;
			}
		}
		else
		{
			j = A->len - j;
			while (j > 0)
			{
				rra(A, 1);
				j--;
			}
		}
		pb(A, B);
		k++;
		i--;
	}
	sort_sA(A);
	sort_sB(B);
	while (B->len > 0)
		pa(A, B);
}

void	slice_sort(t_stk *A, t_stk *B, int min, int max)
{
	int	sort_size;
	int	cnk_size;
	int	cnk_num;

	sort_size = max - min + 1;
	if (sort_size <= 6)
	{
		mini_slice(A, B, sort_size);
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
