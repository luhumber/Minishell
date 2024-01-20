/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:09:17 by chsiffre          #+#    #+#             */
/*   Updated: 2023/08/14 15:10:17 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define REDIR 0
# define CMD 1
# define PIPE 2
# define REP_MAX 256
# define LLMAX  9223372036854775807

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <errno.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include "../libft/get_next_line_bonus.h"

extern int	g_error_last;

typedef struct s_env {
	char			*name;
	char			*value;
	int				equal;
	struct s_env	*next;
}	t_env;

typedef struct s_lst {
	char			**content;
	struct s_lst	*next;
	int				type;
}	t_lst;

typedef struct s_pipe {
	int	file_out;
	int	file_in;
	int	prev_fd;
	int	*tab_fd;
	int	*tab_pid;
	int	count;
	int	last;
}	t_pipe;

typedef struct s_data {
	t_lst	*lst;
	t_lst	*iterator;
	char	**fake_envp;
	char	*line;
	char	*path;
	char	**env_path;
	char	**split_path;
	char	**cmd;
	int		savestdin;
	int		savestdout;
	char	**res_split;
	char	**res_parse;
	ssize_t	i;
	ssize_t	y;
	t_env	*env;
	int		signal;
	int		fd;
	char	*limiter;
	t_pipe	*pipex;
	int		is_redir;
	int		in_redir;
	int		out_redir;
	int		ind;
	int		x;
	char	f_quote;
	char	s_quote;
	char	quote;
	int		loop;
	int		fake;
	char	**fake_path;
}	t_data;

//***********prompt***************//
void	ft_init_data(t_data *data, char **envp);
t_data	ft_init_struct(t_data data);
int		ft_builtins(t_data *data);
char	*ft_try_path(t_data *data, char *cmd);
void	ft_prompt(t_data *data);
int		ft_exec(t_data *prompt, char **cmd);
void	ft_conv_lst(char *line);
void	ft_get_env(t_data *data);

//***********parsing***************//
t_lst	*ft_parse(t_data *d);
t_lst	*add_command(t_lst *lst, t_data *data);
char	*ft_pre_split(char *str);
char	*ft_str_replace(char *str, char *copy, int new_size);
int		ft_is_redir(char *str);
t_lst	*ft_lstnew_t(char **strs, int type, int i);
t_lst	*ft_convert_in_lst(t_lst *lst, t_data *data);
int		ft_len_parse(char **strs, int i);
int		ft_is_redir(char *str);
t_lst	*ft_last(t_lst *lst);
char	**check_res_split(t_data *data);
int		resize_pre_split(char *str, int *new_size);
int		quote_open(char *str);
t_lst	*ft_add_lst(t_lst *lst, t_data *data, int type);
char	**ft_check_fil_content(char **strs, int *y, int *i, char **content);
char	**ft_check_redir(
			char **res_parse, t_data *data, char **strs, int start);
ssize_t	ft_strs_len(char **strs);
char	**ft_check_cmd(char **res_parse, t_data *d, char **strs, int start);
t_lst	*ft_check_builtins(t_lst *lst, t_data *data, ssize_t i);
void	ft_add_back(t_lst **lst, t_lst *new);
char	*copy_str(int *index, char *str, int len, char *ret);
char	*check_pipes(char *str, char *copy, int *i, int *y);
char	*check_chevron(char *str, char *copy, int *i, int *y);
char	*new_join(char const *s1, char const *s2, char *str);
void	*free_data(t_data *data);
int		empty(char *str);
char	*ft_convert_error(char *str, char *ret);
int		ft_int_len(int n);
char	*ft_check_quote_var(char *str, int i, char	*ret, t_data *data);
int		ft_is_not_space(char c);

//***********expand***************//
char	*ft_expand(char *str, t_data *data);
void	ft_skipping_var(char *str, int *i);
char	*copy_var(char *str, char *ret, int *i, t_data *data);
char	*replace_all_str(char *str, char *ret, int i, t_data *data);
int		check_size_var(char *str, int *i, int *new_size, t_data *data);
char	*replace_quote(char *str, char *ret, t_data *data);
int		if_expand(char *str);
int		var_exist(char *str, int *i, t_data *data);
int		is_var(char *str, int i, t_data *data, char *ret);
int		ft_compare_var(char *s1, char *s2, int i);
char	*replace_var(char *str, char *ret, int *i, t_data *data);;
void	check_size(char *str, int *i, int *new_size, t_data *data);
char	*resize_str(char *str, char *ret, t_data *data, int *new_size);
char	*resize_quote(char *str, t_data *data);
char	*is_quote(char *str, t_data *data);
char	*resize_var(char *str, t_data *data);
int		ft_nb_quote(char *str);
char	**check_quotes(char **strs, t_data *data);
char	*del_quote(char *str, char *ret, t_data *data);
void	ft_free(t_data *data);
int		check_pipe(char *str);

//***********dups***************//
int		ft_make_dup(t_data *data);
void	ft_dup_pipe(t_data *data);
int		ft_here_doc(t_data *data);
int		ft_close_end(t_data *data);

//***********builtins***************//
int		check_built(t_data *data);
int		ft_is_builtins(char *str);
void	ft_echo(t_data *data);
int		ft_unset(t_data *data);
int		ft_export(t_data *data);
void	ft_cd(t_data *data);
int		ft_exit(t_data *data);
char	**fill_built(t_data *data, char **cmd);

//***********t_env***************//
void	ft_struct_env(t_data *data);
void	ft_add_var(t_data *data, char *str, int exist);
char	*ft_switch_value(char *val, char *str, int i);
t_env	*ft_envlast(t_env *lst);
t_env	*ft_new_env(char *str);
void	ft_envadd_back(t_env **env, t_env *new);
int		ft_has_equal(char *str);
int		ft_check_exist(t_data *data, t_env *env, char *str);
char	*ft_find_name(char *name, char *str);
char	*new_val(t_env *new, char *str, int i);
char	*ft_add_value(char *str, int i);
void	update_env(t_data *data);

//***********exec***************//
int		ft_check_type(t_data *data);
int		is_executable(char *content);
int		ft_which_redir(t_data *data);
int		ft_pipe(t_data *data);
int		ft_execute_cmd(t_data *data, char *content);
char	**ft_cmd_options(t_data *data, char **cmd, char *content);
int		ft_end(t_data *data);
void	ft_restore_loop(t_data *data, pid_t pid, int *fd, int count);
char	*fake_try_path(t_data *data, char *cmd);

//***********error***************//
int		ft_print_error(char *str, int error_code);
int		ft_write_error(char *str);
int		ft_cmd_error(char	*str);
void	ft_error(t_data *data, char *str, int exit_code, int parse);
int		ft_special_char(char *cmd);
int		ft_export_error(char *str);
void	ft_rl_error(t_data *data);
void	ft_exit_pack(t_data *data, int code_error, int ex, int error);
void	ft_syntax_error(char *str);
void	env_error(t_data *data);

//***********utils***************//
int		ft_compare_str(char *s1, char *s2);
int		list_progress(t_data *data);
int		ft_lstlen(t_lst *lst);

//***********free***************//
void	ft_to_free(t_data *data);
int		ft_free_for_end(t_data *data);
void	free_cmd(char **cmd);
void	free_old_path(t_data *data, int end);

//***********signal***************//
void	ft_ctrl(int signal);
void	ft_ctrl_fork(int signal);
void	ft_here_sig(int signal);
void	ft_mini_sig(int signal);
void	check_signal(t_data *data);

#endif