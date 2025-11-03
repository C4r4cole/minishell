/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:41:24 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/11/03 14:01:32 by fmoulin          ###   ########.fr       */
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

char *env_get_value(t_env *env, const char *key)
{
    while (env)
    {
        if (!ft_strcmp(env->key, key))
            return env->value;
        env = env->next;
    }
    return NULL;
}


int	ft_cd(char **argv, t_shell *shell)
{
    int     argc = 0;
    char    *target;
    char    *oldpwd;
    char    *newpwd;

    while (argv[argc])
        argc++;

    if (argc > 2)
        return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);

    oldpwd = env_get_value(shell->envp_lst, "PWD");

    // ---- Déterminer target ----
    if (argc == 1) // cd seul → HOME
        target = env_get_value(shell->envp_lst, "HOME");
    else if (!ft_strcmp(argv[1], "-")) // cd -
    {
        target = env_get_value(shell->envp_lst, "OLDPWD");
        if (!target)
            return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), 1);
        ft_printf("%s\n", target); // afficher OLDPWD comme bash
    }
    else
        target = argv[1];

    if (!target)
        return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);

    // ---- Changer de dossier ----
    if (chdir(target) != 0)
        return (perror("minishell: cd"), 1);

    // ---- Mettre à jour PWD et OLDPWD ----
    newpwd = getcwd(NULL, 0);
    if (!newpwd)
        return (perror("getcwd"), 1);

    if (oldpwd)
        env_update_or_add(&(shell->envp_lst), "OLDPWD", oldpwd);
    env_update_or_add(&(shell->envp_lst), "PWD", newpwd);

    free(newpwd);
    return (0);
}

int	ft_exit(char **argv, t_shell *shell)
{
	long long	status;

	status = 1;
	ft_putstr_fd("exit\n", 2);
	if (!argv[1])
	{
		status = shell->exit_status;
	}
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
	// remplacer par un atoll car on peut quitter avec un code erreur au dessus de int
	if (shell->current_cmd_list)
		free_cmd_list(shell->current_cmd_list);
	
	// liberer la env aussi
	free_shell(shell);
	// quit avc le bon status
	exit((int)status);
}
