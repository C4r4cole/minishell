/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:21:00 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/10 19:20:32 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

// ======================== //
// ====== STRUCTURES ====== //
// ======================== //

typedef struct s_redir
{
	int				type;
	char			*file;
	int				heredoc_fd;
	int				expand_heredoc;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redir;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_shell
{
	char			**envp;
	t_env			*envp_lst;
	int				exit_status;
	int				in_pipe;
	t_cmd			*current_cmd_list;
}					t_shell;

#endif
