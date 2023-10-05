/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:04:26 by joerober          #+#    #+#             */
/*   Updated: 2023/04/14 15:25:59 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	ft_putstr_fd_quotes(char *s, int fd)
{
	int	a;

	a = 0;
	while (s[a])
	{
		if (a > 0)
		{
			if (s[a - 1] == '=')
				e(write(fd, "\"", 1));
		}
		e(write(fd, &s[a], 1));
		a++;
	}
	e(write(fd, "\"", 1));
	e(write(fd, "\n", 1));
}

char	*ft_strjoin_space(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*mem;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	mem = (char *)ft_calloc(sizeof(*s1), (ft_strlen(s1) + (ft_strlen(s2)) + 2));
	m(mem);
	while (s1[j])
	{
		mem[i++] = s1[j];
		j++;
	}
	mem[i++] = ' ';
	j = 0;
	while (s2[j])
	{
		mem[i++] = s2[j];
		j++;
	}
	mem[i] = '\0';
	return (mem);
}

int	ft_end_var2(char c)
{
	int	i;
	int	j;

	i = ft_isdigit(c);
	j = ft_isalpha(c);
	if (c == '_' || j != 0)
		return (-1);
	if (i != 0)
		return (1);
	return (0);
}

char	**cpy_env(char **env, t_info *info, int len, int n)
{
	int		i;
	char	**tmp;

	(void) info;
	tmp = ft_calloc(sizeof(char *), (len + 4));
	mm(tmp);
	i = -1;
	while (env && env[++i])
		tmp[i] = ft_strdup(env[i]);
	if (!env || !env[0])
	{
		info->env = tmp;
		tmp[0] = ft_strdup("SHLVL=0");
		return (tmp);
	}
	tmp[len + 1] = 0;
	if (n == 1)
		mfree(env);
	return (tmp);
}

void	parsing_end(t_info *info)
{
	signal(SIGINT, handler_c);
	if (WIFEXITED(info->status))
		info->status = WEXITSTATUS(info->status);
	if (g_struct->tmp_len > 0)
		free(g_struct->tmp_ids);
	ft_ctrlc(0, info);
	g_struct->g_var = 0;
}
