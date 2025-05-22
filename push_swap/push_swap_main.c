/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:04:16 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/22 21:13:33 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	*ft_memset(int *s, int c, size_t n)
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

int	prepare(int argc, char **argv, t_stk *A, t_stk *B)
{
	A->stk = get_stkA(argc, argv);
	B->stk = (int *)malloc(sizeof(int) * (argc - 1));
	if (!A->stk || !B->stk)
	{
		free_all(A, B);
		write(2, "Error\n", 6);
		return (-1);
	}
	A->len = argc - 1;
	B->len = 0;
	A->rank = NULL;
	B->rank = NULL;
	get_sortstk_rank(A, argc);
	B->rank = (int *)malloc(sizeof(int) * (argc - 1));
	if (!A->rank || !B->rank)
	{
		free_all(A, B);
		write(2, "Error\n", 6);
		return (-1);
	}
	return (1);
}
int	main(int argc, char **argv)
{
	t_stk	A;
	t_stk	B;
	t_res	res;
	int		pre;

	if (argc <= 1)
		return (0);
	pre = prepare(argc, argv, &A, &B);
	if (pre < 0)
		return (-1);
	res.place = 0;
	ft_memset(res.result, 0, 8000);
	res.min = 0;
	res.max = argc - 2;
	slice_sort(&A, &B, &res);
	check_rrr(res.result);
	put_res(res.result);
	free_all(&A, &B);
	return (0);
}
