/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:02:50 by joctopus          #+#    #+#             */
/*   Updated: 2022/03/04 15:38:58 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**erase_env(char **envp, int i)
{
	int		j;
	int		len;
	char	**cpy;

	len = 0;
	while (envp[len])
		len++;
	cpy = (char **)ft_calloc(sizeof(char *), len);
	if (!cpy)
		return (NULL);
	j = -1;
	while (++j < i)
		cpy[j] = ft_strdup(envp[j]);
	i++;
	while (envp[i])
		cpy[j++] = ft_strdup(envp[i++]);
	free_mtrx(envp);
	return (cpy);
}

static void	unset_alone_declared(t_data **data, char *env)
{
	int		i;
	char	**tmp;

	i = 0;
	while ((*data)->export[i] && ft_strcmp((*data)->export[i], env) != 0)
		i++;
	if ((*data)->export[i])
	{
		tmp = erase_env((*data)->export, i);
		(*data)->export = tmp;
	}
}

char	**unset_command(t_data *data, int j)
{
	int		i;
	int		len;
	char	*env;
	char	**cpy;

	if (data->argc < 2)
		return (data->env);
	len = ft_strlen(data->argv[j]);
	env = ft_strjoin(data->argv[j], "=");
	unset_alone_declared(&data, env);
	i = 0;
	while (data->env[i] && ft_memcmp(env, data->env[i], len + 1))
		i++;
	if (data->env[i])
		cpy = erase_env(data->env, i);
	else
		cpy = data->env;
	free(env);
	return (cpy);
}

static void	put_env(char **s, int fd)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstrlen_fd(s[i], ft_strlen_char(s[i], '=') + 1, fd);
		if (ft_strchr(s[i], '='))
			strs_tofd("\"", ft_strchr(s[i], '=') + 1, "\"", fd);
		write(fd, "\n", 1);
	}
	free_mtrx(s);
}

void	sort_env(char **env, int fd, char c)
{
	int		i;
	int		len;
	char	**s;
	char	*tmp;

	s = copy_env(env, 0);
	i = 0;
	while (s[i] && s[i + 1])
	{
		if (ft_strlen_char(s[i], c) > ft_strlen_char(s[i + 1], c))
			len = ft_strlen_char(s[i], c);
		else
			len = ft_strlen_char(s[i + 1], c);
		if (ft_memcmp(s[i], s[i + 1], len) > 0)
		{
			tmp = s[i];
			s[i] = s[i + 1];
			s[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
	put_env(s, fd);
}
