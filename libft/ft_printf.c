/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:52:43 by joerober          #+#    #+#             */
/*   Updated: 2022/11/02 11:07:37 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_convertions(va_list args, const char format)
{
	int	print_lenght;

	print_lenght = 0;
	if (format == 'c')
		print_lenght += ft_printchar(va_arg(args, int));
	else if (format == 's')
		print_lenght += ft_printstr(va_arg(args, char *));
	else if (format == 'i' || format == 'd')
		print_lenght += ft_printnbr(va_arg(args, int));
	else if (format == 'u')
		print_lenght += ft_printunsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		print_lenght += ft_printhex(va_arg(args, unsigned int), format);
	else if (format == 'p')
		print_lenght += ft_printptr(va_arg(args, unsigned long long));
	else if (format == '%')
		print_lenght += ft_printpercent();
	return (print_lenght);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		print_lenght;
	va_list	args;

	i = 0;
	print_lenght = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			print_lenght += ft_convertions(args, format[i + 1]);
			i++;
		}
		else
			print_lenght += ft_printchar(format[i]);
		i++;
	}
	va_end(args);
	return (print_lenght);
}
