/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 12:44:14 by joctopus          #+#    #+#             */
/*   Updated: 2022/03/04 18:03:57 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** serach_bin part**/
static char	*bin_found(char **paths, char *path, int i)
{
	path = ft_strjoin(paths[i], "/");
	free_mtrx(paths);
	return (path);
}

/** loking for binary 
 *  EACCESS 13 - permision denied (for errno)
 * 
 *  check every paths, while not found one that opens,
 *  modify path and return path string
 *  if not found then close dir and free all stuff
 * **/
static char	*search_bin(char *str, DIR **dir, struct dirent **d, t_data *data)
{
	char	**paths;
	char	*path;
	int		i;

	path = NULL;
	paths = NULL;
	if (init_search_bin(&paths, &i, data, str))
		return (NULL);
	while (paths[++i])
	{
		*dir = opendir(paths[i]);
		if (*dir == NULL)
			break ;
		*d = readdir(*dir);
		while ((*dir) && errno != EACCES && (*d))
		{
			if (!ft_memcmp(str, (*d)->d_name, ft_strlen(str) + 1))
				return (bin_found(paths, path, i));
			if ((*dir))
				*d = readdir(*dir);
		}
		closedir(*dir);
	}
	free_mtrx(paths);
	return (NULL);
}

/** working with binaries **/
int	check_bin(int fd, t_data *data)
{
	DIR				*dir;
	struct dirent	*d;
	char			*front_path;
	char			*path;

	data->ret = 127;
	front_path = search_bin(data->argv[0], &dir, &d, data);
	if (front_path)
	{
		path = ft_strjoin(front_path, d->d_name);
		exec_bin(fd, path, data);
		closedir(dir);
	}
	free(front_path);
	return (data->ret);
}

/** short cut **/
void	bash_cmd_init(t_data **data, char **start, char **path, char *buff)
{
	(*start) = (*data)->argv[0];
	if (ft_memcmp((*data)->argv[0], "/", 1))
		if (!ft_memcmp((*data)->argv[0], "./", 2))
			(*data)->argv[0] += 2;
	(*path) = getcwd(buff, 4096);
	set_path((*data)->argv[0], path);
}

/****/
void	null_export(char **tmp)
{
	tmp = (char **)malloc(sizeof(char *) * 1);
	tmp[0] = ft_strdup("");
}
