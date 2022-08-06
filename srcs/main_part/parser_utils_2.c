/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 18:30:56 by joctopus          #+#    #+#             */
/*   Updated: 2022/03/01 03:24:30 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERR_SEMI				"syntax error near unexpected token `;'\n"
#define ERR_DOUBLE_SEMI			"syntax error near unexpected token `;;'\n"
#define ERR_ALONE_PIPE			"syntax error near unexpected token `|'\n"
#define ERR_ALONE_DOUBLE_PIPE	"syntax error near unexpected token `||'\n"
#define ERR_NEWLINE				"syntax error near unexpected token `newline'\n"
#define ERR_ONE_HEREDOC			"syntax error near unexpected token `<'\n"
#define ERR_ONE_REDIR			"syntax error near unexpected token `>'\n"

/**	переписать под несколько кавыек
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
}	char (*f)(unsigned int, char)
**/

static int	str2fd(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	return (1);
}

/** sytax err when ; ;; | ||  heredoc << **/
static int	check_begin(char *str)
{
	skip_escapes(&str);
	if (ft_strlen(str) > 1 && !ft_strncmp(str, "||", 3))
		return (str2fd(RED SHL DF ERR_ALONE_DOUBLE_PIPE, 2));
	if (ft_strlen(str) > 1 && !ft_strncmp(str, ";;", 3))
		return (str2fd(RED SHL DF ERR_DOUBLE_SEMI, 2));
	if (!ft_memcmp(str, "|", 2) || str[0] == '|')
		return (str2fd(RED SHL DF ERR_ALONE_PIPE, 2));
	if (!ft_memcmp(str, ";", 2) || str[0] == ';')
		return (str2fd(RED SHL DF ERR_SEMI, 2));
	if ((ft_strlen(str) > 1 && !ft_strncmp(str, "<<", 3)) || \
	(!ft_memcmp(str, "<", 2) || str[0] == '<'))
		return (str2fd(RED SHL DF ERR_NEWLINE, 2));
	if (ft_strlen(str) > 1 && !ft_strncmp(str, "<<<<", 5))
		return (str2fd(RED SHL DF ERR_ONE_HEREDOC, 2));
	if (ft_strlen(str) > 1 && !ft_strncmp(str, ">>>", 4))
		return (str2fd(RED SHL DF ERR_ONE_REDIR, 2));
	if (ft_strlen(str) > 1 && ft_strlen(str) < 3 && !ft_strncmp(str, ">>", 3))
		return (str2fd(RED SHL DF ERR_NEWLINE, 2));
	if (ft_strlen(str) == 1 && !ft_memcmp(str, ">", 2))
		return (str2fd(RED SHL DF ERR_NEWLINE, 2));
	return (0);
}

/**проверка на кавычки и прочее на незакрытый пайп на незакрытое '/' **/
/* int	split_str()
{
	
} */

/**
	 * не забыть проверить что строка не NULL
	 * if 1 ret = 2; free(data) return 1
	 * ! добавить проверку на закрытость/незакрытость
	 * **/
int	pre_parser(t_data *data)
{
	if (!data->str || check_begin(data->str))
	{
		if (data->str)
		{
			free(data->str);
			data->str = 0;
			data->ret = 2;
		}
		return (1);
	}
	return (0);
}

static int	is_delimiter(char **argv, int i)
{
	int		pos;

	pos = 0;
	if (ft_strlen(argv[i]) > 1 && \
		(!ft_strncmp(argv[i], "<<", 3) || !ft_strncmp(argv[i], "||", 3) \
		|| !ft_strncmp(argv[i], ">>", 3) || \
		!ft_strncmp(argv[i], ";;", 3)))
		pos = 1;
	else if (!ft_memcmp(argv[i], ">", 2) || !ft_memcmp(argv[i], "|", 2) || \
		!ft_memcmp(argv[i], "<", 2) || !ft_strncmp(argv[i], ";", 2))
		pos = 1;
	return (pos);
}

int	wrong_delimeters(int argc, char **argv)
{
	int	i;
	int	delimiter;

	init_ints(&delimiter, &i, 0, 0);
	if (!argv || !argv[0])
		return (0);
	while (i < argc)
	{
		if (i < argc && is_delimiter(argv, i))
			delimiter++;
		if ((argc % 2 == 0) && (delimiter > argc / 2))
			return (1);
		if ((argc % 2 != 0) && argc > 2 && (delimiter > argc / 2))
			return (1);
		i++;
	}
	if ((argc % 2 == 0) && (delimiter == argc / 2) && \
	(!ft_strncmp(argv[0], ">>", 3) || !ft_strncmp(argv[0], "<<", 3) || \
	!ft_strncmp(argv[0], ">", 2) || !ft_strncmp(argv[0], "<", 2)))
		return (0);
	if ((argc % 2 != 0) && delimiter != (argc / 2))
		return (1);
	return (0);
}
