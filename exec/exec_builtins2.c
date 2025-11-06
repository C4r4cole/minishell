/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:03:42 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/11/05 16:15:22 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "exec_header.h"

int	ft_env(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->envp_lst;
	while (tmp)
	{
		if (tmp->value)
			ft_printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

static int	process_export_arg(char *arg, t_shell *shell, int *exit_code)
{
	char	*eq;
	char	*key;
	char	*value;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		key = ft_substr(arg, 0, eq - arg);
		value = ft_strdup(eq + 1);
		if (!is_valid_env_name(key))
			*exit_code = export_error(arg);
		else
			env_update_or_add(&shell->envp_lst, key, value);
		free(key);
		free(value);
	}
	else if (!is_valid_env_name(arg))
		*exit_code = export_error(arg);
	else
		env_update_or_add(&shell->envp_lst, arg, NULL);
	return (0);
}

int	ft_export(char **argv, t_shell *shell)
{
	int	i;
	int	exit_code;

	i = 1;
	exit_code = 0;
	if (!argv[1])
		return (0);
	while (argv[i])
		process_export_arg(argv[i++], shell, &exit_code);
	if (shell->in_pipe)
		return (1);
	else
		return (exit_code);
}

int	ft_unset(char **argv, t_shell *shell)
{
	int	i;

	if (!argv[1])
		return (0);
	i = 1;
	while (argv[i])
	{
		if (argv[i][0] && is_valid_env_name(argv[i]))
		{
			env_remove(&(shell->envp_lst), argv[i]);
		}
		else
		{
			ft_putstr_fd("': not a valid identifier\n", 2);
			shell->exit_status = 1;
		}
		i++;
	}
	return (0);
}

int	ft_exit(char **argv, t_shell *shell)
{
	long long	status;

	status = 1;
	ft_putstr_fd("exit\n", 2);
	if (!argv[1])
		status = shell->exit_status;
	else if (!ft_isnumber(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		status = 2;
	}
	else if (argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->exit_status = 1;
		return (1);
	}
	else
		status = ft_atoi(argv[1]);
	if (shell->current_cmd_list)
		free_cmd_list(shell->current_cmd_list);
	free_shell(shell);
	exit((int)status);
}
