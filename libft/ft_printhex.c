/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:57:13 by joerober          #+#    #+#             */
/*   Updated: 2022/11/02 11:09:19 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_hex_len(unsigned int n)
{
	unsigned int	len;

	len = 0;
	while (n != 0)
	{
		len ++;
		n = n / 16;
	}
	return (len);
}

void	ft_puthex(unsigned int num, char format)
{
	if (num >= 16)
	{
		ft_puthex(num / 16, format);
		ft_puthex(num % 16, format);
	}
	else
	{	
		if (num <= 9)
			ft_printchar(num + '0');
		else
		{
			if (format == 'x')
				ft_printchar(num - 10 + 'a');
			else
				ft_printchar(num - 10 + 'A');
		}
	}
}

int	ft_printhex(unsigned int num, char format)
{
	unsigned int	len;

	len = get_hex_len(num);
	if (num == 0)
		return (write(1, "0", 1));
	else
		ft_puthex(num, format);
	return (len);
}
