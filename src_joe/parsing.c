/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:01:00 by joerober          #+#    #+#             */
/*   Updated: 2023/05/12 12:48:50 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	built_ins_no_pid(char **args, char **env, t_info *info)
{
	if (info->trigger && strcmp_ms(args[0], "exit") == 0)
	{
		ft_exit(info, args, 0);
	}
	if (info->trigger && strcmp_ms(args[0], "export") == 0)
		ft_export(info, args);
	if (info->trigger && strcmp_ms(args[0], "unset") == 0)
		ft_unset(info, args, -1, 0);
	if (info->trigger && strcmp_ms_caps(args[0], "cd") == 0)
	{
		if (strcmp_ms(args[0], "cd") == 0)
			ft_cd(info, args, env);
		info->trigger = 0;
	}
}

void	built_ins_yes_pid(char **args, char **env, t_info *info)
{
	if (info->trigger && args[0][0] == '.' && args[0][1] == '/')
	{
		g_struct->g_var = 4;
		ft_execve(info, args, args[0], env);
	}
	if (info->trigger && strcmp_ms_caps(args[0], "echo") == 0)
	{
		ft_echo(args, info);
	}
	if (info->trigger && strcmp_ms_caps(args[0], "env") == 0)
	{
		ft_env(info);
	}
	if (info->trigger && strcmp_ms_caps(args[0], "pwd") == 0)
	{
		ft_pwd(info);
	}
	if (info->trigger)
	{
		exec2(args, env);
	}
}

void	pipe_chevron_exec(char **args, char **env, t_info *info)
{
	if (info->trigger)
	{
		if (info->trigger == 1 && find_char(args, '|', info) == 1)
		{
			pipe_init(info, env, args);
		}
		else if (info->trigger == 1 && (find_char(args, '<', info) == 1
				|| find_char(args, '>', info) == 1))
			ft_chevron(info, args, env, 0);
		else
			exit(0);
	}
}

void	parsing_short(t_info *info, char **args, char **env)
{
	pid_t	pid;

	g_struct->g_var = 1;
	signal(SIGQUIT, handler_bs);
	if ((find_char(args, '<', info) == 1 || find_char(args, '>', info) == 1)
		&& (strcmp_ms(args[0], "exit") == 0
			|| strcmp_ms(args[0], "export") == 0
			|| strcmp_ms(args[0], "unset") == 0
			|| strcmp_ms_caps(args[0], "cd") == 0)
		&& find_char(args, '|', info) == 0)
		ft_chevron(info, args, env, 1);
	else if (find_char(args, '|', info) == 1
		|| find_char(args, '<', info) == 1
		|| find_char(args, '>', info) == 1)
	{
		pid = fork();
		e(pid);
		if (pid == 0)
			pipe_chevron_exec(args, env, info);
		else
			waitpid(-1, &info->status, 0);
		info->trigger = 0;
	}
}

void	ft_parsing(char **args, char **env, t_info *info)
{
	pid_t	pid;

	g_struct->g_var = 2;
	tmp_heredoc(info, args, -1, 0);
	ft_ctrlc(1, info);
	if (g_struct->g_var != 5)
	{
		parsing_short(info, args, env);
		built_ins_no_pid(args, env, info);
		if (info->trigger == 1)
		{
			g_struct->g_var = 6;
			if (strcmp_ms("./minishell", args[0]) == 0)
				g_struct->g_var = 4;
			pid = fork();
			e(pid);
			if (pid == 0)
				built_ins_yes_pid(args, env, info);
			else
			{
				e(waitpid(-1, &info->status, 0));
			}
		}
	}
	parsing_end(info);
}
