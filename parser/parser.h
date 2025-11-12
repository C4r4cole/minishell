/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:48:50 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/12 10:39:39 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// ======================== //
// ====== LIBRAIRIES ====== //
// ======================== //

# include "../exec/exec_header.h"
# include "../structures.h"

// ========================= //
// ========= ENUMS ========= //
// ========================= //

enum					e_symbols
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
	CLOSE_BRACKET = ']',
	O_CURLY_BRACKET = '{',
	C_CURLY_BRACKET = '}',
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
	char				**output;
	int					count;
	int					i;
	int					in_single;
	int					in_double;
	char				*buf;
	int					heredoc_next;
	int					token_saw_quote;
	struct s_splitter	*next;
}						t_splitter;

// ======================= //
// ====== FONCTIONS ====== //
// ======================= //

// main function
t_cmd					*parse_input(char *user_input, t_shell *shell);

// parser utils
int						handle_pipe_case(char **tokens, int *i,
							t_cmd **current_cmd, t_cmd **cmd_list);
int						handle_redir_case(char **tokens, int *i,
							t_cmd **current_cmd, t_cmd **list);
void					cleanup(t_cmd *cmd_list, t_redir *redirection_list,
							char **tokens);
int						pipe_and_redir_management(char **tokens, int *i,
							t_cmd **current_cmd, t_cmd **cmd_list);

// syntax
int						syntax_error(char *token);
int						check_syntax_errors(char **tokens);
int						check_unclosed_quotes(char *input);

// expand
char					*expand_one_dollar(char *input, int *idx,
							t_shell *shell);
int						expand_and_join(t_splitter *initialized, char *input,
							t_shell *shell);

// redir utils
t_redir					*ft_redirnew(char *type, char *file);
int						ft_rediradd_back(t_redir **lst, t_redir *new);

// env utils
t_env					*ft_envnew(char *key, char *value);
void					ft_envadd_back(t_env **lst, t_env *new);

// cmd utils
t_cmd					*ft_cmdnew(char **argv, t_redir *redir);
void					ft_cmdadd_back(t_cmd **lst, t_cmd *new);

// lexer's splits functions
char					**input_splitter(char *input, t_shell *shell);
t_splitter				*splitter_init(void);
char					**add_split(char **string_to_subsplit, int *nb_splitted,
							char *start, int len);
int						add_split_meta_len(t_splitter *initialized,
							char *input);
int						add_split_on_space(t_splitter *initialized,
							char *input);
char					**copy_old_split(char **old, int count);
char					*str_append_char(char *str, char c);
void					flush_buf(t_splitter *init);

// tokens' functions
char					**create_cmd_args(char **tokens, int start, int count);
int						handle_redirection(char **tokens, int *i,
							t_redir **redirection_list);
int						handle_command(char **tokens, int *i, t_cmd **cmd_list,
							t_redir **redirection_list);
/* tokens_helpers.c */
int						prepare_redirection_file(int type, char **file,
							int *was_quoted);
int						finalize_and_push_redir(int type, char *file,
							int was_quoted, t_redir **redirection_list);
int						push_cmd_with_redirs(t_cmd **cmd_list, char **cmd_args,
							t_redir **redirection_list);
void					cleanup_build_cmd_args(t_redir **redirection_list);
char					*remove_quotes(char *str);

// tokens utils
void					skip_quotes(char *str, int *i, int *j, char *res);
int						redirection_type(char **tokens, int *i);
char					*redirection_file(char **tokens, int *i);
int						str_has_quote(char *str);

// cleaner's functions
void					free_cmd_list(t_cmd *cmd_list);
void					free_redir_list(t_redir *redir_list);
void					free_tokens(char **tokens);
void					free_tab(char **tab);
void					free_splitter(t_splitter *s);
void					free_env_list(t_env *env);

// ======================= //
// == QUOTING FONCTIONS == //
// ======================= //

// single quotes
int						is_single_quote(char c);
int						set_in_single(t_splitter *initialized, char *input);
int						unset_in_single(t_splitter *initialized, char *input);

// double quotes
int						is_double_quote(char c);
int						set_in_double(t_splitter *initialized, char *input);
int						unset_in_double(t_splitter *initialized, char *input);

// redirections
int						is_redirection_in(char c);
int						is_redirection_out(char c);
int						is_redirection(char *present_token);
int						get_redir_type(char *token);

// others
int						is_space(char c);
int						is_tab(char c);
int						is_pipe(char c);
int						is_dollar(char c);

#endif