/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:00:08 by joerober          #+#    #+#             */
/*   Updated: 2023/05/12 14:35:25 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	export_short2(t_info *info, char **args, int i, int j)
{
	if (info->env[i])
	{
		free(info->env[i]);
		info->env[i] = ft_strdup(args[j]);
		info->status = 0;
	}
	else
	{
		i++;
		info->env = cpy_env(info->env, info, i, 1);
		info->env[i - 1] = ft_strdup(args[j]);
		info->env[i] = 0;
		info->status = 0;
	}
}

int	export_short1(t_info *info, char **args, int j, int i)
{
	char	*var;

	while (args[j] && args[j][i] != '=')
		i++;
	var = ft_calloc(sizeof(char), i + 10);
	m(var);
	i = 0;
	while (args[j] && args[j][i] != '=')
	{
		if (ft_end_var2(args[j][i]) == 0)
		{
			free(var);
			ft_printf("export: %s : not a valid identifier\n", args[j]);
			return (-1);
		}
		var[i] = args[j][i];
		i++;
	}
	var[i] = args[j][i];
	var[i + 1] = 0;
	i = 0;
	while (info->env[i] && ft_strncmp(var, info->env[i], ft_strlen(var)) != 0)
		i++;
	free(var);
	return (i);
}

void	export_args(t_info *info, char **args)
{
	int	j;
	int	i;

	j = 1;
	while (args[j])
	{
		if (args[j][0] == '_' || ft_isalpha(args[j][0]) == 1)
		{
			if (find_char2(args[j], '=') == 1)
			{
				i = export_short1(info, args, j, 0);
				if (i != -1)
					export_short2(info, args, i, j);
				else
					info->status = 1;
			}
		}
		else
		{
			ft_printf("export: '%s' : not a valid identifier\n", args[j]);
			info->status = 1;
		}
		j++;
	}
}

void	export_no_args(t_info *info)
{
	int		i;
	char	**export;

	i = 0;
	while (info->env[i])
		i++;
	export = sort_export(info, i, 0);
	i = -1;
	while (export[++i])
	{
		ft_printf("declare -x ");
		ft_putstr_fd_quotes(export[i], 1);
	}
	mfree(export);
}

void	ft_export(t_info *info, char **args)
{
	info->trigger = 0;
	if (!args[1])
		export_no_args(info);
	else
		export_args(info, args);
}
