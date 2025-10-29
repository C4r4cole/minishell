/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:41:24 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/10/29 11:47:29 by ilsedjal         ###   ########.fr       */
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

	if (shell && shell->pwd)
	{
		printf("%s\n", shell->pwd);
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

int	ft_cd(char **argv, t_shell *shell)
{
	char	*target;
	char	*oldpwd;
	char	*newpwd;

	oldpwd = getcwd(NULL, 0);
	if (!argv[1])
		target = getenv("HOME");
	if (argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->exit_status = 1;
		return (1);
	}
	else if (ft_strncmp(argv[1], "-", ft_strlen(argv[1])) == 0)
		target = shell->oldpwd;
	else
		target = argv[1];
	if (!target)
	{
		perror("cd: no target found");
		free(oldpwd);
		return (1);
	}
	if (chdir(target) != 0)
	{
		perror("cd:");
		free(oldpwd);
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	if (newpwd)
	{
		// free ancien shell->oldpwd
		free(shell->oldpwd);
		shell->oldpwd = oldpwd;
		free(shell->pwd);
		shell->pwd = newpwd;
		// mettre à jour dans l'env
		env_update_or_add(&(shell->envp_lst), "OLDPWD", shell->envp_lst->key);
		env_update_or_add(&(shell->envp_lst), "PWD", shell->envp_lst->key);
	}
	else
		free(oldpwd); // on libère si jamais getcwd a échoué
	return (0);
}

int	ft_exit(char **argv, t_shell *shell)
{
	long long	status;

	status = 1;
	// ft_putstr_fd("exit\n", 2);
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
	// liberer la env aussi
	free_shell(shell);
	// quit avc le bon status
	exit((int)status);
}
