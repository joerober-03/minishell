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

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	a;
	size_t	b;

	b = 0;
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	a = ft_strlen(needle);
	while (haystack[b] && a <= len)
	{
		if (ft_strncmp(&haystack[b], needle, a) == 0
			&& haystack[b] == needle[0])
			return (&((char *)haystack)[b]);
		b++;
		len--;
	}
	return (0);
}
