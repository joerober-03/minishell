/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_research_of_square.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiroz <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:18:15 by shiroz            #+#    #+#             */
/*   Updated: 2022/08/03 19:40:39 by shiroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	a;
	size_t	b;
	size_t	c;

	b = ft_strlen(dst);
	c = b;
	if (b > size)
		return (ft_strlen(src) + size);
	if (b + 1 < size)
	{
		a = 0;
		while (src[a] && b != (size - 1))
		{
			dst[b] = src[a];
			b++;
			a++;
		}
		dst[b] = 0;
	}
	return (ft_strlen(src) + c);
}
