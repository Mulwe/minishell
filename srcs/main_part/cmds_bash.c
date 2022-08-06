/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_bash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 15:10:24 by joctopus          #+#    #+#             */
/*   Updated: 2022/03/04 17:04:27 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_errno(t_data *data, char *str)
{
	if (errno == ENOENT || errno == EACCES)
	{
		strs_tofd(RED SHL DF, str, ": ", 2);
		strs_tofd(strerror(errno), "\n", 0, 2);
		data->ret = 126;
		if (errno == ENOENT)
			data->ret = 127;
		return (1);
	}
	return (0);
}

static void	check_type(t_data **data, char *str, char *path)
{
	DIR		*dir;
	char	**cmds;
	int		fd;

	if (check_errno((*data), str))
		return ;
	dir = opendir(path);
	if (!dir)
	{
		fd = open(path, O_RDONLY, 0666);
		free((*data)->str);
		while (get_next_line(fd, &((*data)->str)))
		{
			cmds = (*data)->commands;
			parser(data);
			(*data)->commands = cmds;
		}
		close(fd);
	}
	else
	{
		strs_tofd(RED SHL DF, str, ": Is a directory\n", 2);
		(*data)->ret = 126;
		closedir(dir);
	}
}

static void	set_filename(int len, char **new, char *str)
{
	int		i;
	char	*filename;
	char	*tmp;

	i = 0;
	while (!ft_memcmp(str + i, "../", 3))
		i = i + 3;
	filename = ft_strdup(str + i);
	i = i / 3;
	while (i-- > 0)
	{
		while ((*new)[len] != '/')
			len--;
		len--;
	}
	tmp = ft_substr(*new, 0, len);
	free(*new);
	*new = ft_strjoin(tmp, "/");
	free(tmp);
	tmp = ft_strjoin(*new, filename);
	free(*new);
	*new = tmp;
	free(filename);
}

void	set_path(char *str, char **path)
{
	int		len;
	char	*new;

	new = ft_strdup(*path);
	len = ft_strlen(*path);
	if (!ft_memcmp(str, "/", 1))
		*path = ft_strdup(str);
	else
	{
		set_filename(len, &new, str);
		*path = new;
		return ;
	}
	free(new);
}

void	bash_cmd(t_data **data)
{
	char	buff[4097];
	char	*path;
	char	*start;
	pid_t	id;

	bash_cmd_init(data, &start, &path, buff);
	id = fork();
	if (id == 0)
	{
		signal(SIGINT, child_sgnl_handler_bash);
		signal(SIGQUIT, child_sigquit_handler);
		if (execve(path, (*data)->argv, (*data)->env))
			check_type(data, start, path);
		exit((*data)->ret);
	}
	waitpid(id, &(*data)->ret, 0);
	if (WIFEXITED((*data)->ret))
		(*data)->ret = WEXITSTATUS((*data)->ret);
	free(path);
	(*data)->argv[0] = start;
}

/* 
start = data->argv[0];
	if (ft_memcmp(data->argv[0], "/", 1))
		if (!ft_memcmp(data->argv[0], "./", 2))
			data->argv[0] += 2;
	path = getcwd(buff, 4096);
	set_path(data->argv[0], &path); */
