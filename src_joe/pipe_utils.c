/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:44:09 by joerober          #+#    #+#             */
/*   Updated: 2023/05/12 12:51:39 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

char	*strn_dup(char *str, int n)
{
	int		i;
	char	*substr;

	i = 0;
	substr = ft_calloc((n + 1), sizeof(char));
	m(substr);
	while (i < n)
	{
		substr[i] = str[i];
		i++;
	}
	substr[n] = '\0';
	return (substr);
}

void	built_ins_pipe2(char **args, t_info *info, char **env)
{
	if (strcmp_ms(args[0], "exit") == 0)
	{
		ft_exit(info, args, 1);
		exit(info->status);
	}
	if (strcmp_ms(args[0], "export") == 0)
	{
		ft_export(info, args);
		exit(info->status);
	}
	if (strcmp_ms(args[0], "unset") == 0)
	{
		ft_unset(info, args, -1, 0);
		exit(info->status);
	}
	if (strcmp_ms_caps(args[0], "cd") == 0)
	{
		ft_cd(info, args, env);
		exit(info->status);
	}
}

void	built_ins_pipe(char **args, t_info *info, char **env)
{
	if (strcmp_ms_caps(args[0], "echo") == 0)
		ft_echo(args, info);
	if (strcmp_ms_caps(args[0], "env") == 0)
		ft_env(info);
	if (strcmp_ms_caps(args[0], "pwd") == 0)
		ft_pwd(info);
	built_ins_pipe2(args, info, env);
}

char	**remove_pipes(t_info *info, char **args)
{
	int	i;

	info->trigger = 0;
	info->after_pipe = 1;
	g_struct->g_var = 3;
	info->pipe_num = 1;
	i = 0;
	while (args[i])
	{
		if (args[i][0] == '|' && info->is_text[i] == 1)
		{
			info->pipe_num++;
			args[i] = 0;
		}
		i++;
	}
	return (args);
}

char	*link_path(char *dir, char *cmd)
{
	char	*path;
	int		i;
	int		j;

	path = ft_calloc(sizeof(char), (ft_strlen(dir) + ft_strlen(cmd) + 10));
	m(path);
	i = 0;
	j = 0;
	while (dir[j] != '\0')
		path[i++] = dir[j++];
	path[i] = '/';
	i++;
	j = 0;
	while (cmd[j] != '\0')
		path[i++] = cmd[j++];
	path[i] = '\0';
	return (path);
}
