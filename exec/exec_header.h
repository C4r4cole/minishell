/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_header.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:26:49 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/09/30 16:07:47 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "../utils/libft/libft.h"
# include "../minishell.h"
# include "../structures.h"


// typedef struct s_env 
// {
// 	char *envp;
// 	struct s_env *next;	
// } t_env;

typedef struct s_shell
{
    char    *pwd;
    char    *oldpwd;
    char   **envp;
	t_env  *envp_lst;
    int      exit_status;
}   t_shell;


int		check_n(const char *str);
int		ft_echo(char **argv);
int		ft_pwd(t_shell *shell);
int		execute_cmds_list(t_cmd *cmds , t_shell *shell);
<<<<<<< HEAD
int		exec_one_cmd(t_cmd *arg, char **envp);
char	*find_path(t_cmd *cmd, char **envp);
void	init_shell(t_shell *shell, char **envp);
void	free_shell(t_shell *shell);
int		ft_cd(char **argv);
t_env 	*env_list_from_envp(char **envp);
int		ft_export(char **argv, t_shell *shell);
void 	env_update_or_add(t_env **lst, char *key, char *value);
int		ft_env(t_shell *shell);
#endif

