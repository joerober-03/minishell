/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_for_lexing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiroz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:35:50 by shiroz            #+#    #+#             */
/*   Updated: 2023/05/13 10:22:52 by shiroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_less_than_quotes(t_info *info, int *i, int quotes)
{
	(*i)++;
	while (info->prompt[*i] && info->prompt[*i] != quotes)
	{
		(*i)++;
	}
	if (info->prompt[*i] == '\0')
		exit(write(2, "close your quotes\n", 18));
}

void	ft_l_t_c_1(t_info *info, int *begin, char *final, int *j)
{
	final[*j] = info->prompt[*begin];
	(*j)++;
	(*begin)++;
}

void	ft_less_than_copy(t_info *info, int *i, int *begin, char *final)
{
	int	j[2];

	j[0] = 0;
	while (*begin <= *i)
	{
		j[1] = info->prompt[*begin];
		if ((j[1] == '\'' || j[1] == '\"') && ++(*begin) > -10)
		{
			while (info->prompt[*begin])
			{
				if ((j[1] == info->prompt[*begin]) && ++(*begin) > -10)
					break ;
				ft_l_t_c_1(info, begin, final, &j[0]);
			}
			if ((info->prompt[*begin] == '\0' || (ft_end_var(&info->prompt \
			[*begin]) == 0 && (info->prompt[*i] == '\'' || info->prompt[*i] \
			== '\"'))) && j[0] == 0)
			{
				final[j[0]] = '\n';
				return ;
			}
			continue ;
		}
		ft_l_t_c_1(info, begin, final, &j[0]);
	}
}

char	*ft_less_than(t_info *info, int *i, int begin, t_cmd *final)
{
	if (info->prompt[*i + 1] != '<')
		return (ft_substr(&info->prompt[*i], 0, 1));
	*i = *i + 2;
	while (&info->prompt[*i] && ft_isspace(&info->prompt[*i]) == 1)
		(*i)++;
	while (info->prompt[*i] != '\0' && (ft_end_var(&info->prompt[*i]) != 0 \
	|| info->prompt[*i] == '\'' || info->prompt[*i] == '\"' || \
	info->prompt[*i] == '$'))
	{
		if (info->prompt[*i] == '\'' || info->prompt[*i] == '\"')
			ft_less_than_quotes(info, i, info->prompt[*i]);
		(*i)++;
	}
	if (info->prompt[*i] == '\0' || ft_end_var(&info->prompt[*i]) == 0)
		(*i)--;
	final->cmd = ft_calloc(1, *i - begin + 2);
	if (!final->cmd)
		ft_error();
	final->cmd[0] = '<';
	final->cmd[1] = '<';
	begin = 2 + begin;
	while (ft_isspace(&info->prompt[begin]) == 1)
		begin++;
	ft_less_than_copy(info, i, &begin, &final->cmd[2]);
	return (final->cmd);
}
