/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 19:05:37 by joctopus          #+#    #+#             */
/*   Updated: 2022/03/11 02:59:24 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * разрешены:
 * 		readline, rl_clear_history, rl_on_new_line,
		rl_replace_line, rl_redisplay, add_history,
 * **/

char	*get_promt(char **env)
{
	char	*tmp;
	char	*home;
	char	*path;
	char	cwd[4097];

	home = get_env(env, "HOME");
	getcwd(cwd, 4096);
	if (ft_memcmp(cwd, home, ft_strlen(home)))
		path = ft_strdup(cwd);
	else
		path = ft_strjoin("~", cwd + ft_strlen(home));
	tmp = ft_strjoin(path, DF "$ ");
	free(path);
	path = ft_strjoin(CYAN, tmp);
	free(tmp);
	tmp = ft_strjoin(MAGENTA SHL, path);
	free(path);
	return (tmp);
}

/** signal SIGINT
 *  нельзя удалять (чтобы полсе парсера всегда был правильный обработчик)	**/
static int	read_input(t_data **data, char **str, char **promt)
{
	signal(SIGINT, shell_sigint_handler);
	if (*promt)
	{
		*str = readline(*promt);
		if (!(*str))
			return (0);
		if (!(ft_strlen(*str) == 0 || input_empty(*str)))
		{
			add_history(*str);
			(*data)->str = ft_strdup(*str);
			parser(data);
		}
	}
	return (1);
}

static void	exit_from_shell(t_data **data, char **promt)
{
	free(*promt);
	free_mtrx((*data)->env);
	free_mtrx((*data)->export);
	(*data)->promt = NULL;
	free(*data);
	printf("exit\n");
	exit(0);
}
	// if ((*data)->promt != NULL)
	// 	free((*data)->promt);   --- remove double free

/** для того чтобы у readline всегда был доступ к promt
 * 	+ актуальный путь на каждой интерации**/
static char	*current_promt(t_data *data, char *oldpromt)
{
	char	*temp;

	temp = get_promt(data->env);
	if (ft_strcmp(oldpromt, temp) != 0)
	{
		free(oldpromt);
		oldpromt = temp;
	}
	else
		free(temp);
	return (oldpromt);
}

void	readline_input(t_data **data)
{	
	char			*str;

	str = NULL;
	(*data)->promt = get_promt((*data)->env);
	rl_clear_history();
	while (read_input(data, &str, &(*data)->promt))
	{
		free(str);
		(*data)->promt = current_promt(*data, (*data)->promt);
	}
	exit_from_shell(data, &(*data)->promt);
}

/** signal(SIGINT, sigint_handler); ctrl-C обработчик **/
/**
 * 
	историю придется писать вручную так
	как большенство функций из history недоступны для использования
 * **/
