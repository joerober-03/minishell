/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:01:59 by joerober          #+#    #+#             */
/*   Updated: 2022/11/02 11:08:42 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	get_len_2(int n)
{
	size_t	i;

	i = 1;
	if (n < 0)
		i++;
	n = n / 10;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

void	ft_putchar(int c)
{
	write(1, &c, 1);
}

int	ft_printnbr(int n)
{
	int			len;
	long int	nb;

	nb = n;
	len = get_len_2(n);
	if (nb <= 2147483647 && nb >= -2147483648)
	{
		if (nb == -2147483648)
			write(1, "-2147483648", 11);
		else if (nb < 0)
		{
			ft_putchar('-');
			ft_printnbr(-nb);
		}
		else if (nb > 9)
		{
			ft_printnbr(nb / 10);
			ft_printnbr(nb % 10);
		}
		else
			ft_putchar(nb + '0');
	}
	return (len);
}
