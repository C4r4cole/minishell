/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:48:50 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/18 17:30:55 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// ======================== //
// ====== LIBRAIRIES ====== //
// ======================== //

# include "../minishell.h"
# include "../utils/utils.h"

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
char	**quotes_management(char **final_split);
char	**test_parser(char *input);


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
int	is_quoting_symbols(char c);

#endif