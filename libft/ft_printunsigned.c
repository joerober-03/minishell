/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:41:56 by joerober          #+#    #+#             */
/*   Updated: 2022/11/02 11:09:02 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	get_len2(unsigned int n)
{
	size_t	i;

	i = 1;
	n = n / 10;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

void	ft_putchar2(int c)
{
	write(1, &c, 1);
}

int	ft_printunsigned(unsigned int i)
{
	int				len;

	len = get_len2(i);
	if (i <= 4294967295 && i >= 0)
	{
		if (i > 9)
		{
			ft_printnbr(i / 10);
			ft_printnbr(i % 10);
		}
		else
			ft_putchar2(i + '0');
	}
	return (len);
}
