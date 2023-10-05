/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:44:11 by joerober          #+#    #+#             */
/*   Updated: 2023/05/13 12:44:13 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cd_home(t_info *info, int i, char *tmp, char *pwd)
{
	e(chdir(tmp));
	while (info->env[i] && ft_strncmp(info->env[i], "OLDPWD=", 7) != 0)
		i++;
	if (info->env[i])
	{
		free(info->env[i]);
		info->env[i] = ft_strjoin("OLDPWD=", pwd);
	}
	i = 0;
	while (info->env[i] && ft_strncmp(info->env[i], "PWD=", 4) != 0)
		i++;
	if (info->env[i])
	{
		m(getcwd(pwd, 128));
		free(info->env[i]);
		info->env[i] = ft_strjoin("PWD=", pwd);
	}
	info->status = 0;
}

void	cd_normal(t_info *info, int i, char *path, char *pwd)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: no such file or directory\n", 2);
		info->status = 1;
	}
	else
	{
		while (info->env[i] && ft_strncmp(info->env[i], "OLDPWD=", 7) != 0)
			i++;
		if (info->env[i])
		{
			free(info->env[i]);
			info->env[i] = ft_strjoin("OLDPWD=", pwd);
		}
		i = 0;
		while (info->env[i] && ft_strncmp(info->env[i], "PWD=", 4) != 0)
			i++;
		if (info->env[i])
		{
			m(getcwd(pwd, 128));
			free(info->env[i]);
			info->env[i] = ft_strjoin("PWD=", pwd);
		}
		info->status = 0;
	}
}

void	cd_oldpwd(t_info *info, int i, char *tmp, char *pwd)
{
	e(chdir(tmp));
	ft_printf("%s\n", tmp);
	i = 0;
	while (info->env[i] && ft_strncmp(info->env[i], "OLDPWD=", 7) != 0)
		i++;
	if (info->env[i])
	{
		free(info->env[i]);
		info->env[i] = ft_strjoin("OLDPWD=", pwd);
	}
	i = 0;
	while (info->env[i] && ft_strncmp(info->env[i], "PWD=", 4) != 0)
		i++;
	if (info->env[i])
	{
		m(getcwd(pwd, 128));
		free(info->env[i]);
		info->env[i] = ft_strjoin("PWD=", pwd);
	}
	info->status = 0;
}

void	ft_cd2(t_info *info, char **args, char *pwd)
{
	int		i;
	char	*tmp;

	i = 0;
	if (args[1] && args[1][0] == '-')
	{
		while (info->env[i] && ft_strncmp(info->env[i], "OLDPWD=", 7) != 0)
			i++;
		if (!info->env[i])
		{
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
			info->status = 1;
		}
		else
		{
			tmp = &info->env[i][7];
			cd_oldpwd(info, i, tmp, pwd);
		}
	}
	else if (args[1])
		cd_normal(info, 0, args[1], pwd);
}

void	ft_cd(t_info *info, char **args, char **env)
{
	char	*tmp;
	char	pwd[128];
	int		i;

	(void) env;
	i = 0;
	m(getcwd(pwd, 128));
	info->trigger = 0;
	if (args[1] == NULL)
	{
		while (info->env[i] && ft_strncmp(info->env[i], "HOME=", 5) != 0)
			i++;
		if (!info->env[i])
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			info->status = 1;
		}
		else
		{
			tmp = &info->env[i][5];
			cd_home(info, 0, tmp, pwd);
		}
	}
	else
		ft_cd2(info, args, pwd);
}
