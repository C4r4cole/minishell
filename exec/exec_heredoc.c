/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:37:47 by fmoulin           #+#    #+#             */
/*   Updated: 2025/10/29 15:37:43 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

char	**env_to_tab(t_env *env)
{
	t_env	*tmp;
	char	**tab;
	int		count;
	int		i;
	char	*tmp2;

	count = 0;
	i = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	while (env)
	{
		tmp2 = ft_strjoin("=", env->value);
		tab[i] = ft_strjoin(env->key, tmp2);
		free(tmp2);
		i++;
		env = env->next;
	}
	tab[i] = NULL;
	return (tab);
}

int	handle_heredoc(char *end_word)
{
	pid_t	pid;
	int		fd[2];
	char	*line;
	int		status;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, handle_sigint_heredoc); // Ctrl-C arrête juste le heredoc
		signal(SIGQUIT, SIG_IGN);
		close(fd[0]); // on écrit seulement
		while (1)
		{
			line = readline("heredoc> ");
			if (!line || ft_strcmp(line, end_word) == 0)
				break ;
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
		free(line);
		close(fd[1]);
		exit(0);
	}
	signal(SIGINT, SIG_IGN); // parent ignore signal pendant heredoc
	close(fd[1]);            // parent lit seulement
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_sigint_heredoc); // rétablir après heredoc
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (-1); // heredoc annulé par Ctrl-C
	return (fd[0]);  // retourne le fd de lecture
}

int	heredoc_before_fork(t_cmd *arg)
{
	t_redir	*redir;
	int		fd;

	redir = arg->redir;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			fd = handle_heredoc(redir->file);
			if (fd < 0)
				return (1); // si Ctrl-C pendant heredoc → on arrête la commande
			redir->heredoc_fd = fd;
		}
		redir = redir->next;
	}
	return (0);
}
