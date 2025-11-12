/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:41:24 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/11/11 18:02:12 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "exec_header.h"

int	ft_echo(char **argv)
{
	int	newline_flag;
	int	i;

	newline_flag = 1;
	i = 1;
	if (!argv[1])
		return (ft_printf("\n"), 0);
	while (argv[i] && check_n(argv[i]) == 0)
	{
		newline_flag = 0;
		i++;
	}
	while (argv[i])
	{
		ft_printf("%s", argv[i]);
		if (argv[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline_flag)
		ft_printf("\n");
	return (0);
}

int	ft_pwd(t_shell *shell)
{
	char	*current_pwd;

	if (shell && env_get_value(shell->envp_lst, "PWD"))
	{
		ft_printf("%s\n", env_get_value(shell->envp_lst, "PWD"));
		return (0);
	}
	current_pwd = getcwd(NULL, 0);
	if (current_pwd)
	{
		ft_printf("%s\n", current_pwd);
		free(current_pwd);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
	return (0);
}

char	*env_get_value(t_env *env, const char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static char	*cd_get_target(char **argv, t_shell *shell)
{
	char	*target;

	if (!argv[1])
		return (env_get_value(shell->envp_lst, "HOME"));
	if (!ft_strcmp(argv[1], "-"))
	{
		target = env_get_value(shell->envp_lst, "OLDPWD");
		if (!target)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (NULL);
		}
		ft_printf("%s\n", target);
		return (target);
	}
	return (argv[1]);
}

int	ft_cd(char **argv, t_shell *shell)
{
	char	*oldpwd;
	char	*newpwd;
	char	*target;

	if (argv[1] && argv[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	oldpwd = env_get_value(shell->envp_lst, "PWD");
	target = cd_get_target(argv, shell);
	if (!target)
		return (1);
	if (chdir(target) != 0)
		return (perror("minishell: cd"), 1);
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		return (perror("getcwd"), 1);
	if (oldpwd)
		env_update_or_add(&shell->envp_lst, "OLDPWD", oldpwd);
	env_update_or_add(&shell->envp_lst, "PWD", newpwd);
	free(newpwd);
	return (0);
}
