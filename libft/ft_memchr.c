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

void	*ft_memchr(const void *str, int c, size_t n)
{
	void	*ptr;

	ptr = 0;
	if (n == 0)
		return (ptr);
	if (n > 0)
		n--;
	while (n >= 0)
	{
		if (((unsigned char *)str)[n] == (unsigned char)c)
			ptr = (void *)(&str[n]);
		if (n == 0)
			break ;
		n--;
	}
	return (ptr);
}
