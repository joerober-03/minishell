/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiroz <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:18:15 by shiroz            #+#    #+#             */
/*   Updated: 2023/05/13 13:12:21 by shiroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	f1(char const *str, char c)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	if (str == 0)
		exit (1);
	while (str[a])
	{
		while (str[a] == c)
			a++;
		if (str[a] != 0)
			b++;
		while (str[a] && c != str[a])
			a++;
	}
	return (b);
}

char	**mfree(char **tab)
{
	int		a;

	a = 0;
	while (tab[a])
	{
		free(tab[a]);
		a++;
	}
	free(tab);
	return (0);
}

char	**f2(const char *s, char c, char **tab)
{
	size_t	a;
	size_t	b;
	size_t	d;

	d = 0;
	a = 0;
	while (s[a])
	{
		if (s[a] == c)
		{
			a++;
			continue ;
		}
		b = a;
		while (s[a] && s[a] != c)
			a++;
		tab[d] = ft_substr(&s[b], 0, a - b);
		if (!tab[d])
			return (mfree(tab));
		d++;
	}
	tab[d] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	tab = (char **) malloc(sizeof(char *) * (f1(s, c) + 1));
	if (!tab)
		exit (1);
	tab = f2(s, c, tab);
	return (tab);
}
