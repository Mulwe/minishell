/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 06:29:04 by joctopus          #+#    #+#             */
/*   Updated: 2022/03/03 11:11:54 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(char *str)
{
	int	n;

	n = 0;
	skip_escapes(&str);
	while (*str)
	{
		skip_escapes(&str);
		n++;
		str += strlen_arg(str);
		skip_escapes(&str);
	}
	return (n);
}

int	char_pos(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

void	free_mtrx(char **mtrx)
{
	int	i;

	i = 0;
	if (!mtrx)
		return ;
	while (mtrx[i])
		free(mtrx[i++]);
	free(mtrx);
	mtrx = NULL;
}

void	init_ints(int *y, int *z, int y_value, int z_value)
{
	*y = y_value;
	*z = z_value;
}

int	inc_cmd(char **argv, int i)
{
	int		cmd;
	char	*tmp;

	tmp = argv[i];
	skip_escapes(&tmp);
	cmd = 0;
	if (ft_strlen(tmp) == 0)
		cmd = 0;
	else if (ft_strlen(argv[i]) > 1 && \
		(!ft_strncmp(argv[i], "<<", 3) || !ft_strncmp(argv[i], "||", 3) \
		|| (i > 0 && ft_strncmp(argv[i], ">>", 2))))
		cmd = 0;
	else if (!ft_strncmp(argv[i], ";;", 3))
		cmd = 0;
	else if (!ft_memcmp(argv[i], ">", 2) || !ft_memcmp(argv[i], "|", 2) || \
		(i > 0 && !ft_memcmp(argv[i], "<", 2)) || !ft_strncmp(argv[i], ";", 3))
		cmd = 0;
	else
		cmd = 1;
	return (cmd);
}
