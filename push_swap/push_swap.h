/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:02:44 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/23 12:47:49 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct s_ati
{
	int		i;
	int		j;
	long	num;
}			t_ati;

typedef struct s_stk
{
	int		*rank;
	int		*stk;
	int		len;
}			t_stk;

typedef struct s_res
{
	int		result[8000];
	int		place;
	int		min;
	int		max;

}			t_res;

typedef struct s_cnk
{
	int		size;
	int		num;
	int		min;
	int		max;
}			t_cnk;

typedef struct s_atb
{
	int		u_or_d;
	int		count;
	int		time;
	int		idx;
}			t_atb;

typedef struct s_bta
{
	int		count;
	int		max_num;
	int		j;
	int		u_or_d;
}			t_bta;

int			sa(t_stk *a, int mode, t_res *res);
int			sb(t_stk *b, int mode, t_res *res);
int			ss(t_stk *a, t_stk *b, t_res *res);
int			pa(t_stk *a, t_stk *b, t_res *res);
int			pb(t_stk *a, t_stk *b, t_res *res);
int			ra(t_stk *a, int mode, t_res *res);
int			rb(t_stk *b, int mode, t_res *res);
int			rr(t_stk *a, t_stk *b, t_res *res);
int			rra(t_stk *a, int mode, t_res *res);
int			rrb(t_stk *b, int mode, t_res *res);
int			rrr(t_stk *a, t_stk *b, t_res *res);
void		ft_quick_sort(int *stk, int min, int max);
void		get_sortstk_rank(t_stk *a, int argc);
int			ft_atoi_sp(char *str, int *error);
int			*get_stka(int argc, char **argv);
int			prepare(int argc, char **argv, t_stk *a, t_stk *b);
int			check_same(int *stk, int len);
void		sort_rank(t_stk *cpy, t_stk *a, int len);
void		slice_sort(t_stk *a, t_stk *b, t_res *res);
void		sort_a_to_b(t_stk *a, t_stk *b, t_cnk *cnk, t_res *res);
void		sort_b_to_a(t_stk *a, t_stk *b, int num, t_res *res);
void		check_rrr(int *r);
void		put_res(int *res);

#endif
