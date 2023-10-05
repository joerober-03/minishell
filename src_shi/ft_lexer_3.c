/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiroz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:06:09 by shiroz            #+#    #+#             */
/*   Updated: 2023/05/13 12:32:27 by shiroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_s_m_d(t_info *info, int *ptr_i, t_cmd *list_cmd)
{
	int	i;
	int	tmp;

	i = *ptr_i;
	tmp = i;
	if (tmp > 0 && ft_isspace(&info->prompt[i - 1]) == 0)
		list_cmd->before = &info->prompt[i - 1];
	i++;
	while (info->prompt[i] && ft_end_var(&info->prompt[i]) != 0)
		i++;
	i--;
	if (info->prompt[i] && ft_isspace(&info->prompt[i + 1]) == 0)
		list_cmd->after = &info->prompt[i + 1];
	if (info->prompt[i + 1] == '?')
		i++;
	list_cmd->cmd = ft_substr(&info->prompt[tmp], 0, i - tmp + 1);
	list_cmd->dollar = 1;
	*ptr_i = i;
}

void	ft_s_m_n(t_info *info, int *ptr_i, t_cmd *list_cmd)
{
	int	i;
	int	tmp;

	i = *ptr_i;
	tmp = i;
	if (tmp > 0 && ft_isspace(&info->prompt[i - 1]) == 0)
		list_cmd->before = &info->prompt[i - 1];
	i++;
	while (info->prompt[i] && (info->prompt[i] != ' ' && info->prompt[i] \
	!= '<' && info->prompt[i] != '>' && info->prompt[i] != '|' \
	&& info->prompt[i] != '$' && info->prompt[i] != '\'' \
	&& info->prompt[i] != '\"'))
		i++;
	i--;
	if (info->prompt[i] && ft_isspace(&info->prompt[i + 1]) == 0)
	list_cmd->after = &info->prompt[i + 1];
		list_cmd->cmd = ft_substr(&info->prompt[tmp], 0, i - tmp + 1);
	*ptr_i = i;
}

void	ft_s_m_bd(t_info *info, int *ptr_i, t_cmd *list_cmd)
{
	int	i;

	i = *ptr_i;
	if (ft_isspace(&info->prompt[i - 1]) == 0)
		list_cmd->before = &info->prompt[i - 1];
	list_cmd->cmd = ft_calloc(1, 1);
	m(list_cmd->cmd);
	if (info->prompt[i] && ft_isspace(&info->prompt[i + 1]) == 0)
		list_cmd->after = &info->prompt[i + 1];
	*ptr_i = i;
}

void	ft_s_m_pld(t_info *info, int *ptr_i, t_cmd *list_cmd)
{
	int	i;
	int	tmp;

	i = *ptr_i;
	tmp = 0;
	if (info->prompt[i + 1] == '>' && i++ > -1)
		tmp++;
	list_cmd->cmd = ft_substr(&info->prompt[i - tmp], 0, 1 + tmp);
	list_cmd->is_text++;
	*ptr_i = i;
}
