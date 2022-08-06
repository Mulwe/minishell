/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 19:27:58 by ojospeh           #+#    #+#             */
/*   Updated: 2022/03/10 01:40:23 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_exported_value(t_data **data, char **s, int j, int *i)
{
	if (!(*data)->export[j])
	{
		s = copy_env((*data)->export, 1);
		s[j] = ft_strdup((*data)->argv[*i]);
		s[j + 1] = 0;
		free_mtrx((*data)->export);
		(*data)->export = s;
	}
}
