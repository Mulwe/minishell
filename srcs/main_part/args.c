/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 07:06:55 by joctopus          #+#    #+#             */
/*   Updated: 2022/02/28 01:43:18 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_chars(char *str, int *i)
{
	if (str[*i] == '>' && str[*i + 1] == '>')
		*i = 2;
	else
		*i = 1;
}

int	strlen_arg_token(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		if (str[i] == '\\' && (str[i + 1] == '"' || str[i + 1] == '\\'))
			i++;
		i++;
	}
	return (i);
}

int	strlen_arg(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '<' || str[i] == '>' || str[i] == '=' || str[i] == '|')
		check_chars(str, &i);
	else
	{
		while (str[i] && !is_space(str[i]) && str[i] != '<' && \
		str[i] != '>' && str[i] != '=' && str[i] != '|')
		{
			if (str[i] == '\'' || str[i] == '"')
			{
				i++;
				i += strlen_arg_token(str + i, str[i - 1]);
				if (!(str[i]))
					return (i);
			}
			i++;
		}
		if (str[i] == '=')
			i++;
	}
	return (i);
}

/**	
 * пропускаем все escapes символы 
 * узнаем длину аргумента
 * копируем с выделением памяти в argv[i] строку str (длины аргументы)
 * обработка аргумента
 * **/
void	set_args(char **argv, char *str, int argc)
{
	int	i;
	int	len;

	i = 0;
	skip_escapes(&str);
	while (i < argc)
	{
		skip_escapes(&str);
		len = strlen_arg(str);
		argv[i] = ft_substr(str, 0, len);
		del_token(&(argv[i]));
		i++;
		str = str + len;
		skip_escapes(&str);
	}
}

char	**copy_args(t_data *data)
{
	int		i;
	char	**args;

	i = 0;
	while (data->argv[i] && ft_memcmp(data->argv[i], "<", 2))
		i++;
	args = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (data->argv[i] && ft_memcmp(data->argv[i], "<", 2))
	{
		args[i] = ft_strdup(data->argv[i]);
		i++;
	}
	return (args);
}
