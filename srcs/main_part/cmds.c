/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:32:14 by joctopus          #+#    #+#             */
/*   Updated: 2022/03/04 17:04:56 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_fd(t_data *data)
{
	int		i;
	int		fd;

	i = 0;
	fd = 1;
	while (data->argv[i] && ft_memcmp(data->argv[i], ">", 2) \
	&& ft_memcmp(data->argv[i], ">>", 3))
		i++;
	if (!data->argv[i])
		return (1);
	return (redirect(data, i, fd));
}

static int	count_redir(t_data *data)
{
	int	count;
	int	i;

	i = -1;
	count = 0;
	while (++i < data->argc)
	{
		if (!ft_memcmp(data->argv[i], ">", 2) || \
		!ft_memcmp(data->argv[i], ">>", 3))
		{
			count++;
			i++;
		}
	}
	return (count);
}

static void	copy_args1(t_data *data)
{
	int		i;
	int		j;
	char	**args;

	data->argc = data->argc - count_redir(data) * 2;
	args = (char **)ft_calloc(sizeof(char *), data->argc + 1);
	i = 0;
	j = 0;
	while (j < data->argc)
	{
		if (!ft_memcmp(data->argv[i], ">", 2) || \
			!ft_memcmp(data->argv[i], ">>", 3))
			i += 2;
		else
			args[j++] = ft_strdup(data->argv[i++]);
	}
	free_mtrx(data->argv);
	data->argv = args;
}

/** 127 -> command not found**/
char	**check_command(char *str, t_data **data)
{
	int	fd;

	if ((*data)->argv[0] && *((*data)->argv[0]))
	{
		fd = set_fd((*data));
		if (!ft_strncmp((*data)->argv[0], ">>", 3) \
		|| !ft_strncmp((*data)->argv[0], ">", 2))
		{
			close(fd);
			return ((*data)->env);
		}
		copy_args1(*data);
		(*data)->ret = check_builtins(fd, data);
		if ((*data)->ret == 127)
		{
			(*data)->ret = check_bin(fd, *data);
			if ((*data)->ret == 127)
				strs_tofd(RED SHL DF, str, ": command not found.\n", 2);
		}
		if (fd != 1)
			close(fd);
	}
	return ((*data)->env);
}

void	free_strs(char *str1, char *str2, char *str3)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (str3)
		free(str3);
}
