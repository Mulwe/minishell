/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 19:27:58 by ojospeh           #+#    #+#             */
/*   Updated: 2022/03/10 01:39:20 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**export_command(t_data *data, int j)
{
	int		i;
	char	**cpy;

	i = 0;
	while (data->env[i] && \
	ft_memcmp(data->env[i], data->argv[j], ft_strlen(data->argv[j])))
		i++;
	if (!data->env[i])
	{
		cpy = copy_env(data->env, 1);
		cpy[i] = ft_strjoin(data->argv[j], data->argv[j + 1]);
		free_mtrx(data->env);
	}
	else
	{
		cpy = data->env;
		free(data->env[i]);
		data->env[i] = ft_strjoin(data->argv[j], data->argv[j + 1]);
	}
	return (cpy);
}

static void	export_variable(t_data **data, int *i)
{
	(*data)->env = export_command(*data, *i);
	if ((*data)->argv[*i + 1])
		*i = *i + 2;
	else
		*i = *i + 1;
}

void	export_value(t_data **data, int *i)
{
	char	**s;
	int		j;

	j = 0;
	s = NULL;
	if (!ft_strchr((*data)->argv[*i], '='))
	{
		j = 0;
		while ((*data)->export[j] && ft_memcmp((*data)->export[j], \
					(*data)->argv[*i], ft_strlen((*data)->argv[*i])))
			j++;
		update_exported_value(data, s, j, i);
		(*i)++;
	}
	else
		export_variable(data, i);
}
