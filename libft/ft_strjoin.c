/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiroz <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:18:15 by shiroz            #+#    #+#             */
/*   Updated: 2023/05/13 13:10:23 by shiroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	a;
	size_t	b;
	char	*c;

	c = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!c)
		exit(1);
	a = 0;
	b = 0;
	while (s1[a])
	{
		c[a] = s1[a];
		a++;
	}
	while (s2[b])
	{
		c[a] = s2[b];
		b++;
		a++;
	}
	c[a] = 0;
	return (c);
}
