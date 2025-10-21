/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:49:56 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/10/21 14:38:27 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

void	init_shell(t_shell *shell, char **envp)
{
	shell->pwd = getcwd(NULL, 0); // ← INITIALISE CORRECTEMENT
	if (!shell->pwd)
	{
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
	shell->oldpwd = NULL;
	shell->envp = envp;
	shell->envp_lst = env_list_from_envp(envp);
	// shell->envp_lst = create_lst_envp(envp);
	shell->exit_status = 0;
}

// t_env	*env_new(char *env_line)
// {
// 	t_env	*node;

// 	node = malloc(sizeof(t_env));
// 	if (!node)
// 		return (NULL);
// 	node->envp = ft_strdup(env_line);
// 	node->next = NULL;
// 	return (node);
// }

// t_env	*create_lst_envp(char **envp)
// {
// 	t_env	*head;
// 	t_env	*tail;
// 	int		i;
// 	t_env	*new;

// 	head = NULL;
// 	tail = NULL;
// 	i = 0;
// 	while (envp && envp[i])
// 	{
// 		new = env_new(envp[i]);
// 		if (!new)
// 			break ;
// 		if (!head)
// 			head = new;
// 		else
// 			tail->next = new;
// 		tail = new;
// 		i++;
// 	}
// 	return (head);
// }

void	free_shell(t_shell *shell)
{
	if (shell->pwd)
		free(shell->pwd);
	if (shell->oldpwd)
		free(shell->oldpwd);
}
void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*ft_strjoin_path(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i++] = '/';
	while (s2[j])
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

char	*find_path(t_cmd *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*full_path;

	paths = NULL;
	if (!cmd || !cmd->argv || !cmd->argv[0])
	{
		return (NULL);
	}
	if (ft_strchr(cmd->argv[0], '/'))
		return (ft_strdup(cmd->argv[0]));
	i = -1;
	while (envp && envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			break ;
		}
	}
	if (!paths || !paths[0])
	{
		free_tab(paths);
		return (NULL);
	}
	i = -1;
	while (paths[++i])
	{
		full_path = ft_strjoin_path(paths[i], cmd->argv[0]);
		if (!full_path)
			return (free_tab(paths), NULL);
		if (access(full_path, X_OK) == 0)
			return (free_tab(paths), full_path);
		free(full_path);
	}
	return (free_tab(paths), NULL);
}

t_env *env_list_from_envp(char **envp)
{
    t_env *head = NULL;
    t_env *tail = NULL;
    int i = 0;

    while (envp && envp[i])
    {
        // Découpe la variable en key et value
        char *equal = ft_strchr(envp[i], '=');
        if (!equal)
        {
            i++;
            continue;
        }
        int key_len = equal - envp[i];
        char *key = ft_substr(envp[i], 0, key_len);
        char *value = ft_strdup(equal + 1);
        t_env *new = ft_envnew(key, value);
        if (!head)
            head = new;
        else
            tail->next = new;
        tail = new;
        i++;
    }
    return head;
}

int	exec_one_cmd(t_cmd *arg, char **envp)
{
	pid_t pid;
	int status;
	char *bin;
	t_env	*env;

	env = env_list_from_envp(envp);
	bin = find_path(arg, envp);
	if (!bin)
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		free(bin);
		return (127);
	}
	pid = fork();
	if (pid < 0)
	{
		free(bin);
		return (1);
	}
	if (pid == 0)
	{
		execute_redirections_cmds(arg, env);
		execve(bin, arg->argv, envp);
		perror("error 127");
		exit(1);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}