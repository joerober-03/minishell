/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:57:33 by joerober          #+#    #+#             */
/*   Updated: 2023/05/12 16:07:28 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	here_gnl(char *limit, t_info *info)
{
	static char	*line_read;

	while (1)
	{
		line_read = readline("> ");
		if (strcmp_ms(limit, line_read) == 0)
		{
			free(line_read);
			exit(0);
		}
		if (line_read == NULL)
		{
			free(line_read);
			exit(0);
		}
		if (limit[0] == '\n' && line_read[0] == '\0')
		{
			free(line_read);
			exit(0);
		}
		ft_putstr_fd(line_read, info->here_tmp2);
		ft_putstr_fd("\n", info->here_tmp2);
		free(line_read);
	}
}

char	**here_new_args(char **args, int i, int j)
{
	char	**new_args;
	int		trigger;

	trigger = 0;
	while (args[i])
		i++;
	new_args = ft_calloc(sizeof(char *), i);
	mm(new_args);
	i = 0;
	while (args[i])
	{
		if (args[i][0] == '<' && trigger == 0)
		{
			if (args[i][1] == '<' && ++i != -1)
				trigger = 1;
			else
				new_args[j++] = args[i++];
		}
		else
			new_args[j++] = args[i++];
	}
	new_args[j] = 0;
	return (new_args);
}

void	here_doc(t_info *info, char *limit)
{
	pid_t	pid;

	g_struct->g_var = 2;
	pid = fork();
	e(pid);
	if (pid == 0)
	{
		info->here_tmp = open(ft_strjoin("/tmp/minishell_tmp_",
					ft_itoa(info->id)), O_WRONLY | O_CREAT | O_TRUNC, 0644);
		e(info->here_tmp);
		info->here_tmp2 = dup(info->here_tmp);
		here_gnl(limit, info);
		e(close(info->here_tmp2));
	}
	else
	{
		g_struct->child_pid = pid;
		e(waitpid(-1, &info->status, 0));
		e(dup2(g_struct->saved_out, STDOUT_FILENO));
	}
	info->after_doc = 1;
}
