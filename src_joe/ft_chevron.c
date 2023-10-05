/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chevron.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:06:46 by joerober          #+#    #+#             */
/*   Updated: 2023/05/12 15:47:49 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	chevron_dup(t_info *info, t_chev *chev)
{
	if (chev->trigger == 0)
	{
		info->after_infile = 0;
		info->after_doc = 1;
		info->here_tmp2 = open(ft_strjoin("/tmp/minishell_tmp_",
					ft_itoa(info->id)), O_RDONLY);
		e(unlink(ft_strjoin("/tmp/minishell_tmp_", ft_itoa(info->id))));
		e(dup2(info->here_tmp2, 0));
		e(close(info->here_tmp2));
	}
	else if (chev->trigger == 1)
	{
		if (info->after_doc == 1)
			e(unlink(ft_strjoin("/tmp/minishell_tmp_", ft_itoa(info->id))));
		info->after_infile = 1;
		info->after_doc = 0;
		e(dup2(chev->infile, 0));
	}
	if (info->after_chevron == 1)
		e(dup2(chev->outfile, 1));
}

int	ft_chevron_outfile(t_info *info, char **args, t_chev *chev)
{
	if (args[chev->i][1] == '>' && ++(chev->i) > -1)
	{
		info->is_text_id++;
		chev->outfile = open(args[chev->i],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		chev->len -= 2;
	}
	else
	{
		chev->i++;
		info->is_text_id++;
		chev->outfile = open(args[chev->i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		chev->len -= 2;
	}
	if (chev->outfile == -1)
	{
		ft_printf("%s: Permission denied or inexistant\n", args[chev->i]);
		info->after_chevron = 0;
		info->status = 1;
		if (chev->isfork == 1)
			return (1);
		exit(1);
	}
		info->after_chevron = 1;
	return (0);
}

int	ft_chevron_infile(t_info *info, char **args, t_chev *chev)
{
	if (args[chev->i][1] == '<')
	{
		chev->trigger = 0;
		chev->len--;
		info->after_doc = 1;
	}
	else
	{
		chev->i++;
		info->is_text_id++;
		chev->infile = open(args[chev->i], O_RDONLY);
		if (chev->infile == -1)
		{
			ft_printf("%s: Permission denied or inexistant\n", args[chev->i]);
			info->status = 1;
			if (chev->isfork == 1)
				return (1);
			exit(1);
		}
		chev->trigger = 1;
		chev->len -= 2;
	}
	return (0);
}

char	**chevron_end(t_info *info, t_chev *chev, char **env, char **args)
{
	char	**new_args;

	info->is_text_id++;
	new_args = chevron_new_args(info, args, chev, -1);
	chevron_dup(info, chev);
	free(chev);
	chevron_exec(info, new_args, env);
	return (new_args);
}

char	**ft_chevron(t_info *info, char **args, char **env, int isfork)
{
	t_chev	*chev;
	char	**new_args;

	chev = (t_chev *)ft_calloc(sizeof(t_chev), 1);
	if (!chev)
		ft_error();
	chevron_init(chev, info, args, isfork);
	while (args[chev->i])
	{
		if (args[chev->i][0] == '<' && info->is_text[info->is_text_id] == 1)
		{
			if (ft_chevron_infile(info, args, chev) == 1)
				return (NULL);
		}
		else if (args[chev->i][0] == '>'
			&& info->is_text[info->is_text_id] == 1)
		{
			if (ft_chevron_outfile(info, args, chev) == 1)
				return (NULL);
		}
		chev->i++;
		info->is_text_id++;
	}
	new_args = chevron_end(info, chev, env, args);
	return (new_args);
}
