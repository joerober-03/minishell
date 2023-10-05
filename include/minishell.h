/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:44:49 by joerober          #+#    #+#             */
/*   Updated: 2023/05/13 13:04:03 by shiroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <termios.h>
# include <signal.h>
# include <dirent.h>
# include <termcap.h>

typedef struct s_chev
{
	int		i;
	int		len;
	int		outfile;
	int		infile;
	int		trigger;
	int		index;
	char	**new_args;
	int		isfork;
}				t_chev;

typedef struct s_cmd
{
	struct s_cmd	*next;
	struct s_cmd	*prev;
	int				dollar;
	char			*before;
	char			*after;
	char			*cmd;
	char			*to_free;
	char			*tmp;
	char			**quotes;
	int				is_text;
}					t_cmd;

typedef struct s_info
{
	struct s_info	*tmp;
	t_cmd			*list_cmd;
	t_cmd			*quotes;
	char			*prompt;
	char			**tab_cmd;
	int				*is_text;
	struct termios	termios_save;
	int				pipefd[2];
	int				heredocfd[2];
	int				trigger;
	char			**env;
	int				status;
	int				after_doc;
	int				after_pipe;
	int				after_infile;
	int				after_chevron;
	int				after_sig;
	int				saved_out;
	int				saved_in;
	int				pipe_num;
	int				id;
	int				here_tmp;
	int				here_tmp2;
	int				g_var;
	int				*tmp_ids;
	int				tmp_len;
	int				child_pid;
	int				is_text_id;
}				t_info;

t_info	*g_struct;

///////////////shiroz///////////////////////
//look up*
void	ft_lexer(t_info *info);
//Check if the char means the end of the $var
int		ft_end_var(char	*str);
//Check if it is whitespace
int		ft_isspace(char *str);
//
void	ft_main_double_quotes(t_info *info, int *i, t_cmd *list_cmd);
void	ft_prep_t_cmd(t_cmd *chain, t_cmd *prev);
void	ft_final_join(t_info *info, t_cmd *to_join);
void	ft_replace_var(t_info *info, t_cmd *tmp);
char	*ft_double_quotes(t_info *info, t_cmd *quotes, int *i, int tmp);
void	ft_find_var(t_info *info, t_cmd *list_cmd);
char	*ft_less_than(t_info *info, int *i, int begin, t_cmd *final);
void	ft_find_var_2(t_info *info, t_cmd *list_cmd, char *tmp_char);
void	ft_find_var(t_info *info, t_cmd *list_cmd);
void	ft_dollar_quote(t_info *info);
void	ft_preparation_cmd(t_info *info, t_cmd *list_cmd);
void	ft_s_m_sg(t_info *info, int *ptr_i, t_cmd *list_cmd);
void	ft_s_m_d(t_info *info, int *ptr_i, t_cmd *list_cmd);
void	ft_s_m_n(t_info *info, int *ptr_i, t_cmd *list_cmd);
void	ft_s_m_bd(t_info *info, int *ptr_i, t_cmd *list_cmd);
void	ft_s_m_pld(t_info *info, int *ptr_i, t_cmd *list_cmd);
////////////////joerober////////////////////
//////////////////initiation////////////////
void	ft_parsing(char **args, char **env, t_info *info);
void	parsing_end(t_info *info);
void	handler_c(int num);
void	handler_bs(int num);
char	**group_cmds(char **args);
//////////////////pipe//////////////////////
void	pipe_init(t_info *info, char **env, char **args);
void	ft_pipe(t_info *info, char **args, int num, char **env);
char	**remove_pipes(t_info *info, char **args);
void	built_ins_pipe(char **args, t_info *info, char **env);
char	*get_path(char *cmd, char **env);
char	*link_path(char *dir, char *cmd);
int		chr_len(char *path, char c);
char	*strn_dup(char *str, int n);
///////////////chevron&here_doc/////////////
char	**ft_chevron(t_info *info, char **args, char **env, int isfork);
void	chevron_init(t_chev *chev, t_info *info, char **args, int isfork);
char	**chevron_new_args(t_info *info, char **args, t_chev *chev, int i);
void	chevron_exec(t_info *info, char **new_args, char **env);
char	*ft_chevron_pipe(t_info *info, char **args, char **env);
void	tmp_heredoc(t_info *info, char **args, int i, int doc_id);
void	tmp_to_malloc(char **args, t_info *info);
int		tmp_is_error(t_info *info, char **args, int doc_id, int i);
void	tmp_heredoc_short(t_info *info, char **args, int i, int len);
void	here_doc(t_info *info, char *limit);
char	**here_new_args(char **args, int i, int j);
////////////built_ins///////////////////////
void	ft_hide(t_info *info);
void	ft_ctrlc(int n, t_info *info);
void	ft_echo(char **args, t_info *info);
void	ft_cd(t_info *info, char **args, char **env);
void	ft_pwd(t_info *info);
void	ft_env(t_info *info);
void	ft_unset(t_info *info, char **args, int i, int j);
void	ft_exit(t_info *info, char **args, int ispipe);
void	ft_export(t_info *info, char **args);
char	**sort_export(t_info *info, int i, int j);
void	export_no_args(t_info *info);
//////////////////execution/////////////////
void	exec(char *cmd, char **env, t_info *info);
void	exec2(char **cmd, char **env);
void	ft_execve(t_info *info, char **args, char *str, char **env);
///////////////utils////////////////////////
int		strcmp_ms(const char *s1, const char *s2);
int		strcmp_ms_caps(const char *s1, const char *s2);
int		find_char(char **str, char c, t_info *info);
int		find_char2(char *str, char c);
int		find_char_place(char **str, char c);
char	*ft_strjoin_space(char *str1, char *str2);
void	ft_putstr_fd_quotes(char *s, int fd);
char	**cpy_env(char **env, t_info *info, int len, int n);
int		ft_end_var2(char c);
int		ft_error(void);
void	e(int e);
void	m(char *m);
void	mm(char **mm);
char	**group_cmds(char **args);
char	*group_cmd(char **args);
void	clear_tmp_files(void);
//////////////////GNU_librairy//////////////
void	rl_replace_line(const char *str, int i);
void	rl_clear_history(void);

#endif
