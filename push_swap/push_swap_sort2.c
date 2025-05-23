/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:17:17 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/23 12:37:56 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_same(int *stk, int len)
{
	int	i;

	i = 0;
	while (i < len - 1)
	{
		if (stk[i] == stk[i + 1])
			return (1);
		i++;
	}
	return (0);
}

void	sort_rank(t_stk *cpy, t_stk *a, int len)
{
	int	i;
	int	j;

	a->rank = (int *)malloc(sizeof(int) * len);
	if (!a->rank)
		return ;
	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len)
		{
			if (a->stk[i] == cpy->stk[j])
			{
				a->rank[i] = j;
				break ;
			}
			j++;
		}
		i++;
	}
}
