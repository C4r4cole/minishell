/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:44:59 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/25 14:23:53 by fmoulin          ###   ########.fr       */
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
		new[i] = old[i];
		i++;
	}
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
		return (string_to_subsplit);
	special_character = ft_strndup(start, len);
	if (!special_character)
	{
		free(new_split_tab);
		return (new_split_tab);
	}
	new_split_tab[*nb_splitted] = special_character;
	new_split_tab[*nb_splitted + 1] = NULL;
	(*nb_splitted)++;
	free(string_to_subsplit);
	return (new_split_tab);
}

static void	split_word(t_splitter *res, char *str, int *j)
{
	int start;

	start = *j;
	while (str[*j] && !is_quoting_symbols(str[*j]))
		(*j)++;
	res->final_split = add_split(res->final_split, &res->count, &str[start], *j - start);
}

static void split_special(t_splitter *res, char *str, int *j)
{
	res->final_split = add_split(res->final_split, &res->count, &str[*j], 1);
	if (str[*j])
		(*j)++;
}

char **input_splitter(char *input)
{
	t_splitter result;
	int		i;
	int		j;
	
	result.input_split = ft_split(input, ' ');
	result.final_split = NULL;
	i = 0;
	result.count = 0;
	while (result.input_split[i])
	{
		j = 0;
		while (result.input_split[i][j])
		{
			if (is_quoting_symbols(result.input_split[i][j]))
				split_special(&result, result.input_split[i], &j);
			else
				split_word(&result, result.input_split[i], &j);
		}
		i++;
	}
	return (result.final_split);
}
