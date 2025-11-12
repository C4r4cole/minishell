/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_piped_logic.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:10:00 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/11/12 10:43:19 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

void	wait_for_all_children(pid_t last_pid, t_shell *shell)
{
	pid_t	w;
	int		status;
	int		sig;

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
			{
				sig = WTERMSIG(status);
				if (sig == SIGQUIT)
					write(2, "Quit (core dumped)\n", 20);
				shell->exit_status = 128 + sig;
			}
		}
	}
}

void	find_last_and_builtin(t_cmd *cmds, t_cmd **last, int *is_builtin)
{
	t_cmd	*node;

	node = cmds;
	while (node && node->next)
		node = node->next;
	*last = node;
	*is_builtin = 0;
	if (node && node->argv && node->argv[0])
	{
		if (!ft_strcmp(node->argv[0], "cd") || !ft_strcmp(node->argv[0],
				"export") || !ft_strcmp(node->argv[0], "unset")
			|| !ft_strcmp(node->argv[0], "exit"))
			*is_builtin = 1;
	}
}

int	exec_last_builtin_parent(t_cmd *last, t_shell *shell)
{
	int	ret;

	ret = -1;
	if (!ft_strcmp(last->argv[0], "cd"))
		ret = ft_cd(last->argv, shell);
	else if (!ft_strcmp(last->argv[0], "export"))
		ret = ft_export(last->argv, shell);
	else if (!ft_strcmp(last->argv[0], "unset"))
		ret = ft_unset(last->argv, shell);
	else if (!ft_strcmp(last->argv[0], "exit"))
		ret = ft_exit(last->argv, shell);
	return (ret);
}
