/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:03:06 by joerober          #+#    #+#             */
/*   Updated: 2023/05/02 09:43:17 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	ft_execve(t_info *info, char **args, char *str, char **env)
{
	char	path[128];
	char	*path2;
	char	*exe;
	int		j;
	int		i;

	info->trigger = 0;
	m(getcwd(path, 128));
	i = 1;
	j = 2;
	exe = ft_calloc(sizeof(char), ft_strlen(str));
	m(exe);
	exe[0] = '/';
	while (str[j])
		exe[i++] = str[j++];
	exe[i] = 0;
	args[0] = exe;
	path2 = ft_strjoin(path, exe);
	execve(path2, args, env);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": cannot be executed\n", 2);
	free(exe);
	exit(126);
}

void	exec(char *cmd, char **env, t_info *info)
{
	char	**args;
	char	*path;
	int		i;

	(void) info;
	i = 0;
	args = ft_split(cmd, ' ');
	path = get_path(args[0], env);
	if (find_char2(args[0], '/') == 1)
	{
		execve(args[0], args, env);
	}
	else
	{
		execve(path, args, env);
	}
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

void	exec2(char **cmd, char **env)
{
	char	*path;

	if (cmd[0])
	{
		if (find_char2(cmd[0], '/') == 1)
		{
			execve(cmd[0], cmd, env);
		}
		else
		{
			path = get_path(cmd[0], env);
			execve(path, cmd, env);
		}
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	exit(0);
}
