/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:42:18 by joerober          #+#    #+#             */
/*   Updated: 2023/05/12 12:50:27 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*path;
	char	*dir;
	char	*bin;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (0);
	path = env[i] + 5;
	while (path && chr_len(path, ':') > -1)
	{
		dir = strn_dup(path, chr_len(path, ':'));
		bin = link_path(dir, cmd);
		free(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		free (bin);
		path += chr_len(path, ':') + 1;
	}
	return (0);
}

void	ft_pipe(t_info *info, char **args, int num, char **env)
{
	pid_t	pid;
	char	**tmp;

	tmp = ft_chevron(info, &args[num], env, 1);
	if (tmp == NULL)
		exit(info->status);
	e(pipe(info->pipefd));
	pid = fork();
	e(pid);
	if (pid == 0)
	{
		e(close(info->pipefd[0]));
		if (info->after_chevron == 0)
			e(dup2(info->pipefd[1], 1));
		built_ins_pipe(tmp, info, env);
		exec2(tmp, env);
	}
	else
	{
		e(close(info->pipefd[1]));
		e(dup2(info->pipefd[0], 0));
	}
	free(tmp);
}

int	pipe_loop(t_info *info, char **args, char **env, int saved_in)
{
	int	i;
	int	num;
	int	pnum;

	pnum = info->pipe_num;
	i = 0;
	num = 0;
	while (num + 1 < pnum)
	{
		info->id = num;
		ft_pipe(info, args, i, env);
		num++;
		while (args[i] != 0)
			i++;
		i++;
		if (num + 1 < pnum)
			e(close(info->pipefd[0]));
		e(dup2(info->saved_out, STDOUT_FILENO));
		e(dup2(saved_in, STDIN_FILENO));
	}
	info->id = num;
	return (i);
}

void	last_fork(t_info *info, char **args, char **env, int i)
{
	pid_t	pid;
	char	**tmp;

	pid = fork();
	e(pid);
	if (pid == 0)
	{
		tmp = ft_chevron(info, &args[i], env, 1);
		if (tmp == NULL)
			exit(info->status);
		if (info->after_doc == 0 && info->after_infile == 0)
			e(dup2(info->pipefd[0], 0));
		built_ins_pipe(tmp, info, env);
		exec2(tmp, env);
	}
	else
		e(close(info->pipefd[0]));
}

void	pipe_init(t_info *info, char **env, char **args)
{
	int		i;
	int		saved_in;

	saved_in = 0;
	args = remove_pipes(info, args);
	i = pipe_loop(info, args, env, saved_in);
	last_fork(info, args, env, i);
	e(close(saved_in));
	while (waitpid(-1, &info->status, 0) > 0)
		;
	if (info->status)
		exit(WEXITSTATUS(info->status));
	exit(0);
}
