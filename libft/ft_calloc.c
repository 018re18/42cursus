/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:36:32 by rookuma           #+#    #+#             */
/*   Updated: 2025/04/30 14:56:10 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mal;

	if (size != 0 && (nmemb * size) / size != nmemb)
	{
		return (NULL);
	}
	mal = (void *)malloc(nmemb * size);
	if (!(mal))
	{
		return (NULL);
	}
	ft_bzero(mal, nmemb * size);
	return (mal);
}
