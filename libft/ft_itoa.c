/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiroz <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:18:15 by shiroz            #+#    #+#             */
/*   Updated: 2023/05/13 13:13:27 by shiroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	f4(int a)
{
	int	b;

	b = 1;
	while (a > 0)
	{
		a--;
		b = b * 10;
	}
	return (b);
}

static int	f3(int n, int a, int b)
{
	while (b < a)
	{
		n = n / 10;
		b++;
	}
	return (n);
}

static void	f2(char *c, int a, int n)
{
	int	b;
	int	d;

	d = 0;
	b = 0;
	while (b <= a)
	{
		d = f3(n, a, b);
		c[b] = d + '0';
		n = n - f4(a - b) * d;
		b++;
	}
	c[b] = 0;
}

static int	size(int n)
{
	int	a;

	a = 1;
	if (n < 0)
		a++;
	while (n > 9 || n < -9)
	{
		a++;
		n = n / 10;
	}
	return (a);
}

char	*ft_itoa(int n)
{
	int		a;
	char	*c;

	a = size(n);
	c = malloc(sizeof(char) * (a + 1));
	if (!c)
		exit (1);
	if (n < 0)
		c[0] = '-';
	if (n == -2147483648)
	{
		c[0] = '-';
		c[1] = '2';
		f2(&c[2], a - 3, 147483648);
		return (c);
	}
	if (n >= 0)
		f2(c, a - 1, n);
	else
		f2(&c[1], a - 2, n * -1);
	return (c);
}
