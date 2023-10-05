/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:40:10 by joerober          #+#    #+#             */
/*   Updated: 2022/11/02 11:09:32 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_hex_len2(unsigned long long n)
{
	unsigned int	len;

	len = 2;
	while (n != 0)
	{
		len ++;
		n = n / 16;
	}
	return (len);
}

void	ft_puthex2(unsigned long long num)
{
	if (num >= 16)
	{
		ft_puthex2(num / 16);
		ft_puthex2(num % 16);
	}
	else
	{	
		if (num <= 9)
			ft_printchar(num + '0');
		else
			ft_printchar(num - 10 + 'a');
	}
}

int	ft_printptr(unsigned long long ptr)
{
	unsigned int	len;

	len = get_hex_len2(ptr);
	write (1, "0x", 2);
	if (ptr == 0)
	{
		write (1, "0", 1);
		len++;
	}
	else
		ft_puthex2(ptr);
	return (len);
}
