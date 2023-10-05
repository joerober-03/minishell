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

static int	ft_number(int a, int b, int c, const char *str)
{
	while (str[a] >= '0' && str[a] <= '9')
	{
		c = c * 10 + (str[a] - 48) * b;
		a++;
	}
	return (c);
}

static int	ft_minus(int a, int b, int *d, const char *str)
{
	if (str[a + 1] == '+' || str[a + 1] == '-')
		return (a);
	if (str[a] == '-')
		b++;
	if (str[a] == '+' || str[a] == '-')
		a++;
	*d = b;
	return (a);
}

static int	ft_space(int a, const char *str)
{
	while ((str[a] >= 9 && str[a] <= 13) || str[a] == ' ')
	{
		a++ ;
	}
	return (a);
}

int	ft_atoi(const char *str)
{
	int	a;
	int	b;
	int	c;
	int	*d;

	a = 0;
	c = 0;
	d = &b;
	b = 0;
	a = ft_space(a, str);
	a = ft_minus(a, b, d, str);
	b = 1 - 2 * (b % 2);
	return (ft_number(a, b, c, str));
}
