/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:21:00 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/25 15:25:14 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

// ======================== //
// ====== STRUCTURES ====== //
// ======================== //

typedef struct s_redir
{
	int				type;   // <, >, >>, <<
	char    		*file;
	struct s_redir	*next;
}   			t_redir;

typedef struct s_cmd
{
	char          **argv;   // ["ls", "-l", NULL]
	t_redir       *redir;   // liste des redirections
	struct s_cmd  *next;    // si pipe → commande suivante
}   			t_cmd;

typedef struct s_env
{
	char          *key;		// $HOME
	char          *value;	// fmoulin
	struct s_env  *next;
}   			t_env;

#endif