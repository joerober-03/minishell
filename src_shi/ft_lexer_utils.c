/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiroz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 11:31:12 by shiroz            #+#    #+#             */
/*   Updated: 2023/04/27 11:59:37 by shiroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_prep_t_cmd(t_cmd *chain, t_cmd *prev)
{
	chain->next = NULL;
	chain->prev = prev;
	chain->dollar = 0;
	chain->before = NULL;
	chain->after = NULL;
	chain->cmd = NULL;
	chain->tmp = NULL;
	chain->quotes = NULL;
	chain->is_text = 0;
}

int	ft_isspace(char *str)
{
	if (*str == '\t' || *str == '\v' || *str == ' ' || *str == '\n' || \
	*str == '\f' || *str == '\r')
		return (1);
	return (0);
}

int	ft_end_var(char	*str)
{
	int	i;
	int	j;

	i = ft_isdigit(*str);
	j = ft_isalpha(*str);
	if (ft_isspace(str) == 1)
		return (0);
	if (*str == '_' || j != 0)
		return (-1);
	if (i != 0)
		return (1);
	return (0);
}
