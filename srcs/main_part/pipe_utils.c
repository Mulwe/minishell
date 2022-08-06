/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:55:19 by joctopus          #+#    #+#             */
/*   Updated: 2022/02/23 19:29:09 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	switch_pipes(int *fds)
{
	close(fds[0]);
	close(fds[1]);
	fds[0] = fds[2];
	fds[1] = fds[3];
	pipe(fds + 2);
}

int	switch_flag(t_data *data, int i, int j)
{
	if (!data->argv[i + j])
		return (1);
	else
		return (0);
}

void	init_check_pipe(int *chlds, int **flag, int *j)
{
	*chlds = 0;
	(*flag) = (int *)malloc(sizeof(int) * 2);
	(*flag)[0] = 1;
	(*flag)[1] = 0;
	*j = 0;
}

/** extra utils **/

int	istoken(char c)
{
	if (c == '"' || c == '\\')
		return (1);
	return (0);
}

/** output utils**/
int	strs_tofd(char *first, char *second, char *third, int fd)
{
	if (first)
		write(fd, first, ft_strlen(first));
	if (second)
		write(fd, second, ft_strlen(second));
	if (third)
		write(fd, third, ft_strlen(third));
	return (1);
}
