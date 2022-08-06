/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 06:41:09 by joctopus          #+#    #+#             */
/*   Updated: 2022/03/10 01:41:47 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERR_SYNTAX		"syntax error\n"

static int	unclosed_quotes(char **str, int *i)
{
	(*i)++;
	while ((*str)[*i] && ((*str)[*i] != '\''))
		(*i)++;
	if (!(*str)[*i])
	{
		ft_putstr_fd("Quotes is unclosed\n", 2);
		return (1);
	}
	return (0);
}

/** return new len, len - new position in str (check_env)**/
static int	change_env(int i, int pos, char **str, t_data *data)
{
	int		len;
	char	*before;
	char	*after;
	char	*env;
	char	*s;

	env = 0;
	check_params(str, &i, &len, &pos);
	before = ft_substr(*str, 0, i);
	s = ft_substr(*str, i + 1 + pos, len - 1 - pos * 2);
	if (!ft_memcmp(s, "?", 2))
		env = ft_itoa(data->ret);
	after = ft_strdup(*str + i + len);
	if (!env)
		env = ft_strdup(get_env(data->env, s));
	len = ft_strlen(env);
	free(s);
	s = ft_strjoin(before, env);
	free_strs(before, env, *str);
	*str = ft_strjoin(s, after);
	free(s);
	free(after);
	return (len);
}

static int	check_env(char **str, t_data *data)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while ((*str) && (*str)[i])
	{
		if ((*str)[i] == '\'' && unclosed_quotes(str, &i))
			return (1);
		if ((*str)[i] && (*str)[i] == '\\')
		{
			if ((*str)[i + 1] == '$')
				del_char(str, i);
			if ((*str)[i + 1])
				i++;
		}
		else if ((*str)[i] == '$' && !(!(*str)[i + 1] ||
		is_space((*str)[i + 1]) || (*str)[i + 1] == '\'' ||
		(*str)[i + 1] == '"' || (*str)[i + 1] == '/'))
			i = i + change_env(i, pos, str, data) - 1;
		i++;
	}
	return (0);
}

static void	parser_err_syntax(t_data *data)
{
	ft_putstr_fd(RED SHL DF ERR_SYNTAX, 2);
	free_mtrx(data->argv);
}

/**
 * проверка на ; 
 * (лишнее срабатывание при "'")
 * todo: разные проверки для закрытости кавычек ( "'" не должно срабатывать)
 * 		: провекрка на	';'		';;'	'|'		'||'	(в начале команды)
 * **/
void	parser(t_data **data)
{
	int	i;

	if (pre_parser((*data)))
		return ;
	(*data)->commands = ft_split_some((*data)->str, ';');
	i = 0;
	while ((*data)->commands[i])
	{
		check_env(&((*data)->commands[i]), *data);
		(*data)->argc = count_args((*data)->commands[i]);
		(*data)->argv = (char **)ft_calloc(sizeof(char *), ((*data)->argc + 1));
		set_args((*data)->argv, (*data)->commands[i], (*data)->argc);
		if (i < 0 && wrong_delimeters((*data)->argc, (*data)->argv))
		{
			parser_err_syntax((*data));
			break ;
		}
		pipe_or_cmd(data, i);
		i++;
		free_mtrx((*data)->argv);
	}
	free((*data)->str);
	(*data)->str = 0;
	free_mtrx((*data)->commands);
}
