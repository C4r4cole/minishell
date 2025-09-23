/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_header.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:26:49 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/09/23 14:33:41 by ilsedjal         ###   ########.fr       */
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
# include "../../minishell.h"


typedef struct s_shell
{
    char    *pwd;
    char    *oldpwd;
    char   **envp;         // ton tableau d’environnement
    int      exit_status;
}   t_shell;

int		executre_cmds_list(t_cmd *cmds , t_shell *shell);
int		check_n(const char *str);
int		ft_echo(char **argv);
int		ft_pwd(t_shell *shell);
int		execute_cmds_list(t_cmd *cmds , t_shell *shell);
int		exec_one_cmd(char **argv, char **envp);
char	*find_path(char *args, char **envp);
void	init_shell(t_shell *shell)
#endif

