/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:24:08 by joctopus          #+#    #+#             */
/*   Updated: 2022/03/04 17:06:02 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_pipe_args(t_data *data, int i)
{
	char	**args;
	int		j;
	int		k;

	j = 0;
	while (data->argv[i + j] && ft_memcmp(data->argv[i + j], "|", 2))
		j++;
	args = (char **)ft_calloc(sizeof(char *), j + 1);
	k = -1;
	while (++k < j)
		args[k] = ft_strdup(data->argv[i + k]);
	data->argv = args;
	data->argc = j;
}

/**	 работа с пайпом **/
static void	pipe_chld(int *flag, int *fds, t_data *data, int pos)
{
	int		i;
	int		argc;
	char	**argv;
	pid_t	id;

	signal(SIGINT, child_sgnl_handler);
	id = fork();
	if (!id)
	{
		if (!flag[0])
			dup2(fds[0], 0);
		if (!flag[1])
			dup2(fds[3], 1);
		i = 0;
		while (i < 4)
			close(fds[i++]);
		argc = data->argc;
		argv = data->argv;
		set_pipe_args(data, pos);
		check_command(data->str, &data);
		free_mtrx(data->argv);
		data->argc = argc;
		data->argv = argv;
		exit(data->ret);
	}
}

/** проверка pipe**/
static int	check_pipe(int *fds, t_data *data)
{
	int		chlds;
	int		*flag;
	int		i;
	int		j;

	flag = NULL;
	init_check_pipe(&chlds, &flag, &j);
	while (data->argv[j])
	{
		i = 0;
		while (data->argv[j + i] && ft_memcmp(data->argv[j + i], "|", 2))
			i++;
		flag[1] = switch_flag(data, i, j);
		pipe_chld(flag, fds, data, j);
		chlds++;
		flag[0] = 0;
		switch_pipes(fds);
		if (!data->argv[j + i])
			j = j + i;
		else
			j = j + i + 1;
	}
	free(flag);
	return (chlds);
}

/** command or pipe (check)
 *	 кратко о dup
 * 	dup дублирует файловый дискриптор, система создает копию файлового диск-ра.
 *  после этого новый и старый фд может быть использован interchangeably 
 *  (взаимозаменяемо)
 * 
 * 	std_out теперь dup(0),  создали копию файлового дискриптора и открыли ее.
 * 
 * 	пробегаем по всему argv до тех пор пока не встретим пропустим все |
 * 		data->env = check_command(data->commands[n], data);
 * 			 - проверка команды из своих builtins и бинарников системы
 * 		если команада является pipe 
 * 			else if (data->commands[n])
 * 				создаем pipe для перенаправления файловых дискрипторов
 * 			pipe(fds) -> fds[0] fds[1] будет содержать фд, 
 * 				которые ссылаются на концы pipe(трубы)
 * 			pipe(fds + 2) -> fds[2] fds[3] будет содержать следующие фд
 * 			
 * 			chld = check_pipe(fds, data); проверка/подмена фд/
 * 			исполнение команды в дочернем процессе
 * 			while (chld-- > 0) ожидание завершения всех дочерних процессов
 * 			после исполнения закрытие всех fds
 * 		закрываем копию открытого фд (std_out) оригинал не будет закрыт
 * **/
void	pipe_or_cmd(t_data **data, int n)
{
	int	fds[4];
	int	std_out;
	int	chld;
	int	i;

	std_out = dup(0);
	i = 0;
	while ((*data)->argv[i] && ft_memcmp((*data)->argv[i], "|", 2))
		i++;
	if (!(*data)->argv[i])
		(*data)->env = check_command((*data)->commands[n], data);
	else if ((*data)->commands[n])
	{
		pipe(fds);
		pipe(fds + 2);
		chld = check_pipe(fds, *data);
		while (chld-- > 0)
			wait(&((*data))->ret);
		(*data)->ret = (*data)->ret / 256;
		i = -1;
		while (++i < 4)
			close(fds[i]);
	}
	dup2(std_out, 0);
}

int	ft_strlen_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}
