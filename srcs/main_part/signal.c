/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 05:52:41 by joctopus          #+#    #+#             */
/*   Updated: 2022/02/28 02:53:48 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_sgnl_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
	}
}

void	child_sgnl_handler_bash(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		exit(0);
	}
}

/** SIGINT обработчик (нажатие Ctrl+C)
 * переход на новую строку
 * востановление приглашение на новой линии
 * **/
void	shell_sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/**	write(2, "\b\b  \b\b", 6);  rabotaet Ubuntu**/
void	shell_sigquit_handler(int sig)
{
	if (sig == SIGQUIT)
		write(2, "\b\b  \b\b", 6);
}

void	child_sigquit_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		write(2, "\n", 1);
		write(2, "Quit (core dumped)\n", 20);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit(131);
	}
}
