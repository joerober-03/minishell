/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:45:05 by joerober          #+#    #+#             */
/*   Updated: 2023/05/13 12:45:07 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	chr_len(char *path, char c)
{
	int	i;

	i = 0;
	while (path[i] != '\0' && path[i] != c)
		i++;
	if (path[i] == c)
		return (i);
	return (-1);
}

void	ft_hide(t_info *info)
{
	struct termios	attributes;

	tcgetattr(STDIN_FILENO, &info->termios_save);
	if (tcgetattr(STDIN_FILENO, &attributes) == -1)
		ft_error();
	attributes.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes) == -1)
		ft_error();
	signal(SIGINT, handler_c);
}
