/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_body1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:44:13 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/15 20:18:34 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sort_A_to_B(t_stk *A, t_stk *B, int min, int max)
{
	int	pivot;
	int	i;
	int	j;
	int	count_B;

	pivot = min + (max - min) / 2;
	i = 0;
	j = max - min + 1;
	count_pb = 0;
	while (i < j)
	{
		if (A->rank[i] <= pivot)
		{
			pb(A, B);
			count_B++;
		}
		else
		{
			ra(A, 1);
		}
		i++;
	}
	return (count_B);
}

int	sort_B_to_A(t_stk *A, t_stk *B, int min, int max)
{
	int	pivot;
	int	i;
	int	j;

	pivot = min + (max - min) / 2;
	i = 0;
	j = max - min + 1;
	while (i < j)
	{
		if (B->rank > pivot)
		{
			pa(A, B);
		}
		else
		{
			rb(B, 1);
		}
		i++;
	}
	return (pivot);
}

void	sort_sA(t_stk *A)
{
	int	a;
	int	b;
	int	c;

	a = A->stk[0];
	b = A->stk[1];
	c = A->stk[2];
	if (A->len == 2)
	{
		if (a > b)
			sa(A, 1);
		return ;
	}
	if (a < b && b < c)
		return ;
	else if (a < c && c < b)
	{
		sa(A, 1);
		ra(A, 1);
	}
	else if (b < a && a < c)
	{
		sa(A, 1);
	}
	else if (b < c && c < a)
	{
		rra(A, 1);
	}
	else if (c > a && a < b)
	{
		ra(A, 1);
	}
	else if (c < b && b < a)
	{
		sa(A, 1);
		rra(A, 1);
	}
}

void	sort_sB(t_stk *B)
{
	int	a;
	int	b;
	int	c;

	a = B->stk[0];
	b = B->stk[1];
	c = B->stk[2];
	if (B->len == 2)
	{
		if (a > b)
			sb(B, 1);
		return ;
	}
	if (a < b && b < c)
		return ;
	else if (a < c && c < b)
	{
		sb(B, 1);
		rb(B, 1);
	}
	else if (b < a && a < c)
	{
		sb(B, 1);
	}
	else if (b < c && c < a)
	{
		rrb(B, 1);
	}
	else if (c > a && a < b)
	{
		rb(B, 1);
	}
	else if (c < b && b < a)
	{
		sb(B, 1);
		rrb(B, 1);
	}
}

void	quick_sort_sp(t_stk *A, t_stk *B, int min, int max)
{
	int	count_B;

	if ((max - min + 1) <= 3)
	{
		sort_sA(A);
		return ;
	}
	A->len = max;
	count_B = sort_A_to_B(A, B, min, max);
	quick_sort_sp(A, B, min + count_B, max);
	sort_B_to_A(A, B, min, min + count_B + 1);
	quick_sort_sp(A, B, min, min + count_B + 1);
}
