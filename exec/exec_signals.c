/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:46:42 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/10/30 12:15:21 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

int		g_sig = 0;

void	handle_sigint(int sig)
{
	// (void)sig;
	g_sig = sig;
	// printf(">>>>>>> SIG >>> %d\n", g_sig);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void handle_sigint_heredoc(int sig)
{
    (void)sig;
    g_sig = SIGINT;
    write(STDOUT_FILENO, "\n", 1);
    _exit(130); // on tue *immédiatement* l'enfant heredoc avec 130
}

void	handle_sigquit(int sig)
{
	(void)sig;
	// ne fait rien : évite que ^\ imprime "Quit (core dumped)"
}
void	setup_signals_main(void)
{
	struct termios	term;

	// Récupère la configuration du terminal
	tcgetattr(STDIN_FILENO, &term);
	// Désactive l'affichage des caractères de contrôle (ex: ^C, ^\)
	term.c_lflag &= ~ECHOCTL;
	// Applique immédiatement la nouvelle configuration
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
