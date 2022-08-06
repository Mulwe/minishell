/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 03:25:40 by joctopus          #+#    #+#             */
/*   Updated: 2022/03/04 18:21:45 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char **envp, char *env)
{
	int		i;
	int		len;
	char	*tmp;

	env = ft_strjoin(env, "=");
	len = ft_strlen(env);
	i = 0;
	while (envp[i] && ft_memcmp(env, envp[i], len))
		i++;
	if (envp[i])
		tmp = envp[i] + len;
	else
		tmp = 0;
	free(env);
	return (tmp);
}

char	**copy_env(char **envp, int add)
{
	int		len;
	int		i;
	char	**cpy;

	len = 0;
	while (envp[len])
		len++;
	cpy = (char **)ft_calloc(sizeof(char *), (len + add + 1));
	if (!cpy)
		return (0);
	i = -1;
	while (++i < len)
		cpy[i] = ft_strdup(envp[i]);
	return (cpy);
}

/**	' ' '\t' '\n' '\v' '\f' '\r' **/
int	is_space(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

void	ft_addchar(char **str, char c)
{
	char	*tmp;

	tmp = ft_calloc(sizeof(char), ft_strlen(*str) + 2);
	ft_memcpy(tmp, *str, ft_strlen(*str));
	tmp[ft_strlen(tmp)] = c;
	if (*str)
		free(*str);
	*str = tmp;
}

void	skip_escapes(char **str)
{
	while (**str == ' ' || ('\t' <= **str && **str <= '\r'))
		(*str)++;
}
