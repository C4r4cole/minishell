/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:49:39 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/06 17:33:18 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parser.h"

char	**copy_old_split(char **old, int count)
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

char	**add_split(char **string_to_subsplit, int *nb_splitted, char *start,
		int len)
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

int	get_metacharacter_length(char *str)
{
	if (!str)
		return (0);
	if ((is_redirection_in(str[0]) && is_redirection_in(str[1]))
		|| (is_redirection_out(str[0]) && is_redirection_out(str[1])))
		return (2);
	if (is_redirection_in(str[0]) || is_redirection_out(str[0])
		|| is_pipe(str[0]))
		return (1);
	return (0);
}

int	add_split_meta_len(t_splitter *initialized, char *input)
{
	int	meta_len;

	meta_len = get_metacharacter_length(&input[initialized->i]);
	if (meta_len > 0)
	{
		if (initialized->buf[0] != '\0')
		{
			initialized->output = add_split(initialized->output,
					&initialized->count, initialized->buf,
					ft_strlen(initialized->buf));
			free(initialized->buf);
			initialized->buf = ft_strdup("");
		}
		initialized->output = add_split(initialized->output,
				&initialized->count, &input[initialized->i], meta_len);
		initialized->i += meta_len;
		return (1);
	}
	return (0);
}

int	add_split_on_space(t_splitter *initialized, char *input)
{
	if (is_space(input[initialized->i]) || is_tab(input[initialized->i]))
	{
		if (initialized->buf[0] != '\0')
		{
			initialized->output = add_split(initialized->output,
					&initialized->count, initialized->buf,
					ft_strlen(initialized->buf));
			free(initialized->buf);
			initialized->buf = ft_strdup("");
		}
		initialized->i++;
		return (1);
	}
	return (0);
}
