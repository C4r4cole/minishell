/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:49:39 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/10 21:25:14 by fmoulin          ###   ########.fr       */
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
	init->heredoc_next = 0;
	init->token_saw_quote = 0;
	return (init);
}

void flush_buf(t_splitter *init)
{
    char	*to_push;
	char	prefix[2];
	char	*tmp;
	
	to_push = init->buf;
    if (init->heredoc_next)
    {
        if (init->token_saw_quote)
        {
            prefix[0] = '\1';
			prefix[1] = 0;
            tmp = ft_strjoin(prefix, to_push);
            free(to_push);
            to_push = tmp;
        }
        init->heredoc_next = 0;
        init->token_saw_quote = 0;
    }
    init->output = add_split(init->output, &init->count, to_push, ft_strlen(to_push));
    free(to_push);
    init->buf = ft_strdup("");
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
