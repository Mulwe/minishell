/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 13:54:10 by joctopus          #+#    #+#             */
/*   Updated: 2022/02/28 02:51:42 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_reading(int *fd, int *ret, char *c)
{
	*ret = read(*fd, c, 1);
	while (*ret)
	{
		if (*ret == -1)
		{
			write(2, "Couldn't read file\n", 19);
			break ;
		}
		*ret = read(*fd, c, 1);
	}
}

int	redirect(t_data *data, int i, int fd)
{
	int		ret;
	char	c;

	while (data->argv[i])
	{
		if (!ft_memcmp(data->argv[i], ">", 2))
			fd = open(data->argv[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
		else if (!ft_memcmp(data->argv[i], ">>", 3))
		{
			fd = open(data->argv[i + 1], O_RDWR | O_CREAT | O_APPEND, 0666);
			ret = 0;
			redirect_reading(&fd, &ret, &c);
		}
		i++;
		if (data->argv[i] && (!ft_memcmp(data->argv[i], ">>", 3) || \
		!ft_memcmp(data->argv[i], ">", 2)))
			close(fd);
	}
	return (fd);
}

static void	set_in(char **argv)
{
	int		fd;
	int		i;

	i = 0;
	while (argv[i] && ft_memcmp(argv[i], "<", 2))
		i++;
	if (argv[i])
	{
		fd = open(argv[i + 1], O_RDONLY, 0666);
		if (fd < 0)
		{
			ft_putstr_fd("Couldn't read from file.\n", 2);
			return ;
		}
		dup2(fd, 0);
		close(fd);
	}
}

inline static void	wait_process(t_data **d, pid_t id, \
char **path, char **args)
{
	waitpid(id, &((*d)->ret), 0);
	if (WIFEXITED((*d)->ret))
		(*d)->ret = WEXITSTATUS((*d)->ret);
	free(*path);
	free_mtrx(args);
}

/**	cmds_bin.c 
 * check_bin() part **/
void	exec_bin(int fd, char *path, t_data *data)
{
	char	**args;
	pid_t	id;

	args = copy_args(data);
	signal(SIGINT, child_sgnl_handler);
	id = fork();
	if (id == 0)
	{
		signal(SIGQUIT, child_sigquit_handler);
		set_in(data->argv);
		if (fd > 1)
			dup2(fd, 1);
		if ((execve(path, args, data->env)) && errno == EACCES)
		{
			data->ret = 126;
			strs_tofd(RED SHL DF, data->argv[0], ": ", 2);
			strs_tofd(strerror(errno), "\n", 0, 2);
		}
		exit(data->ret);
	}
	wait_process(&data, id, &path, args);
}
