/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:50:36 by joctopus          #+#    #+#             */
/*   Updated: 2022/03/03 09:09:21 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define NOT_VALID "\': not a valid identifier\n"

int	export_have_comment(char **argv, int *i)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strchr(argv[*i], '#'))
	{
		tmp = ft_substr(argv[*i], 0, ft_strlen(argv[*i]) - \
		ft_strlen(ft_strchr(argv[*i], '#')));
		free(tmp);
		return (1);
	}
	return (0);
}

int	check_export_error(char **argv, int *i)
{
	char	**s;
	int		k;

	s = argv;
	if (ft_isdigit(s[*i][0]) || s[*i][0] == '!' || (s[*i][0] >= '$' && \
	s[*i][0] <= '&') || (s[*i][0] >= ':' && s[*i][0] <= '@') || \
	(s[*i][0] >= '[' && s[*i][0] <= '`') || (s[*i][0] >= '{' \
	&& s[*i][0] <= '~') || (s[*i][0] >= '(' && s[*i][0] <= '/'))
		return (strs_tofd(RED SHL DF "export: \'", s[(*i)++], NOT_VALID, 2));
	k = 1;
	while (s[*i][k] && s[*i][k] != '=')
	{
		if ((s[*i][k] >= '$' && s[*i][k] <= '&') || (s[*i][k] >= ':' && \
		s[*i][k] <= '<') || (s[*i][k] >= '[' && s[*i][k] <= '`') || (s[*i][k] \
		>= '{' && s[*i][k] <= '~') || (s[*i][k] >= '(' && s[*i][k] <= '/') || \
		s[*i][k] == '!')
			return (strs_tofd(RED SHL DF "export: \'", s[(*i)++], NOT_VALID, 2));
		k++;
	}
	return (0);
}

/* int	check_export_error(char **argv, int *i)
{
	int	j;

	j = 0;
	printf("check value\n");
	while (ft_isalnum(argv[*i][j]) || argv[*i][j] == '_' || \
			argv[*i][j] == '#' || argv[*i][j] == '=' || argv[*i][j] == '$')
		j++;
	printf("argv[%d][%d] = %c\n", (*i), j, argv[*i][j]);
	if (ft_isdigit(argv[*i][0]) || argv[*i][j])
	{
		if (ft_strchr(argv[*i], '='))
		{
			strs_tofd(RED SHL DF, argv[0], ": \'", 2);
			strs_tofd(argv[*i], argv[(*i) + 1], NOT_VALID, 2);
			(*i)++;
		}
		else
		{
			strs_tofd(RED SHL DF, argv[0], ": \'", 2);
			strs_tofd(argv[*i], "\': not a valid identifier\n", 0, 2);
		}
		(*i)++;
		return (1);
	}
	return (0);
} */
