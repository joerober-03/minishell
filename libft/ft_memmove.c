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

void	*ft_memmove(void *str1, const void *str2, size_t n)
{
	size_t	a;

	a = 0;
	if (str2 == str1 || n == 0)
		return (str1);
	if (str1 > str2)
	{
		while (a < n)
		{
			((char *)str1)[n - a - 1] = ((char *)str2)[n - a - 1];
			a++;
		}
	}
	else
	{
		while (a < n)
		{
			((char *)str1)[a] = ((char *)str2)[a];
			a++;
		}
	}
	return (str1);
}
