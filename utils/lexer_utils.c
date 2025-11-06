/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:49:39 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/06 17:33:22 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parser.h"

t_splitter	*splitter_init(void)
{
	t_splitter	*init;

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

char	*str_append_char(char *str, char c)
{
	char	tmp[2];
	char	*joined;

	tmp[0] = c;
	tmp[1] = '\0';
	joined = ft_strjoin(str, tmp);
	free(str);
	return (joined);
}
