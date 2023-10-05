/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:41:14 by joerober          #+#    #+#             */
/*   Updated: 2023/05/12 12:38:40 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	ft_error(void)
{
	perror("");
	exit(1);
	return (0);
}

void	e(int e)
{
	if (e == -1)
		ft_error();
}

void	m(char *m)
{
	if (!m)
		ft_error();
}

void	mm(char **mm)
{
	if (!mm)
		ft_error();
}
