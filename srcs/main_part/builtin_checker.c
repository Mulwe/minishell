/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:41:07 by joctopus          #+#    #+#             */
/*   Updated: 2022/03/09 23:56:10 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ret_value(int ret)
{
	if (ret)
		return (1);
	return (0);
}

/**multiple_env continue**/
static void	export_execution(t_data **data, int *i)
{
	while ((*data)->argv[*i])
	{
		if (ft_strchr((*data)->argv[*i], '#'))
		{
			export_have_comment((*data)->argv, i);
			(*i)++;
			break ;
		}
		else
		{
			if (check_export_error((*data)->argv, i))
				(*data)->ret++;
			else
			{
				if (!ft_memcmp((*data)->argv[0], "export", 7))
					export_value(data, i);
				else if (!ft_memcmp((*data)->argv[0], "unset", 6))
					(*data)->env = unset_command(*data, (*i)++);
			}
		}
	}
}

static char	**multiple_env(t_data **data, int fd)
{
	int	i;

	(*data)->ret = 0;
	if (!ft_memcmp((*data)->argv[0], "export", 7) && (*data)->argc == 1 && \
		(!ft_strlen((*data)->argv[1])))
	{
		sort_env((*data)->env, fd, '=');
		sort_env((*data)->export, fd, 0);
	}
	i = 1;
	export_execution(data, &i);
	(*data)->ret = ret_value((*data)->ret);
	return ((*data)->env);
}

/** ADD BUILTINS | echo | pwd (optional) | cd | **/
static int	is_echo_pwd_cd(int fd, t_data *data)
{
	char	*path;
	char	cwd[4097];

	path = 0;
	if (!ft_memcmp(data->argv[0], "echo", 5))
		echo_command(data, fd);
	else if (!ft_memcmp(data->argv[0], "pwd", 4))
		strs_tofd(getcwd(cwd, 4096), "\n", 0, fd);
	else if (!ft_memcmp(data->argv[0], "cd", 3))
	{
		path = ft_strdup(data->argv[1]);
		cd_command(data);
		if (path && !ft_strncmp(path, "-", 2))
			strs_tofd(getcwd(cwd, 4096), "\n", 0, fd);
		free(path);
	}
	else
		return (1);
	return (0);
}

/**** 127 command not found => ADD BUILTINS
 * check is echo | pwd | cd
 * then check others bultins
 * if not found try bash binaries
 * else set error 127 - command not found
 * **/
int	check_builtins(int fd, t_data **data)
{
	(*data)->ret = 0;
	if (!is_echo_pwd_cd(fd, *data))
		return ((*data)->ret);
	else if (!ft_memcmp((*data)->argv[0], "env", 4))
		env_command((*data), fd);
	else if (!ft_memcmp((*data)->argv[0], "./", 2) || \
			!ft_memcmp((*data)->argv[0], "../", 3) || \
			!ft_memcmp((*data)->argv[0], "/", 1))
		bash_cmd((data));
	else if (!ft_memcmp((*data)->argv[0], "export", 7) || \
			!ft_memcmp((*data)->argv[0], "unset", 6))
		(*data)->env = multiple_env(data, fd);
	else if (!ft_memcmp((*data)->argv[0], "exit", 5) || \
			!ft_memcmp((*data)->argv[0], "q", 2))
		exit_command((*data));
	else
		return (127);
	return ((*data)->ret);
}
