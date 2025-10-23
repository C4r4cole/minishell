/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:44:59 by fmoulin           #+#    #+#             */
/*   Updated: 2025/10/23 11:44:13 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	**copy_old_split(char **old, int count)
{
	char	**new;
	int		i;
	
	new = malloc(sizeof(char *) * (count + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new[i] = ft_strdup(old[i]);
		if (!new[i])
		{
			while (i > 0)
				free(new[--i]);
			free(new);
			return (NULL);
		}
		i++;
	}
	new[i] = NULL;
	return (new);
}

char	**add_split(char **string_to_subsplit, int *nb_splitted, char *start, int len)
{
	char	**new_split_tab;
	char	*special_character;
	
	if (len <= 0)
		return (string_to_subsplit);
	new_split_tab = copy_old_split(string_to_subsplit, *nb_splitted);
	if (!new_split_tab)
	{
		free_tab(string_to_subsplit);
		return (NULL);
	}
	special_character = ft_strndup(start, len);
	if (!special_character)
	{
		free_tab(new_split_tab);
		free_tab(string_to_subsplit);
		return (NULL);
	}
	new_split_tab[*nb_splitted] = special_character;
	new_split_tab[*nb_splitted + 1] = NULL;
	(*nb_splitted)++;
	free_tab(string_to_subsplit);
	return (new_split_tab);
}

// static void	split_word(t_splitter *res, char *str, int *j)
// {
// 	int start;

// 	start = *j;
// 	while (str[*j] && !is_metacharacter(str[*j]) && !is_quote(str[*j]))
// 		(*j)++;
// 	res->final_split = add_split(res->final_split, &res->count, &str[start], *j - start);
// 	if (!res->final_split)
// 		return ;
// }

int	get_metacharacter_length(char *str)
{
	if (!str)
		return (0);
	if ((is_redirection_in(str[0]) && is_redirection_in(str[1]))
		|| (is_redirection_out(str[0]) && is_redirection_out(str[1])))
		return (2);
	if (is_redirection_in(str[0]) || is_redirection_out(str[0]) || is_pipe(str[0]))
		return (1);
	return (0);
}

// static void split_special(t_splitter *res, char *str, int *j)
// {
// 	int	metacharacter_len;
	
// 	metacharacter_len = get_metacharacter_length(&str[*j]);
	
// 	if (metacharacter_len > 0)
// 	{
// 		res->final_split = add_split(res->final_split, &res->count, &str[*j], metacharacter_len);
// 		if (!res->final_split)
// 			return ;
// 		*j += metacharacter_len;
// 	}
// 	else
// 	{
// 		res->final_split = add_split(res->final_split, &res->count, &str[*j], 1);
// 		if (!res->final_split)
// 			return ;
// 		if (str[*j])
// 			(*j)++;
// 	}
// }

char **input_splitter(char *input, t_shell *shell)
{
	// t_splitter result;
	// int		i;
	// int		j;

	// if (check_unclosed_quotes(input))
	// 	return (NULL);
	// result.input_split = ft_split(input, ' ');
	// result.final_split = NULL;
	// i = 0;
	// result.count = 0;
	// while (result.input_split[i])
	// {
	// 	j = 0;
	// 	while (result.input_split[i][j])
	// 	{
	// 		if (is_metacharacter(result.input_split[i][j]) || is_quote(result.input_split[i][j]))
	// 			split_special(&result, result.input_split[i], &j);
	// 		else
	// 			split_word(&result, result.input_split[i], &j);
	// 	}
	// 	i++;
	// }
	// free_tab(result.input_split);
	// return (result.final_split);

	char **out = NULL;
    int count = 0;
    int i = 0;
    int in_single = 0, in_double = 0;
    char *buf = ft_strdup("");

    while (input[i]) {
        if (!in_single && !in_double) {
            // Métas hors quotes
            int m = get_metacharacter_length(&input[i]);
            if (m > 0) {
                if (buf[0] != '\0') {
                    out = add_split(out, &count, buf, ft_strlen(buf));
                    free(buf);
                    buf = ft_strdup("");
                }
                out = add_split(out, &count, (char *)&input[i], m);
                i += m;
                continue;
            }
            // Espace hors quotes => fin de mot
            if (input[i] == ' ' || input[i] == '\t') {
                if (buf[0] != '\0') {
                    out = add_split(out, &count, buf, ft_strlen(buf));
                    free(buf);
                    buf = ft_strdup("");
                }
                i++;
                continue;
            }
            // Quotes qui ouvrent
            if (input[i] == '\'') { in_single = 1; i++; continue; }
            if (input[i] == '"')  { in_double = 1; i++; continue; }
            // Expansion $ hors quotes
            if (input[i] == '$') {
                i++;
                char *exp = expand_one_dollar(input, &i, shell);
                char *joined = ft_strjoin(buf, exp);
                free(buf); free(exp);
                buf = joined;
                continue;
            }
        } else if (in_single) {
            // Dans quotes simples : tout est littéral sauf la quote fermante
            if (input[i] == '\'') { in_single = 0; i++; continue; }
        } else if (in_double) {
            // Dans quotes doubles : fin si " ; $ est actif
            if (input[i] == '"') { in_double = 0; i++; continue; }
            if (input[i] == '$') {
                i++;
                char *exp = expand_one_dollar(input, &i, shell);
                char *joined = ft_strjoin(buf, exp);
                free(buf); free(exp);
                buf = joined;
                continue;
            }
        }
        // Caractère normal (dans/ hors quotes)
        buf = str_append_char(buf, input[i]);
        i++;
    }

    // Fin de ligne : flush
    if (buf[0] != '\0') {
        out = add_split(out, &count, buf, ft_strlen(buf));
    }
    free(buf);
    return out;
}
