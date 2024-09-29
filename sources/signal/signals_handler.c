/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapuis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:40:03 by gabarnou          #+#    #+#             */
/*   Updated: 2024/09/29 17:39:37 by echapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrlc_shell_wait(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handler_wait(void)
{
	struct sigaction	act;

	sigquit_disapear();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &ctrlc_shell_wait;
	sigaction(SIGINT, &act, NULL);
}

void	new_line(int sig)
{
	(void)sig;
	rl_on_new_line();
}

void	signal_handler_run(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &new_line;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

void	sigquit_disapear(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}
