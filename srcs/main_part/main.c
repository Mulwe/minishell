/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:43:23 by joctopus          #+#    #+#             */
/*   Updated: 2022/03/11 05:39:27 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** pre-initialization
 * allocating memory for the structure
 * env		- (copied envp from main)
 * export	- an empty array (with allocated memory)
 * argv		- exact duplicate of the argv from main()
 * ret		- byte quantity have been read from read/readline
 * str		- empty at first
 * child	- id child process (empty at first)
 * ret[]	- needed to shell_run
 * **/

static void	init_data(t_data **data, char **argv, char **envp)
{
	(*data) = (t_data *)malloc(sizeof(t_data));
	(*data)->env = copy_env(envp, 0);
	(*data)->export = (char **)ft_calloc(sizeof(char *), 1);
	(*data)->argv = argv;
	(*data)->ret = 0;
	(*data)->str = 0;
	(*data)->child = 0;
	init_readline();
	(*data)->promt = NULL;
}

/**
 * 		ret_len[0]	- quantity input bytes.
 * 			if > 0 && c != \n 
 * 			- char is  adding to  **data->str (in the loop)
 * 
 * 		ret_len[1]	- length of resulting string (0 at first)
 * 
 * 		If the previous cycle was interrupted, we check ('c' == \n) - 
 * 		for case reaching the end of the line launching the parser.
 * 
 * 		if !ret_len[0] && !ret_len[1] - exit shell
 *  */

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;

	if (argc != 1)
		return (1);
	signal(SIGINT, shell_sigint_handler);
	signal(SIGQUIT, shell_sigquit_handler);
	init_data(&data, argv, envp);
	readline_input(&data);
	return (0);
}
