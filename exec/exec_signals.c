/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:46:42 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/10/22 14:09:06 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
void	handle_sigquit(int sig)
{
	(void)sig;
	// ne fait rien : évite que ^\ imprime "Quit (core dumped)"
}
void	setup_signals_main(void)
{
	struct termios term;

	// Récupère la configuration du terminal
	tcgetattr(STDIN_FILENO, &term);

	// Désactive l'affichage des caractères de contrôle (ex: ^C, ^\)
	term.c_lflag &= ~ECHOCTL;

	// Applique immédiatement la nouvelle configuration
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	
	signal(SIGINT,handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
