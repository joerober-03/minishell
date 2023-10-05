/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:05:05 by joerober          #+#    #+#             */
/*   Updated: 2023/04/06 14:04:11 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	find_char(char **str, char c, t_info *info)
{
	int	i;
	int	j;

	if (!str || !c)
		return (-1);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == c && info->is_text[i] == 1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	find_char2(char *str, char c)
{
	int	i;

	if (!str || !c)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	find_char_place(char **str, char c)
{
	int	i;
	int	j;

	if (!str || !c)
		return (-1);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == c)
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}

int	strcmp_ms(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	strcmp_ms_caps(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (ft_tolower(s1[i]) == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((unsigned char)(ft_tolower(s1[i])) - (unsigned char)s2[i]);
}
