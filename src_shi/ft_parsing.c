/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiroz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 17:42:19 by shiroz            #+#    #+#             */
/*   Updated: 2023/05/13 12:20:36 by shiroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_replace_var_2(t_info *info, t_cmd **tmp, t_cmd **prev)
{
	if ((!(*tmp)->cmd || (*tmp)->cmd[0] == '\0') && (*prev) != (*tmp)->next)
	{
		if ((*prev) && (*prev)->after)
			(*prev)->after = (*tmp)->before;
		if ((*tmp)->next && (*tmp)->next->before)
			(*tmp)->next->before = (*tmp)->after;
		(*prev)->next = (*tmp)->next;
		(*tmp) = (*tmp)->next;
	}
	else if (!(*tmp)->cmd || (*tmp)->cmd[0] == '\0')
	{
		if ((*prev) && (*prev)->after)
			(*prev)->after = (*tmp)->before;
		if ((*tmp)->next && (*tmp)->next->before)
			(*tmp)->next->before = (*tmp)->after;
		(*tmp) = (*tmp)->next;
		if ((*tmp))
			(*prev) = (*tmp)->next;
		info->list_cmd = (*tmp);
	}
}

void	ft_replace_var(t_info *info, t_cmd *tmp)
{
	t_cmd	*prev;

	prev = tmp->next;
	while (tmp)
	{
		if (tmp->dollar >= 1)
		{
			if (tmp->dollar == 1)
			{
				free(tmp->cmd);
				tmp->cmd = tmp->tmp;
			}
			if (tmp->cmd && !tmp->cmd[0])
				free(tmp->cmd);
			if (!tmp->cmd || tmp->cmd[0] == '\0')
			{
				ft_replace_var_2(info, &tmp, &prev);
				continue ;
			}
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	ft_final_join(t_info *info, t_cmd *to_join)
{
	if (to_join->before && to_join->prev && to_join->prev->after)
	{
		to_join->tmp = ft_strjoin(to_join->prev->cmd, to_join->cmd);
		free(to_join->cmd);
		free(to_join->prev->cmd);
		to_join->prev->cmd = to_join->tmp;
		to_join->prev->next = to_join->next;
		to_join = to_join->prev;
		ft_final_join(info, to_join);
	}
	else if (to_join->after && to_join->next && to_join->next->before)
	{
		to_join->tmp = ft_strjoin(to_join->cmd, to_join->next->cmd);
		to_join->after = to_join->next->after;
		free(to_join->cmd);
		free(to_join->next->cmd);
		to_join->next = to_join->next->next;
		to_join->cmd = to_join->tmp;
		ft_final_join(info, to_join);
	}
	if (!to_join->next)
		return ;
	to_join->next->prev = to_join;
	ft_final_join(info, to_join->next);
}
