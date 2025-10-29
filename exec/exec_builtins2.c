/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:03:42 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/10/29 10:13:37 by ilsedjal         ###   ########.fr       */
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
		if (tmp->value) // n'affiche que les variables avec une valeur
			ft_printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_export(char **argv, t_shell *shell)
{
	int		i;
	char	*equal;
	char	*key;
	char	*value;
	int		exit_code;

	i = 1;
	exit_code = 0;
	// ✅ si export sans argument → on gérera ça plus tard
	if (!argv[1])
		return (0);
	while (argv[i])
	{
		equal = ft_strchr(argv[i], '=');
		if (equal) // cas VAR=VALUE
		{
			key = ft_substr(argv[i], 0, equal - argv[i]);
			value = ft_strdup(equal + 1);
			if (!is_valid_env_name(key))
				exit_code = export_error(argv[i]);
			else
				env_update_or_add(&(shell->envp_lst), key, value);
			free(key);
			free(value);
		}
		else // cas VAR tout seul
		{
			if (!is_valid_env_name(argv[i]))
				exit_code = export_error(argv[i]);
			else
				env_update_or_add(&(shell->envp_lst), argv[i], NULL);
		}
		i++;
	}
	// ✅ Si on est dans un pipe, bash renvoie 1
	if (shell->in_pipe)
		return (1);
	return (exit_code);
}

int	ft_unset(char **argv, t_shell *shell)
{
	int i;

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