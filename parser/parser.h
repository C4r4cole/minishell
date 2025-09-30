/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:48:50 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/30 17:43:21 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// ======================== //
// ====== LIBRAIRIES ====== //
// ======================== //

# include "../structures.h"
# include "../utils/utils.h"

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
	REDIRECTION_APPEND = 256,
	HEREDOC = 257,
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

typedef struct s_splitter
{
	char				**input_split;
	char				**final_split;
	int					count;
	int					start;
	struct s_splitter	*next;
}				t_splitter;

// ======================= //
// ====== FONCTIONS ====== //
// ======================= //

char	**input_splitter(char *input);
char	**add_split(char **string_to_subsplit, int *nb_splitted, char *start, int len);
char	**quotes_management(char **final_split, t_env *env);
t_cmd	*parse_input(char *user_input, t_env *env);
void	ft_rediradd_back(t_redir **lst, t_redir *new);
void	ft_cmdadd_back(t_cmd **lst, t_cmd *new);
void	ft_envadd_back(t_env **lst, t_env *new);
int		is_env(char *present_token);
int		is_redirection(char *present_token);
t_cmd	*ft_cmdnew(char **argv, t_redir *redir);
t_redir	*ft_redirnew(char *type, char *file);
t_env	*ft_envnew(char *key, char *value);
// t_env	*stored_env(char **envp);


// ======================= //
// == QUOTING FONCTIONS == //
// ======================= //

int	is_pipe(char c);
int	is_slash(char c);
int is_backslash(char c);
int	is_hyphen(char c);
int	is_underscore(char c);
int	is_dollar(char c);
int	is_question_mark(char c);
int	is_double_quote(char c);
int is_single_quote(char c);
int is_ampersand(char c);
int is_redirection_in(char c);
int	is_redirection_out(char c);
int is_semicolon(char c);
int is_opening_parenthesis(char c);
int is_closing_parenthesis(char c);
int is_backtick(char c);
int	is_space(char c);
int is_tab(char c);
int	is_new_line(char c);
int	is_star(char c);
int	is_open_bracket(char c);
int	is_hash(char c);
int	is_tilde(char c);
int	is_equal(char c);
int	is_percent(char c);
int	is_metacharacter(char c);

#endif