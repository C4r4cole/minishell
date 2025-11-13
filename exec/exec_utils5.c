/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:27:42 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/11/13 11:50:16 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

void    add_env_var(t_shell *shell, const char *key, const char *value)
{
    t_env    *new;
    t_env    *tmp;

    new = malloc(sizeof(t_env));
    if (!new)
        return ;
    new->key = strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
    new->next = NULL;
    if (!shell->envp_lst)
        shell->envp_lst = new;
    else
    {
        tmp = shell->envp_lst;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}

static void    init_minimal_env(t_shell *shell)
{
    char    *pwd;

    pwd = getcwd(NULL, 0);
    if (!pwd)
        pwd = strdup(""); // sécurité
    add_env_var(shell, "PWD", pwd);
    add_env_var(shell, "SHLVL", "1");
    add_env_var(shell, "_", "/usr/bin/env");
    add_env_var(shell, "PATH", "/usr/local/bin:/usr/bin:/bin");
    free(pwd);
}

void    init_shell(t_shell *shell, char **envp)
{
    if (!envp || !*envp)
    {
        shell->envp_lst = NULL;
        init_minimal_env(shell);
    }
    else
        shell->envp_lst = env_list_from_envp(envp);
    shell->exit_status = 0;
    shell->in_pipe = 0;
    shell->current_cmd_list = NULL;
}

