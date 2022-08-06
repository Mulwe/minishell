/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:21:27 by joctopus          #+#    #+#             */
/*   Updated: 2022/03/02 05:30:47 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define NOT_NBR ": numeric argument required\n"

static void	free_data(t_data *data)
{
	free(data->str);
	free_mtrx(data->env);
	free_mtrx(data->export);
	free_mtrx(data->argv);
	free_mtrx(data->commands);
	free(data);
}

void	exit_command(t_data *data)
{
	int	i;

	if (data->argc > 2)
	{
		strs_tofd("exit\n", RED SHL DF, "exit: too many arguments\n", 2);
		data->ret = 1;
	}
	else
	{
		i = 0;
		while (data->argc > 1 && ft_isdigit(data->argv[1][i]))
			i++;
		if (data->argc > 1 && data->argv[1][i])
		{
			strs_tofd("exit\n" RED SHL DF "exit: ", data->argv[1], NOT_NBR, 2);
			data->ret = 2;
		}
		i = data->ret;
		if (data->argc > 1 && data->ret != 2)
			i = ft_atoi(data->argv[1]);
		free_data(data);
		exit(i);
	}
}
