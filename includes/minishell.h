/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 20:13:02 by joctopus          #+#    #+#             */
/*   Updated: 2022/03/10 03:32:03 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <term.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include <string.h>

# include <sys/wait.h>
# include <sys/stat.h>

# define RED			"\001\e[1m\e[31m\002"
# define BLUE			"\001\e[1m\e[34m\002"
# define GREEN			"\001\e[1m\e[32m\002"
# define MAGENTA		"\001\e[1m\e[35m\002"
# define CYAN			"\001\e[1m\e[36m\002"
# define DF				"\001\e[0m\002"

# define SHL			"minishell: "

typedef struct s_history
{
	char				*line;
	struct s_history	*next;
	struct s_history	*prev;
}				t_history;

typedef struct s_data
{
	int				argc;
	char			**argv;
	char			**env;
	char			**export;
	int				ret;
	char			*str;
	char			**commands;
	int				child;
	char			*promt;
}				t_data;

/** env utils **/
char		**copy_env(char **envp, int add);
char		*get_env(char **envp, char *env);
int			strlen_env(char *str);

/** cmds utils **/
int			redirect(t_data *data, int i, int fd);
int			strlen_arg(char *str);
int			strlen_arg_token(char *str, char c);
void		set_args(char **argv, char *str, int argc);
char		**copy_args(t_data *data);
void		exec_bin(int fd, char *path, t_data *data);
void		bash_cmd(t_data **data);
void		set_path(char *str, char **path);
void		bash_cmd_init(t_data **data, char **start, char **path, char *buff);
char		**split_path(t_data *data, char *str);
int			init_search_bin(char ***paths, int *i, t_data *data, char *str);

/** parser and other utils**/
int			pre_parser(t_data *data);
void		parser(t_data **data);
void		check_params(char **str, int *i, int *len, int *pos);
void		pipe_or_cmd(t_data **data, int n);
void		init_check_pipe(int *chlds, int **flag, int *j);
void		switch_pipes(int *fds);
int			switch_flag(t_data *data, int i, int j);
char		**check_command(char *str, t_data **data);
int			wrong_delimeters(int argc, char **argv);

/** bultins	checkers**/
int			check_builtins(int fd, t_data **data);
int			check_bin(int fd, t_data *data);

/** bultins cmds**/
void		echo_command(t_data *data, int fd);
void		cd_command(t_data *data);
void		exit_command(t_data *data);
void		env_command(t_data *data, int fd);
char		**export_command(t_data *data, int j);
int			export_have_comment(char **argv, int *i);
void		export_value(t_data **data, int *i);
int			check_export_error(char **argv, int *i);
void		sort_env(char **env, int fd, char c);
char		**unset_command(t_data *data, int j);
void		update_exported_value(t_data **data, char **s, int j, int *i);

/** signal handlers **/
void		sigint_handler(int sig);
void		shell_handler(int sig);
void		child_sgnl_handler_bash(int sig);
void		child_sgnl_handler(int sig);
void		sigquit_handler(int sig);
void		shell_sigint_handler(int sig);
void		shell_sigquit_handler(int sig);
void		child_sigquit_handler(int sig);

/**	extra utils	**/
void		ft_addchar(char **str, char c);
void		free_strs(char *str1, char *str2, char *str3);
void		free_mtrx(char **mtrx);
int			strs_tofd(char *first, char *second, char *third, int fd);
void		free_mtrx(char **mtrx);
int			count_args(char *str);
int			char_pos(char *str, char c);
void		del_token(char **arg);
void		del_char(char **str, int i);
void		del_backslash(char **arg, int *i);
int			istoken(char c);
int			is_space(int c);
void		skip_escapes(char **str);
int			ft_strlen_char(char *str, char c);
void		ft_putstrlen_fd(char *s, int len, int fd);
void		init_ints(int *y, int *z, int y_value, int z_value);
int			inc_cmd(char **argv, int i);
void		swap_mtrxs(t_data **data, char ***arr);
void		null_export(char **tmp);

/** readline **/
void		init_readline(void);
void		readline_input(t_data **data);
int			input_empty(char *str);
void		show_args(int argc, char **argv);

#endif
