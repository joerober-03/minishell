/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:03:38 by joerober          #+#    #+#             */
/*   Updated: 2023/05/12 14:10:40 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	echo_write(char **args, int i)
{
	int	j;

	while (args[i])
	{
		j = -1;
		while (args[i][++j])
			e(write(1, &args[i][j], 1));
		e(args[i + 1] && write(1, " ", 1));
		i++;
	}
}

void	echo_parse(char **args, int isn, int i, int trigger)
{
	if (ft_strncmp(args[1], "-n", 2) == 0)
	{
		i = 1;
		while (args[1][++i])
		{
			if (args[1][i] != 'n')
				trigger++;
		}
		i = 1;
		if (trigger == 0)
		{
			isn = 1;
			i = 2;
		}
	}
	if (isn == 1 && !args[2])
		exit(0);
	echo_write(args, i);
	if (isn == 0)
		e(write(1, "\n", 1));
}

void	ft_echo(char **args, t_info *info)
{
	int		isn;
	int		i;
	int		trigger;

	trigger = 0;
	info->trigger = 0;
	isn = 0;
	i = 1;
	if (!args[1])
	{
		e(write(1, "\n", 1));
		exit(0);
	}
	echo_parse(args, isn, i, trigger);
	exit(0);
}

void	unset_short(t_info *info, char **args, int j)
{
	int		i;
	char	*str2;

	i = -1;
	str2 = ft_strjoin(args[j], "=");
	while (info->env[++i])
	{
		if (ft_strncmp(str2, info->env[i], ft_strlen(str2)) == 0)
		{
			free(info->env[i]);
			while (info->env[i - 1])
			{
				info->env[i] = info->env[i + 1];
				i++;
			}
			info->env[i] = 0;
			break ;
		}
	}
	free(str2);
}

void	ft_unset(t_info *info, char **args, int i, int j)
{
	int		trigger;

	info->trigger = 0;
	while (args[++j])
	{
		i = -1;
		trigger = 0;
		while (args[j][++i])
		{
			if (ft_end_var2(args[j][i]) == 0)
				trigger++;
		}
		if ((args[j][0] == '_' || ft_isalpha(args[j][0]) == 1) && trigger == 0)
			unset_short(info, args, j);
		else
		{
			ft_printf("unset: '%s': not a valid identifier\n", args[j]);
			info->status = 1;
		}
	}
}
