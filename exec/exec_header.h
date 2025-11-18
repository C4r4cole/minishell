/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_header.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:26:49 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/11/18 17:27:26 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_HEADER_H
# define EXEC_HEADER_H

# include "../minishell.h"
# include "../structures.h"
# include "../utils/libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

int			check_n(const char *str);
int			ft_echo(char **argv);
int			ft_pwd(t_shell *shell);
int			execute_cmds_list(t_cmd *cmds, t_shell *shell);
int			execute_piped_cmds(t_cmd *cmds, t_shell *shell);
char		*find_path(t_cmd *cmd, t_shell *shell);
void		init_shell(t_shell *shell, char **envp);
void		free_shell(t_shell *shell);
int			ft_cd(char **argv, t_shell *shell);
t_env		*env_list_from_envp(char **envp);
int			ft_export(char **argv, t_shell *shell);
void		env_update_or_add(t_env **lst, char *key, char *value);
int			ft_env(t_shell *shell);
void		update_pwd(t_shell *shell, char *oldpwd);
int			ft_exit(char **argv, t_shell *shell);
int			ft_unset(char **argv, t_shell *shell);
int			is_valid_env_name(const char *str);
int			export_error(char *arg);
int			ft_isnumber(char *str);
void		env_remove(t_env **lst, char *key);
char		*env_get_value(t_env *env, const char *key);

int			handle_heredoc(char *end_word, int expand, t_shell *shell);
char		**env_to_tab(t_env *env);
void		execute_redirections_cmds(t_cmd *cmd);
int			execute_redirections_builtins(t_redir *redir);
int			heredoc_before_fork(t_cmd *cmd, t_shell *shell);
int			heredoc_before_fork_all(t_cmd *cmds, t_shell *shell);
void		handle_sigint_heredoc(int sig);
/* piped helpers */
void		child_io_setup(t_cmd *cmds, int in_fd, int *fd);
void		wait_for_all_children(pid_t last_pid, t_shell *shell);
void		parent_io_management(t_cmd *cmds, int *in_fd, pid_t pid, int *fd);
void		find_last_and_builtin(t_cmd *cmds, t_cmd **last, int *is_builtin);
int			exec_last_builtin_parent(t_cmd *last, t_shell *shell);
pid_t		spawn_stage(t_cmd *current, int in_fd, int fd[2], t_shell *shell);
int			try_child_builtin(char **argv, t_shell *shell, int *handled);
void		apply_redirs_noop_heredocs(t_redir *redir);

/* exec_heredoc_utils.c */
char		*heredoc_expand_line(char *str, t_shell *shell);
void		append_char_to_out(char **out, char c);
void		process_dollar(char **out, char *str, int *i, t_shell *shell);
int			line_is_end(char *line, char *end_word);
void		write_heredoc(int fd, char *line, int expand, t_shell *shell);
void		close_heredoc_fds_parent(t_cmd *cmds);
int			apply_redirs_noop_files(t_redir *redir);

void		setup_signals_main(void);
void		handle_sigint(int sig);
void		handle_sigquit(int sig);
int			ft_exit_return_code(char **argv);
void		add_env_var(t_shell *shell, const char *key, const char *value);
char		**env_to_tab(t_env *env);
void		free_path_env_tab(char *path, t_shell *shell);
void		child_cleanup_and_exit(t_shell *shell, int status);
void		child_cleanup_and_exit_execve(t_shell *shell, int status,
				char *path, char **env_tab);
int			is_ll_overflow(const char *str);
extern int	g_sig;

#endif
