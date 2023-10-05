/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:44:37 by joerober          #+#    #+#             */
/*   Updated: 2023/05/13 12:44:38 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	tmp_to_malloc(char **args, t_info *info)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (args[++i])
	{
		if (args[i][0] == '<' && args[i][1] == '<' && info->is_text[i] == 1)
			len++;
	}
	if (len > 0)
	{
		g_struct->tmp_ids = ft_calloc(sizeof(int), (len + 5));
		if (!g_struct->tmp_ids)
			ft_error();
	}
}

int	tmp_is_error(t_info *info, char **args, int doc_id, int i)
{
	if (args[i][0] == '>' && info->is_text[i] == 1)
	{
		if (!args[i + 1] || args[i][0] == '\n' || info->is_text[i + 1] == 1)
		{
			ft_printf("syntax error near token following '>'\n");
			info->status = 258;
			if (g_struct->tmp_len > 0)
				free(g_struct->tmp_ids);
			g_struct->g_var = 5;
		}
	}
	else if (args[i][0] == '|' && info->is_text[i] == 1)
	{
		if (!args[i + 1] || args[i][0] == '\n' || i == 0
				|| (args[i + 1][0] == '|' && info->is_text[i + 1] == 1))
		{
			ft_printf("syntax error near token following '|'\n");
			info->status = 258;
			if (g_struct->tmp_len > 0)
				free(g_struct->tmp_ids);
			g_struct->g_var = 5;
		}
		doc_id++;
	}
	return (doc_id);
}

void	tmp_heredoc_short(t_info *info, char **args, int i, int len)
{
	int		j;
	char	*limiter;

	j = -1;
	limiter = ft_calloc(sizeof(char), ft_strlen(args[i]) - 1);
	if (!limiter)
	{
		ft_error();
		g_struct->g_var = 5;
	}
	while (args[i][len++])
		limiter[++j] = args[i][len];
	g_struct->tmp_ids[g_struct->tmp_len++] = info->id;
	if (!limiter[0])
	{
		ft_printf("syntax error near token following heredoc\n");
		info->status = 258;
		if (g_struct->tmp_ids[0])
			free(g_struct->tmp_ids);
		g_struct->g_var = 5;
	}
	else
		here_doc(info, limiter);
	free(limiter);
	g_struct->tmp_ids[g_struct->tmp_len++] = info->id;
}

void	tmp_heredoc(t_info *info, char **args, int i, int doc_id)
{
	tmp_to_malloc(args, info);
	while (args[++i] && g_struct->g_var != 5)
	{
		if (args[i][0] == '<' && info->is_text[i] == 1)
		{
			if (args[i][1] == '<')
			{
				info->id = doc_id;
				tmp_heredoc_short(info, args, i, 1);
			}
			else
			{
				if (!args[i + 1] || args[i][0] == '\n'
						|| info->is_text[i + 1] == 1)
				{
					ft_printf("syntax error near token following '<'\n");
					info->status = 258;
					if (g_struct->tmp_len > 0)
						free(g_struct->tmp_ids);
					g_struct->g_var = 5;
				}
			}
		}
		doc_id += tmp_is_error(info, args, 0, i);
	}
}
