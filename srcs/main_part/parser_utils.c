/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:03:11 by joctopus          #+#    #+#             */
/*   Updated: 2022/02/10 15:21:30 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strlen_env(char *str)
{
	int	len;

	len = 0;
	while (*str && \
	(ft_isalnum(*str) || *str == '{' || *str == '?' || *str == '_'))
	{
		len++;
		str++;
	}
	if (*str == '=')
		len++;
	return (len);
}

void	check_params(char **str, int *i, int *len, int *pos)
{
	*pos = 0;
	if ((*str)[*i + 1] == '{')
		*pos = 1;
	if (char_pos(*str + *i + 1, ':') < strlen_env(*str + *i + 1))
		*len = char_pos(*str + *i + 1, ':') + 1;
	else
		*len = strlen_env(*str + *i + 1) + 1 + *pos;
}

void	del_char(char **str, int i)
{
	char	*s1;
	char	*s2;

	s1 = ft_substr(*str, 0, i);
	s2 = ft_strdup(*str + i + 1);
	free(*str);
	*str = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
}

void	del_backslash(char **arg, int *i)
{
	while ((*arg)[*i])
	{
		if ((*arg)[*i] == '\\' && istoken((*arg)[*i + 1]))
			del_char(arg, *i);
		else if ((*arg)[*i] == '"')
			break ;
		(*i)++;
	}
}

void	del_token(char **arg)
{
	int		i;

	i = 0;
	while ((*arg)[i])
	{
		if ((*arg)[i] == '\'')
		{
			del_char(arg, i);
			i += char_pos(*arg + i, '\'');
			del_char(arg, i);
		}
		else if ((*arg)[i] == '"')
		{
			del_char(arg, i);
			del_backslash(arg, &i);
			del_char(arg, i);
		}
		else if (((*arg)[i] == '\\') && \
		(istoken((*arg)[i + 1]) || (*arg)[i + 1] == '\''))
			del_char(arg, i++);
		else
			i++;
	}
}
