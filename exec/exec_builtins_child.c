/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins_child.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:41:01 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/11/12 10:41:03 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

int	try_child_builtin(char **argv, t_shell *shell, int *handled)
{
	int	code;

	*handled = 1;
	if (!ft_strcmp(argv[0], "exit"))
	{
		code = ft_exit_return_code(argv);
		if (!ft_isnumber(argv[1]))
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		return (code);
	}
	if (!ft_strcmp(argv[0], "echo"))
		return (ft_echo(argv));
	if (!ft_strcmp(argv[0], "pwd"))
		return (ft_pwd(shell));
	if (!ft_strcmp(argv[0], "env"))
		return (ft_env(shell));
	if (!ft_strcmp(argv[0], "cd"))
		return (ft_cd(argv, shell));
	if (!ft_strcmp(argv[0], "export"))
		return (ft_export(argv, shell));
	if (!ft_strcmp(argv[0], "unset"))
		return (ft_unset(argv, shell));
	*handled = 0;
	return (0);
}
