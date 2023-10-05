/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiroz <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:18:15 by shiroz            #+#    #+#             */
/*   Updated: 2023/05/13 13:11:18 by shiroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*f1(char *c, int d)
{
	c[d] = 0;
	return (c);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		a;
	int		b;
	char	*c;
	int		d;

	a = 0;
	d = 0;
	b = (ft_strlen(s1));
	while (s1[a] && 0 != ft_strchr(set, s1[a]))
		a++;
	while (a < b && ft_strrchr(set, s1[b - 1]))
		b--;
	c = (char *)malloc(sizeof(char) * (b - a + 1));
	if (!c)
		exit (1);
	while (b > a)
	{
		c[d] = s1[a];
		a++;
		d++;
	}
	return (f1(c, d));
}
