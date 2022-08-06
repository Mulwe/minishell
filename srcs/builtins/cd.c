/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:20:12 by joctopus          #+#    #+#             */
/*   Updated: 2022/03/01 01:25:34 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_dir(char *path, t_data *data)
{
	char	cwd[4097];
	char	oldpwd[4097];

	getcwd(oldpwd, 4096);
	if (chdir(path) == 0)
	{
		data->argc = 4;
		free_mtrx(data->argv);
		data->argv = (char **)ft_calloc(sizeof(char *), 4);
		data->argv[0] = ft_strdup("export");
		data->argv[1] = ft_strdup("OLDPWD=");
		data->argv[2] = ft_strdup(oldpwd);
		data->env = export_command(data, 1);
		free_mtrx(data->argv);
		data->argv = (char **)ft_calloc(sizeof(char *), 4);
		data->argv[0] = ft_strdup("export");
		data->argv[1] = ft_strdup("PWD=");
		data->argv[2] = ft_strdup(getcwd(cwd, 4096));
		data->env = export_command(data, 1);
	}
	else
		strs_tofd(SHL "cd: ", data->argv[1], ": ", 2);
}

void	cd_command(t_data *data)
{
	char	*path;

	errno = 0;
	if (data->argc <= 2)
	{
		if (!data->argv[1] || !ft_strncmp(data->argv[1], "--", 3) || \
			!ft_strncmp(data->argv[1], "~", 2))
			path = get_env(data->env, "HOME");
		else if (!ft_strncmp(data->argv[1], "-", 2))
			path = get_env(data->env, "OLDPWD");
		else
			path = data->argv[1];
		change_dir(path, data);
		if (errno > 0)
		{
			strs_tofd(strerror(errno), "\n", 0, 2);
			data->ret = 1;
		}
	}
	else
	{
		ft_putstr_fd(RED SHL DF "cd: too many arguments\n", 2);
		data->ret = 1;
	}
	errno = 0;
}
