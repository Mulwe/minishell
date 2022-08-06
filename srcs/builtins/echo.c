/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:38:45 by joctopus          #+#    #+#             */
/*   Updated: 2022/03/02 05:30:06 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERR_MSG "command must be without arguments or options!\n"

/**
 *  echo -nnnn (не верно работает)
 * 	echo "'" тоже не верно (переписать проверку незакрытых ковычек) 
 *  выводит верно но с сообщением о незакрытых кавычках (не должно так)
 */

static int	is_an_option(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] == '-')
	{
		i = 1;
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

void	echo_command(t_data *data, int fd)
{
	int	i;
	int	offnewline;
	int	ignore;

	init_ints(&i, &offnewline, 0, 0);
	ignore = 0;
	if (data->argc > 1 && is_an_option(data->argv[1]))
		init_ints(&i, &offnewline, 1, 1);
	while (++i < data->argc)
	{
		if (!is_an_option(data->argv[i]) || ignore == 1)
		{
			ft_putstr_fd(data->argv[i], fd);
			if (i < data->argc - 1 && ft_strlen(data->argv[i + 1]))
				write(fd, " ", 1);
			ignore = 1;
		}
	}
	if (offnewline == 0)
		write(fd, "\n", 1);
}

void	env_command(t_data *data, int fd)
{
	int	i;

	i = 0;
	if (data->argc != 1)
	{
		strs_tofd(RED "env: " DF "\'", data->argv[1], "\': " ERR_MSG, 2);
		data->ret = 126;
		return ;
	}
	while (data->env[i])
		strs_tofd(data->env[i++], "\n", 0, fd);
}
