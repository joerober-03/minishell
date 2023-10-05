/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiroz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:23:49 by shiroz            #+#    #+#             */
/*   Updated: 2023/05/13 12:29:14 by shiroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_find_var_2(t_info *info, t_cmd *list_cmd, char *tmp_char)
{
	if (tmp_char[1] == '?')
		list_cmd->tmp = ft_itoa(info->status);
	else if (ft_end_var(&tmp_char[1]) == 0)
		list_cmd->tmp = ft_strdup("$");
	else if (ft_end_var(&tmp_char[1]) > 0)
		list_cmd->tmp = ft_strdup(list_cmd->cmd);
}

void	ft_find_var(t_info *info, t_cmd *list_cmd)
{
	char		*tmp_char;
	size_t		i;
	size_t		size;

	while (list_cmd != NULL && list_cmd->cmd != NULL)
	{
		tmp_char = ft_strchr(list_cmd->cmd, '$');
		if (tmp_char && list_cmd->dollar == 1 && *tmp_char == '$')
		{
			i = 0;
			size = ft_strlen(tmp_char + 1);
			if (size > 0 && tmp_char[size - 1 + 1] == ' ')
				size--;
			while (info->env[i] && (ft_strncmp(info->env[i], tmp_char + 1, \
			size) != 0 || info->env[i][size] != '='))
				i++;
			if (info->env[i] && ft_strncmp(info->env[i], tmp_char + 1, size) == \
			0 && info->env[i][size] == '=')
				list_cmd->tmp = ft_strdup(&info->env[i][size + 1]);
			else
				ft_find_var_2(info, list_cmd, tmp_char);
		}
		list_cmd = list_cmd->next;
	}
}

void	ft_dollar_quote(t_info *info)
{
	ft_find_var(info, info->list_cmd);
	ft_replace_var(info, info->list_cmd);
	if (info->list_cmd)
		info->list_cmd->prev = NULL;
	if (info->list_cmd && (info->list_cmd->cmd || info->list_cmd->next))
		ft_final_join(info, info->list_cmd);
}

void	ft_preparation_cmd(t_info *info, t_cmd *list_cmd)
{
	int		i;
	t_cmd	*tmp;

	list_cmd->next = NULL;
	i = 1;
	ft_dollar_quote(info);
	tmp = info->list_cmd;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	info->tab_cmd = ft_calloc(sizeof(char *), i + 1);
	info->is_text = ft_calloc(sizeof(int), i + 10);
	mm(info->tab_cmd);
	if (!info->is_text)
		ft_error();
	i = 0;
	while (info->list_cmd != NULL)
	{
		info->tab_cmd[i] = info->list_cmd->cmd;
		info->is_text[i] = info->list_cmd->is_text;
		info->list_cmd = info->list_cmd->next;
		i++;
	}
}

void	ft_s_m_sg(t_info *info, int *ptr_i, t_cmd *list_cmd)
{
	int	i;
	int	tmp;

	i = *ptr_i;
	if (i > 0 && ft_isspace(&info->prompt[i - 1]) == 0)
		list_cmd->before = &info->prompt[i - 1];
	i++;
	tmp = i;
	while (info->prompt[i] && info->prompt[i] != '\'')
	i++;
	list_cmd->cmd = ft_substr(&info->prompt[tmp], 0, i - tmp);
	if (info->prompt[i] && ft_isspace(&info->prompt[i + 1]) == 0)
		list_cmd->after = &info->prompt[i + 1];
	*ptr_i = i;
}
