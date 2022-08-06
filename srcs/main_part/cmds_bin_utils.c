/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_bin_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 05:51:34 by joctopus          #+#    #+#             */
/*   Updated: 2022/03/04 19:34:22 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_path(t_data *data, char *str)
{
	char	*path;
	char	**paths;

	path = get_env(data->env, "PATH");
	if (path)
		paths = ft_split_some(path, ':');
	else
	{
		strs_tofd(RED SHL DF, str, ": No such file or directory\n", 2);
		data->ret = 127;
		return (NULL);
	}
	return (paths);
}

int	init_search_bin(char ***paths, int *i, t_data *data, char *str)
{
	(*i) = -1;
	(*paths) = split_path(data, str);
	if (!(*paths))
		return (1);
	return (0);
}

void	show_args(int argc, char **argv)
{
	int		i;

	i = 0;
	while (i < argc)
	{
		printf("argv[%d] '%s'\n", i, argv[i]);
		i++;
	}
}

/** 0 : not empty
 *  1 : str contains only escape chars**/
int	input_empty(char *str)
{
	while (*str)
	{
		if (!is_space(*str))
			return (0);
		str++;
	}
	return (1);
}

/** swap arrays **/
void	swap_mtrxs(t_data **data, char ***arr)
{
	if ((*data)->export)
		free((*data)->export);
	(*data)->export = *arr;
}
