/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:27:10 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/09/23 15:07:38 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

int	execute_cmds_list(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		if (ft_strncmp(current->argv[0], "echo", ft_strlen(current->argv[0])) == 0)
		{
			ft_echo(current->argv);
		}
		else if (ft_strncmp(current->argv[0], "pwd",
				ft_strlen(current->argv[0])) == 0)
		{
			ft_pwd(shell);
		}
		else
		{
			shell->exit_status = exec_one_cmd(current->argv, shell->envp);
		}
		current = current->next;
	}
	return (shell->exit_status);
}
