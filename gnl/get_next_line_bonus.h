/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:37:20 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/05 14:34:37 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_gnl
{
	char	*str;
	char	*line;
	char	*tmp;
}			t_gnl;

typedef struct s_line
{
	size_t	ln_len;
	size_t	str_len;
	char	*line;
}			t_line;

typedef struct s_join
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str;
}			t_join;

char		*get_next_line(int fd);
size_t		ft_strlen_c_n(char *s, int num);
char		*ft_strjoin_free(char *s1, char *s2);
char		*rd_1t(int fd, int *remain);
char		*rtn_line(char *str, int num);

#endif
