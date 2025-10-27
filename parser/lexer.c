/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:44:59 by fmoulin           #+#    #+#             */
/*   Updated: 2025/10/27 18:32:51 by fmoulin          ###   ########.fr       */
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

t_splitter	*splitter_init(void)
{
	t_splitter *init;
	
	init = malloc(sizeof(t_splitter));
	if (!init)
		return (NULL);
	init->output = NULL;
	init->count = 0;
	init->i = 0;
	init->in_single = 0;
	init->in_double = 0;
	init->buf = ft_strdup("");

	return (init);
}

int	add_split_meta_len(	t_splitter *initialized, char *input)
{
	int meta_len;
	
	meta_len = get_metacharacter_length(&input[initialized->i]);
	if (meta_len > 0)
	{
		if (initialized->buf[0] != '\0')
		{
			initialized->output = add_split(initialized->output, &initialized->count, initialized->buf, ft_strlen(initialized->buf));
			free(initialized->buf);
			initialized->buf = ft_strdup("");
		}
		initialized->output = add_split(initialized->output, &initialized->count, &input[initialized->i], meta_len);
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
			initialized->output = add_split(initialized->output, &initialized->count, initialized->buf, ft_strlen(initialized->buf));
			free(initialized->buf);
			initialized->buf = ft_strdup("");
		}
		initialized->i++;
		return (1);
	}
	return (0);
}

int	set_in_single(t_splitter *initialized, char *input)
{
	if (is_single_quote(input[initialized->i]))
	{
		initialized->in_single = 1;
		initialized->i++;
		return (1);
	}
	return (0);
}

int	set_in_double(t_splitter *initialized, char *input)
{
	if (is_double_quote(input[initialized->i]))
	{
		initialized->in_double = 1;
		initialized->i++;
		return (1);
	}
	return (0);
}

int	unset_in_single(t_splitter *initialized, char *input)
{
	if (is_single_quote(input[initialized->i]))
	{
		initialized->in_single = 0;
		initialized->i++;
		return (1);
	}
	return (0);
}

int	unset_in_double(t_splitter *initialized, char *input)
{
	if (is_double_quote(input[initialized->i]))
	{
		initialized->in_double = 0;
		initialized->i++;
		return (1);
	}
	return (0);
}

int	expand_and_join(t_splitter *initialized, char *input, t_shell *shell)
{
	char *expanded;
	char *joined;
	
	if (is_dollar(input[initialized->i]))
	{
		initialized->i++;
		expanded = expand_one_dollar(input, &initialized->i, shell);
		joined = ft_strjoin(initialized->buf, expanded);
		free(initialized->buf);
		free(expanded);
		initialized->buf = joined;
		return (1);
	}
	return (0);
}

char **input_splitter(char *input, t_shell *shell)
{
	t_splitter *initialized;

	initialized = splitter_init();
    while (input[initialized->i])
	{
        if (!initialized->in_single && !initialized->in_double)
		{
			if (add_split_meta_len(initialized, input))
				continue ;
			if (add_split_on_space(initialized, input))
				continue ;
			if (set_in_single(initialized, input))
				continue ;
			if (set_in_double(initialized, input))
				continue ;
			if (expand_and_join(initialized, input, shell))
				continue ;
        }
		else if (initialized->in_single)
		{
			if (unset_in_single(initialized, input))
				continue ;
        }
		else if (initialized->in_double)
		{
			if (unset_in_double(initialized, input))
				continue ;
			if (expand_and_join(initialized, input, shell))
				continue ;
        }
        initialized->buf = str_append_char(initialized->buf, input[initialized->i]);
        initialized->i++;
    }
    if (initialized->buf[0] != '\0')
	{
        initialized->output = add_split(initialized->output, &initialized->count, initialized->buf, ft_strlen(initialized->buf));
    }
    free(initialized->buf);
    return (initialized->output);
}
