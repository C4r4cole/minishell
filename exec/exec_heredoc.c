/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:37:47 by fmoulin           #+#    #+#             */
/*   Updated: 2025/10/29 16:56:47 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

int	handle_heredoc(char *end_word)
{
	pid_t	pid;
	int		fd[2];
	int		status;
		char *line;

	if (pipe(fd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), close(fd[0]), close(fd[1]), -1);
	if (pid == 0)
	{
		// ----- CHILD (saisie heredoc) -----
		signal(SIGINT, handle_sigint_heredoc); // Ctrl-C => exit(130)
		signal(SIGQUIT, SIG_IGN);
		close(fd[0]); // on n’écrit que sur fd[1]
		while (1)
		{
			line = readline("heredoc> ");
			if (!line)
				// EOF (Ctrl-D) ou SIGINT (mais on a déjà _exit(130) dans le handler)
				break ;
			if (ft_strcmp(line, end_word) == 0)
			{
				free(line);
				break ;
			}
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
		close(fd[1]);
		_exit(0); // fin normale
	}
	// ----- PARENT -----
	signal(SIGINT, SIG_IGN); // ignore Ctrl-C pendant la saisie heredoc
	close(fd[1]);            // ne garde que la lecture
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_sigint); // rétablit le handler normal du shell
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(fd[0]); // on ferme le tube, on annule
		return (-1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		close(fd[0]);
		return (-1);
	}
	return (fd[0]); // OK : on renvoie le fd de lecture du contenu
}

int	heredoc_before_fork(t_cmd *cmd)
{
	t_redir	*r;
	int		fd;

	r = cmd->redir;
	while (r)
	{
		if (r->type == HEREDOC)
		{
			fd = handle_heredoc(r->file);
			if (fd == -1) // <- Ctrl-C détecté ici
				return (-1);
			r->heredoc_fd = fd;
		}
		r = r->next;
	}
	return (0);
}
