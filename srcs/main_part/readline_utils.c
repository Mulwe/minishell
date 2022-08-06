/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:32:30 by joctopus          #+#    #+#             */
/*   Updated: 2022/03/02 09:46:15 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** костыль для readline -_- на Ubuntu**/
/** когда программа стратует запускается первый раз readline
 *  так как ввода нет используем переменую rl_event_hook,
 *  чтобы установить функцию при простое readline().
 * 	она отрабатывает и завершает readline переменной rl_done
 * 
 * тем самым избавляемся от бага переписывания приглашения 
 * при вводе длинной строки во время первого запуска readline 
 * (так как запущен он 2-ой раз)**/

static int	readline_timeout_hook(void)
{
	int	i;

	i = 0;
	while (i < 5)
		i++;
	rl_done = 1;
	return (0);
}

/** первый запуск readline
 * termcap на случай попытки ввода (отключаем визуальный ввод,
 *  затем снова включаем)
 * структура termios (структура termcap)
 * 	c_iflag;		режимы ввода 
 *	c_oflag;		режимы вывода 
 *	c_cflag;		режимы управления
 *	c_lflag;		режимы локали
 *	c_cc[NCCS];		управляющие символы
 * 
 * 	 получить пар-ры и сохранить их в termios структуре
 * 	 выключение отображения ввода символов в терминале
 * 	 применить все изменения сейчас
 * 	  tgetent - получить описание текущего терминала: 
 * **/
inline static void	init_term(struct termios *term)
{
	tcgetattr(0, term);
	term->c_iflag &= ~(ECHO);
	tcsetattr(0, TCSANOW, term);
	tgetent(0, "xterm-256color");
}

/** возвращаем параметры в исходное состояние**/
inline static void	reset_term(struct termios *term)
{
	term->c_iflag |= ECHO;
	tcsetattr(0, TCSANOW, term);
}

void	init_readline(void)
{
	struct termios	term;
	char			*str;

	init_term(&term);
	str = NULL;
	rl_event_hook = readline_timeout_hook;
	str = readline(NULL);
	if (str)
		free(str);
	reset_term(&term);
	rl_event_hook = NULL;
}

void	ft_putstrlen_fd(char *s, int len, int fd)
{
	int	i;

	if (!s || !fd)
		return ;
	i = 0;
	while (s[i] && i < len)
	{
		write(fd, &s[i], 1);
		i++;
	}
}
