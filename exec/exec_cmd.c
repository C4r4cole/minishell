/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:27:10 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/10/29 10:13:41 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

int	exec_one_cmd(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	*path;

	path = find_path(cmd, shell);
	// Si find_path a échoué → on ne fork pas !
	if (!path)
		return (shell->exit_status);
	// Créer un processus enfant
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0) // ---- CHILD ----
	{
		// Remet les signaux par défaut pour exec
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		// Appliquer redirections
		if (cmd->redir)
			execute_redirections_cmds(cmd); // exit(1) dedans si erreur
		// Exécuter la commande
		execve(path, cmd->argv, shell->envp);
		perror("execve"); // si execve échoue
		exit(126);
	}
	// ---- PARENT ----
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
	free(path);
	return (shell->exit_status);
}

int	execute_cmds_list(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*current;
	t_cmd	*tmp;
	pid_t	pid;
	int		status;

	if (cmds->next) // s'il y a un pipe -> on délègue
		return (execute_piped_cmds(cmds, shell));
	current = cmds;
	tmp = cmds;
	while (tmp)
	{
		if (heredoc_before_fork(tmp))
			return (1);
		tmp = tmp->next;
	}
	while (current)
	{
		// ---------- BUILTINS sans redirection ----------
		if (!current->redir && (!ft_strcmp(current->argv[0], "echo")
				|| !ft_strcmp(current->argv[0], "pwd")
				|| !ft_strcmp(current->argv[0], "env")))
		{
			if (!ft_strcmp(current->argv[0], "echo"))
				shell->exit_status = ft_echo(current->argv);
			else if (!ft_strcmp(current->argv[0], "pwd"))
				shell->exit_status = ft_pwd(shell);
			else
				shell->exit_status = ft_env(shell);
		}
		// ---------- BUILTINS avec redirections ----------
		else if (current->redir && (!ft_strcmp(current->argv[0], "echo")
				|| !ft_strcmp(current->argv[0], "pwd")
				|| !ft_strcmp(current->argv[0], "env")))
		{
			pid = fork();
			if (pid == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				if (execute_redirections_builtins(current->redir))
					exit(1);
				if (!ft_strcmp(current->argv[0], "echo"))
					exit(ft_echo(current->argv));
				else if (!ft_strcmp(current->argv[0], "pwd"))
					exit(ft_pwd(shell));
				else
					exit(ft_env(shell));
			}
			waitpid(pid, &status, 0);
			shell->exit_status = WEXITSTATUS(status);
		}
		// ---------- BUILTINS : export, unset, cd, exit ----------
		else if (!ft_strcmp(current->argv[0], "cd")
			|| !ft_strcmp(current->argv[0], "export")
			|| !ft_strcmp(current->argv[0], "unset")
			|| !ft_strcmp(current->argv[0], "exit"))
		{
			if (!ft_strcmp(current->argv[0], "cd"))
				shell->exit_status = ft_cd(current->argv, shell);
			else if (!ft_strcmp(current->argv[0], "export"))
				shell->exit_status = ft_export(current->argv, shell);
			else if (!ft_strcmp(current->argv[0], "unset"))
				shell->exit_status = ft_unset(current->argv, shell);
			else if (!ft_strcmp(current->argv[0], "exit"))
				shell->exit_status = ft_exit(current->argv, shell);
		}
		// ---------- Commande externe ----------
		else
		{
			shell->exit_status = exec_one_cmd(current, shell);
		}
		current = current->next;
	}
	return (shell->exit_status);
}

int	execute_piped_cmds(t_cmd *cmds, t_shell *shell)
{
	int		fd[2];
	int		in_fd;
	pid_t	pid;
	pid_t	last_pid;
	int		status;
	char	*path;
	pid_t	w;

	in_fd = -1;
	last_pid = -1;
	signal(SIGPIPE, SIG_IGN);
	shell->in_pipe = 1;
	while (cmds)
	{
		if (cmds->next && pipe(fd) == -1)
			return (perror("pipe"), 1);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 1);
		if (pid == 0) // ---- CHILD ----
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			// stdin ← pipe précédent ?
			if (in_fd != -1)
			{
				if (dup2(in_fd, STDIN_FILENO) == -1)
					(perror("dup2 in"), exit(1));
				close(in_fd);
			}
			// stdout → pipe suivant ?
			if (cmds->next)
			{
				close(fd[0]);
				if (dup2(fd[1], STDOUT_FILENO) == -1)
					(perror("dup2 out"), exit(1));
				close(fd[1]);
			}
			// redirections fichier (appliquées en plus du piping)
			if (cmds->redir)
				execute_redirections_cmds(cmds);
			// doit exit(1) en cas d'échec d’open/dup2
			// builtins interdits dans un pipe (pas d’effet → exit 1 comme bash)
			if (!ft_strcmp(cmds->argv[0], "export") || !ft_strcmp(cmds->argv[0],
					"unset") || !ft_strcmp(cmds->argv[0], "cd")
				|| !ft_strcmp(cmds->argv[0], "exit"))
				exit(1);
			// builtins simples OK dans un pipe
			if (!ft_strcmp(cmds->argv[0], "echo"))
				exit(ft_echo(cmds->argv));
			if (!ft_strcmp(cmds->argv[0], "pwd"))
				exit(ft_pwd(shell));
			if (!ft_strcmp(cmds->argv[0], "env"))
				exit(ft_env(shell));
			// commande externe
			path = find_path(cmds, shell);
			if (!path)
				exit(shell->exit_status);
			// ✅ renvoie 126 ou 127 selon find_path()
			if (!path)
				exit(127);
			execve(path, cmds->argv, shell->envp);
			perror("execve");
			exit(126);
		}
		// ---- PARENT ----
		last_pid = pid; // mémorise le dernier enfant créé
		if (in_fd != -1)
			close(in_fd);
		if (cmds->next)
		{
			close(fd[1]);  // ferme l’écriture côté parent
			in_fd = fd[0]; // garde la lecture pour la commande suivante
		}
		cmds = cmds->next;
	}
	// Attend TOUS les enfants, mais ne retient que le statut du dernier
	while (1)
	{
		w = waitpid(-1, &status, 0);
		if (w == -1)
			break ;
		if (w == last_pid)
		{
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->exit_status = 128 + WTERMSIG(status);
		}
	}
	shell->in_pipe = 0;
	return (shell->exit_status);
}
