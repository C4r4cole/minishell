/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_header.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:26:49 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/10/30 12:17:57 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

# include "../minishell.h"
# include "../structures.h"
# include "../utils/libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

int		check_n(const char *str);
int		ft_echo(char **argv);
int		ft_pwd(t_shell *shell);
int		execute_cmds_list(t_cmd *cmds, t_shell *shell);
int		execute_piped_cmds(t_cmd *cmds, t_shell *shell);
int		exec_one_cmd(t_cmd *cmd, t_shell *shell);
char	*find_path(t_cmd *cmd, t_shell *shell);
void	init_shell(t_shell *shell, char **envp);
void	free_shell(t_shell *shell);
int		ft_cd(char **argv, t_shell *shell);
t_env	*env_list_from_envp(char **envp);
int		ft_export(char **argv, t_shell *shell);
void	env_update_or_add(t_env **lst, char *key, char *value);
int		ft_env(t_shell *shell);
void	update_pwd(t_shell *shell, char *oldpwd);
int		ft_exit(char **argv, t_shell *shell);
int		ft_unset(char **argv, t_shell *shell);
int		is_valid_env_name(const char *str);
int		export_error(char *arg);
int		ft_isnumber(char *str);
void	env_remove(t_env **lst, char *key);
char	*env_get_value(t_env *env, const char *key);

int		handle_heredoc(char *end_word);
char	**env_to_tab(t_env *env);
void	execute_redirections_cmds(t_cmd *cmd);
int		execute_redirections_builtins(t_redir *redir);
int		heredoc_before_fork(t_cmd *arg);
int		heredoc_before_fork_all(t_cmd *cmds);
void    handle_sigint_heredoc(int sig);

void	setup_signals_main(void);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
extern int g_sig; 

#endif
