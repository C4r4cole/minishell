/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:37:47 by fmoulin           #+#    #+#             */
/*   Updated: 2025/10/18 19:11:13 by fmoulin          ###   ########.fr       */
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

void execute_redirections_cmds(t_cmd *cmd, t_env *env)
{
	t_redir	*redir;
	int		fd;
	char	*path;
	char 	**envp;

	envp = env_to_tab(env);
	path = find_path(cmd, envp);
	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			// fd = handle_heredoc(redir->file);
			// if (fd < 0)
			// {
			// 	perror("heredoc");
			// 	free_tab(envp);
			// 	return ;
			// }
            if (dup2(redir->heredoc_fd, STDIN_FILENO) < 0)
            {
                perror("dup2");
				exit (1);
            }
			close(redir->heredoc_fd);
		}
		else if (redir->type == REDIRECTION_IN)
		{
			fd = open(redir->file, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->type == REDIRECTION_OUT)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
	execve(path, cmd->argv, envp);
	perror("execve");
	free_tab(envp);
	exit(EXIT_FAILURE);
}

int	handle_heredoc(char *end_word)
{
	char	*line;
	int		fd_write;
	int		fd_read;
	char	*tmpfile;

	tmpfile = "/tmp/minishell_heredoc.txt";
	fd_write = open(tmpfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_write < 0)
		return (perror("heredoc"), -1);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (ft_strcmp(line, end_word) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd_write);
		free(line);
	}
	close(fd_write);
	
	fd_read = open(tmpfile, O_RDONLY);
	if (fd_read < 0)
		return (perror("heredoc read"), -1);
	return (fd_read);
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
			{
				perror("heredoc");
				return (1);
			}
			redir->heredoc_fd = fd;
		}
		redir = redir->next;
	}
	return (0);
}