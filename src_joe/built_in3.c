/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:02:43 by joerober          #+#    #+#             */
/*   Updated: 2023/05/12 14:32:45 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	ft_env(t_info *info)
{
	int	i;

	info->trigger = 0;
	i = -1;
	while (info->env[++i])
		ft_printf("%s\n", info->env[i]);
	exit(0);
}

void	ft_pwd(t_info *info)
{
	char	path[128];
	int		i;

	info->trigger = 0;
	i = -1;
	m(getcwd(path, 128));
	while (path[++i])
		e(write(1, &path[i], 1));
	e(write(1, "\n", 1));
	exit(0);
}

long int	ft_check_number(t_info *info, char *to_check, long int tmp, int neg)
{
	int	i;

	i = 0;
	if ((to_check[i] == '-' || to_check[i] == '+') && i++ > -1 && \
	to_check[i - 1] == '-')
		neg = neg * -1;
	while (to_check[i] == '0')
		i++;
	to_check = &to_check[i];
	i = 0;
	while (to_check[i])
	{
		if (to_check[i] < '0' || to_check[i] > '9' || i > 10 || \
		tmp < -2147483648 || tmp > 21474836487)
		{
			e(tcsetattr(STDIN_FILENO, TCSANOW, &info->termios_save));
			mfree(info->tab_cmd);
			mfree(info->env);
			ft_putstr_fd("exit\nnumeric argument required\n", 2);
			exit(255);
		}
		tmp = to_check[i] - '0' + tmp * 10;
		i++;
	}
	return ((tmp * neg) % 256);
}

void	ft_exit(t_info *info, char **args, int ispipe)
{
	long int	tmp;
	long int	neg;

	tmp = 0;
	neg = 1;
	(void)args;
	info->trigger = 0;
	if (args[1])
		tmp = ft_check_number(info, args[1], tmp, neg);
	if (args[0] && args[1] && args[2] && info->status * 0 + 1 == 1)
	{
		info->status = 1;
		ft_putstr_fd("exit: too many arguments\n", 2);
		return ;
	}
	if (ispipe == 0)
	{
		e(write (2, "exit\n", 5));
		e(tcsetattr(STDIN_FILENO, TCSANOW, &info->termios_save));
	}
	mfree(info->tab_cmd);
	free(info->is_text);
	mfree(info->env);
	free(g_struct);
	exit(tmp);
}

char	**sort_export(t_info *info, int i, int j)
{
	char	**export;
	char	*tmp;

	export = cpy_env(info->env, info, i + 100, 0);
	i = 0;
	while (export[i + 1])
	{
		if (export[i][j] == export[i + 1][j])
			j++;
		else if (export[i][j] > export[i + 1][j])
		{
			tmp = export[i];
			export[i] = export[i + 1];
			export[i + 1] = tmp;
			i = 0;
			j = 0;
		}
		else
		{
			j = 0;
			i++;
		}
	}
	return (export);
}
