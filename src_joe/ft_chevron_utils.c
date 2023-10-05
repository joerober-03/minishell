/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chevron_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:44:24 by joerober          #+#    #+#             */
/*   Updated: 2023/05/13 12:44:26 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	chevron_init(t_chev *chev, t_info *info, char **args, int isfork)
{
	info->trigger = 0;
	info->after_chevron = 0;
	info->after_doc = 0;
	info->after_infile = 0;
	chev->i = 0;
	chev->len = 0;
	chev->infile = 0;
	chev->outfile = 1;
	chev->trigger = 2;
	chev->isfork = isfork;
	chev->index = info->is_text_id;
	while (args[chev->len])
		chev->len++;
	chev->len++;
}

char	**chevron_new_args(t_info *info, char **args, t_chev *chev, int i)
{
	chev->new_args = ft_calloc(chev->len + 10, sizeof(char *));
	mm(chev->new_args);
	chev->len = 0;
	while (args[++i] != 0)
	{
		if (i == 0)
		{
			if (info->is_text[chev->index] != 1)
				chev->new_args[(chev->len)++] = args[i];
		}
		else
		{
			if (args[i - 1][0] == '<' && args[i - 1][1] == '<'
				&& info->is_text[chev->index - 1] == 1
				&& info->is_text[chev->index] == 0)
				chev->new_args[(chev->len)++] = args[i];
			else if (info->is_text[chev->index] == 0
				&& info->is_text[chev->index - 1] != 1)
				chev->new_args[(chev->len)++] = args[i];
		}
		(chev->index)++;
	}
	chev->new_args[chev->len] = 0;
	return (chev->new_args);
}

int	built_ins_chevron_half(char **args, t_info *info, char **env)
{
	if (strcmp_ms(args[0], "exit") == 0)
	{
		e(dup2(info->saved_out, STDOUT_FILENO));
		ft_exit(info, args, 0);
		return (1);
	}
	if (strcmp_ms(args[0], "export") == 0)
	{
		ft_export(info, args);
		return (1);
	}
	if (strcmp_ms(args[0], "unset") == 0)
	{
		ft_unset(info, args, -1, 0);
		return (1);
	}
	if (strcmp_ms_caps(args[0], "cd") == 0)
	{
		ft_cd(info, args, env);
		return (1);
	}
	return (0);
}

int	built_ins_chevron(char **args, t_info *info, char **env)
{
	if (built_ins_chevron_half(args, info, env) == 1)
		return (1);
	if (strcmp_ms_caps(args[0], "echo") == 0)
		ft_echo(args, info);
	if (strcmp_ms_caps(args[0], "env") == 0)
		ft_env(info);
	if (strcmp_ms_caps(args[0], "pwd") == 0)
		ft_pwd(info);
	return (0);
}

void	chevron_exec(t_info *info, char **new_args, char **env)
{
	if (info->after_pipe == 0)
	{
		if (built_ins_chevron(new_args, info, env) == 0)
		{
			if (g_struct->tmp_len > 0)
				free(g_struct->tmp_ids);
			if (!new_args[0])
				exit(0);
			else
				exec2(new_args, env);
		}
		else
		{
			e(dup2(info->saved_in, STDIN_FILENO));
			e(dup2(info->saved_out, STDOUT_FILENO));
		}
	}
}
