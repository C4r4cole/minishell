/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:52:30 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/18 17:31:02 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ======================== //
// ====== LIBRAIRIES ====== //
// ======================== //

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <stdlib.h>
# include <stdio.h>
# include "utils/libft/libft.h"
# include "utils/libft/ft_printf.h"
# include "utils/libft/get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>

# include "./parser/parser.h"

// ========================= //
// ========= ENUMS ========= //
// ========================= //

enum symbols
{
	PIPE = '|',
	SLASH = '/',
	HYPHEN = '-',
	UNDERSCORE = '_',
	DOLLAR = '$',
	QUESTION_MARK = '?',
	DOUBLE_QUOTE = '"',
	SINGLE_QUOTE = '\'',
	REDIRECTION_IN = '<',
	REDIRECTION_OUT = '>',
	OPEN_BRACKET = '[',
	TILDE = '~',
	PERCENT = '%',
	AMPERSAND = '&',
	SEMI_COLON = ';',
	OPENING_PARENTHESIS = '(',
	CLOSING_PARENTHESIS = ')',
	BACKTICK = '`',
	SPACE_CHAR = ' ',
	TAB_CHAR = '\t',
	NEWLINE_CHAR = '\n',
	BACKSLASH = '\\',
	STAR = '*',
	HASH = '#',
	EQUAL = '='
};

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
	char          *key;		// $
	char          *value;	// HOME
	struct s_env  *next;
}   			t_env;


// ======================= //
// ====== FONCTIONS ====== //
// ======================= //

void	print_banner(void);
// t_cmd	*parse_input(char *line, t_env *env);

#endif