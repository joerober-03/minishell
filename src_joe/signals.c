/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:42:50 by joerober          #+#    #+#             */
/*   Updated: 2023/05/12 12:52:13 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	ft_signals(void)
{
	if (g_struct->g_var == 2)
	{
		e(kill(g_struct->child_pid, SIGTERM));
		g_struct->g_var = 5;
		clear_tmp_files();
		e(write(1, "\n", 1));
		g_struct->status = 1;
	}
	else if (g_struct->g_var == 3)
	{
		exit(1);
		rl_replace_line("", 0);
		rl_on_new_line();
		g_struct->g_var = 0;
		g_struct->status = 130;
	}
	else if (g_struct->g_var == 4)
	{
		g_struct->status = 1;
	}
	else if (g_struct->g_var == 6)
	{
		e(write(1, "\n", 1));
		g_struct->status = 130;
	}
}

void	handler_c(int num)
{
	(void) num;
	if (g_struct->g_var == 0)
	{
		e(write(1, "\n", 1));
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_struct->status = 1;
	}
	else if (g_struct->g_var == 1)
	{
		e(write(1, "\n", 1));
		rl_replace_line("", 0);
		rl_on_new_line();
		g_struct->g_var = 0;
		g_struct->status = 130;
	}
	else
		ft_signals();
	g_struct->after_sig = 1;
}

void	handler_bs(int num)
{
	(void) num;
	if (g_struct->g_var == 1)
	{
		e(write(2, "Quit: 3\n", 8));
		rl_replace_line("", 0);
		rl_on_new_line();
		g_struct->status = 131;
	}
	else if (g_struct->g_var == 3)
	{
		exit(1);
		e(write(2, "Quit: 3\n", 8));
		rl_replace_line("", 0);
		rl_on_new_line();
		g_struct->status = 131;
	}
	else if (g_struct->g_var == 4)
		g_struct->status = 1;
	else if (g_struct->g_var == 6)
	{
		g_struct->status = 131;
		e(write(2, "Quit: 3\n", 8));
	}
	g_struct->g_var = 0;
	g_struct->after_sig = 1;
}

void	ft_ctrlc(int n, t_info *info)
{
	struct termios	attributes;

	if (n == 0)
	{
		if (tcgetattr(STDIN_FILENO, &attributes) == -1)
			ft_error();
		attributes.c_lflag &= ~(ECHOCTL);
		if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes) == -1)
			ft_error();
	}
	else if (n == 1)
	{
		if (tcsetattr(STDIN_FILENO, TCSANOW, &info->termios_save) == -1)
			ft_error();
	}
}

void	clear_tmp_files(void)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = g_struct->tmp_len;
	while (g_struct->tmp_len > 0)
	{
		tmp = ft_itoa(g_struct->tmp_ids[g_struct->tmp_len - 1]);
		tmp2 = ft_strjoin("/tmp/minishell_tmp_", tmp);
		unlink(tmp2);
		g_struct->tmp_len--;
		free(tmp);
		free(tmp2);
	}
	g_struct->tmp_len = i;
	while (g_struct->tmp_len > 0)
	{
		g_struct->tmp_ids[g_struct->tmp_len--] = '\0';
	}
	if (g_struct->tmp_len > 0)
		free(g_struct->tmp_ids);
}
