/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:39:04 by joerober          #+#    #+#             */
/*   Updated: 2023/05/12 12:42:40 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	ft_shlvl(t_info *info, int i, int j)
{
	int		num;
	char	*tmp;
	char	*new_shlvl;

	while (info->env[i] && ft_strncmp("SHLVL=", info->env[i], 6) != 0)
		i++;
	if (info->env[i])
	{
		while (info->env[i][j] != '=')
			j++;
		num = ft_atoi(&info->env[i][j + 1]);
		num++;
		tmp = ft_itoa(num);
		new_shlvl = ft_strjoin("SHLVL=", tmp);
		free(info->env[i]);
		info->env[i] = ft_strdup(new_shlvl);
		free(new_shlvl);
		free(tmp);
	}
	else if (i++ != -1)
	{
		info->env = cpy_env(info->env, info, i, 1);
		info->env[i - 1] = ft_strdup("SHLVL=1");
		info->env[i] = 0;
	}
}

void	ctrl_d_exit(t_info *info, char *line_read)
{
	e(tcsetattr(STDIN_FILENO, TCSANOW, &info->termios_save));
	e(write(1, "exit\n", 5));
	mfree(info->env);
	free(line_read);
	free(g_struct);
	exit(0);
}

void	loop_prep(t_info *info, int argc, char **argv)
{
	(void) argc;
	(void) argv;
	info->is_text_id = 0;
	signal(SIGQUIT, SIG_IGN);
	g_struct->tmp_len = 0;
	info->trigger = 1;
	if (g_struct->after_sig == 1)
		info->status = g_struct->status;
}

void	ft_initiate(t_info *info, char **env, int i)
{
	char	**args;

	g_struct = (t_info *)ft_calloc(sizeof(t_info), 1);
	if (!g_struct)
		ft_error();
	g_struct->g_var = 0;
	info->status = 0;
	info->after_doc = 0;
	info->after_chevron = 0;
	info->after_pipe = 0;
	g_struct->after_sig = 0;
	info->saved_out = dup(STDOUT_FILENO);
	g_struct->saved_out = dup(STDOUT_FILENO);
	info->saved_in = dup(STDIN_FILENO);
	if (info->saved_out == -1 || info->saved_in == -1
		|| g_struct->saved_out == -1)
		ft_error();
	while (env && env[i])
		i++;
	info->env = cpy_env(env, info, i, 0);
	args = ft_split("unset _", ' ');
	ft_unset(info, args, -1, 0);
	ft_shlvl(info, 0, 0);
	mfree(args);
	ft_hide(info);
}

int	main(int argc, char **argv, char **env)
{
	t_info		info;
	static char	*line_read;

	ft_initiate(&info, env, 0);
	while (1)
	{
		loop_prep(&info, argc, argv);
		line_read = readline("minishell> ");
		info.prompt = line_read;
		ft_lexer(&info);
		g_struct->after_sig = 0;
		if (line_read && *line_read)
			add_history(line_read);
		if (line_read == NULL)
			ctrl_d_exit(&info, line_read);
		if (info.tab_cmd != NULL)
		{
			if (*info.tab_cmd)
				ft_parsing(info.tab_cmd, info.env, &info);
			free(line_read);
			mfree(info.tab_cmd);
			free(info.is_text);
		}
	}
	return (0);
}
