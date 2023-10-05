/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiroz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:21:02 by shiroz            #+#    #+#             */
/*   Updated: 2023/05/12 18:30:32 by shiroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_double_quotes_2(t_info *info)
{
	t_cmd	*tmp;
	char	*final;
	char	*to_free;

	to_free = NULL;
	final = ft_calloc(1, 1);
	m(final);
	tmp = info->list_cmd;
	ft_find_var(info, info->list_cmd);
	ft_replace_var(info, info->list_cmd);
	while (tmp)
	{
		if (!tmp->cmd)
		{
			tmp = tmp->next;
			continue ;
		}
		to_free = final;
		final = ft_strjoin(final, tmp->cmd);
		free(tmp->cmd);
		free(to_free);
		tmp = tmp->next;
	}
	return (final);
}

void	ft_double_quotes_1_5(t_cmd *quotes, int *i, int *tmp, t_cmd *next)
{
	quotes->next = next;
	ft_prep_t_cmd(next, NULL);
	*tmp = *i;
	(*i)++;
}

char	*ft_double_quotes(t_info *info, t_cmd *quotes, int *i, int tmp)
{
	t_cmd	next;

	while (info->prompt[*i] && info->prompt[*i] != '\"' && ((info->prompt[tmp] \
	!= '$' && info->prompt[*i] != '$') || (info->prompt[tmp] == '$' && \
	ft_end_var(&info->prompt[*i]) != 0)))
		(*i)++;
	if (info->prompt[tmp + 1] == '?')
		(*i)++;
	if (*i - tmp != 0)
		quotes->cmd = ft_substr(&info->prompt[tmp], 0, (*i - tmp));
	else
		return (ft_calloc(1, 1));
	if (info->prompt[tmp] == '$')
		quotes->dollar = 1;
	if (info->prompt[*i] && info->prompt[*i] != '\"')
	{
		ft_double_quotes_1_5(quotes, i, &tmp, &next);
		return (ft_double_quotes(info, &next, i, tmp));
	}
	else
	{
		quotes->next = NULL;
		return (ft_double_quotes_2(info));
	}
}

void	ft_main_double_quotes(t_info *info, int *i, t_cmd *list_cmd)
{
	t_cmd	cmd2;
	t_info	tmp;

	tmp = *info;
	tmp.list_cmd = &cmd2;
	tmp.tmp = info;
	info->tmp = &tmp;
	ft_prep_t_cmd(&cmd2, &cmd2);
	if (*i > 0 && ft_isspace(&info->prompt[*i - 1]) == 0)
		list_cmd->before = &info->prompt[*i - 1];
	(*i)++;
	if (info->prompt[*i] == '$' && (*i)++ > -1)
		list_cmd->cmd = ft_double_quotes(info->tmp, \
		info->tmp->list_cmd, i, *i - 1);
	else
		list_cmd->cmd = ft_double_quotes(info->tmp, info->tmp->list_cmd, i, *i);
	if (info->prompt[*i] && ft_isspace(&info->prompt[*i + 1]) == 0)
		list_cmd->after = &info->prompt[*i + 1];
}
