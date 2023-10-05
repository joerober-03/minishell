/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiroz <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:18:15 by shiroz            #+#    #+#             */
/*   Updated: 2023/05/13 13:10:02 by shiroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*f2(void)
{
	char	*c;

	c = malloc(sizeof(char));
	if (!c)
		exit (1);
	c[0] = 0;
	return (c);
}

static char	*f1(char const *s, unsigned int start, size_t len, char *c)
{
	int	a;

	a = 0;
	while (s[start] && len >= 0)
	{
		c[a] = s[start];
		if (len == 0)
			break ;
		len--;
		start++;
		a++;
	}
	c[a] = 0;
	return (c);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*c;
	size_t	a;

	a = ft_strlen(s);
	if (len == 0 || start >= a)
		return (f2());
	if (a < len)
		len = a;
	if ((a - start + 1) > (len + 1))
		c = malloc(sizeof(char) * (len + 1));
	else
		c = malloc(sizeof(char) * (a - start + 1));
	if (!c)
		exit (1);
	return (f1(s, start, len, c));
}
