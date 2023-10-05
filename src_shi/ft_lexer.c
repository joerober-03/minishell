/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiroz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:06:09 by shiroz            #+#    #+#             */
/*   Updated: 2023/05/13 12:34:54 by shiroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_split_minishell_2(t_info *info, int *ptr_i, t_cmd *list_cmd)
{
	int	i;

	i = *ptr_i;
	if (info->prompt[i] == '|' || info->prompt[i] == '>')
		ft_s_m_pld(info, &i, list_cmd);
	else if (info->prompt[i] == '<' && ++list_cmd->is_text > -1)
		list_cmd->cmd = ft_less_than(info, &i, i, list_cmd);
	else if (info->prompt[i] == '\'')
		ft_s_m_sg(info, &i, list_cmd);
	else if (info->prompt[i] == '$' && (info->prompt[i + 1] == '\'' || \
	info->prompt[i + 1] == '\"'))
		ft_s_m_bd(info, &i, list_cmd);
	else if (info->prompt[i] == '\"')
		ft_main_double_quotes(info, &i, list_cmd);
	else if (info->prompt[i] == '$')
		ft_s_m_d(info, &i, list_cmd);
	else if (info->prompt[i])
		ft_s_m_n(info, &i, list_cmd);
	if (info->prompt[i])
		i++;
	*ptr_i = i;
}

void	ft_split_minishell(t_info *info, int i, t_cmd *list_cmd)
{
	t_cmd	next;

	while (info->prompt[i] && info->prompt[i] == ' ')
		i++;
	ft_split_minishell_2(info, &i, list_cmd);
	if (info->prompt[i])
	{
		list_cmd->next = &next;
		ft_prep_t_cmd(&next, list_cmd);
		ft_split_minishell(info, i, &next);
	}
	else
		ft_preparation_cmd(info, list_cmd);
}

int	ft_check_quotes(char *check)
{
	int		i;
	char	c;

	i = 0;
	if (!check)
		return (1);
	while (check[i])
	{
		while (check[i] != '\'' && check[i] != '\"' && check[i])
			i++;
		if (check[i] == '\'' || check[i] == '\"')
		{
			c = check[i];
			i++;
			while (check[i] != c && check[i])
				i++;
			if (check[i] != c)
				return (1);
			i++;
		}
	}
	return (0);
}

void	ft_lexer(t_info *info)
{
	t_cmd	cmd;
	t_cmd	cmd2;
	t_info	tmp;

	if (!info->prompt)
		return ;
	info->tab_cmd = NULL;
	if (1 == ft_check_quotes(info->prompt))
		return ;
	tmp = *info;
	tmp.list_cmd = &cmd2;
	tmp.tmp = info;
	info->tmp = &tmp;
	info->list_cmd = &cmd;
	ft_prep_t_cmd(&cmd2, &cmd2);
	ft_prep_t_cmd(&cmd, &cmd);
	ft_split_minishell(info, 0, &cmd);
}
