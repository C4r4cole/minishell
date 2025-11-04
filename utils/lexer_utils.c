/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:49:39 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/04 15:43:11 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parser.h"

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

char	*str_append_char(char *str, char c)
{
	char tmp[2];
	char *joined;
	
	tmp[0] = c;
	tmp[1] = '\0';
	joined = ft_strjoin(str, tmp);
	free(str);
	return (joined);
}
