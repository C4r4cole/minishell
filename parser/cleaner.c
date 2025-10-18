/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:27:02 by fmoulin           #+#    #+#             */
/*   Updated: 2025/10/17 14:28:33 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_cmd_list(t_cmd *cmd_list)
{
    t_cmd	*current;
    t_cmd	*next;
    int		i;

    current = cmd_list;
    while (current)
    {
        next = current->next;
        if (current->argv)
        {
            i = 0;
            while (current->argv[i])
            {
                free(current->argv[i]);
                i++;
            }
            free(current->argv);
        }
        free_redir_list(current->redir);
        free(current);
        current = next;
    }
}

void	free_redir_list(t_redir *redir_list)
{
    t_redir	*current;
    t_redir	*next;
	
    current = redir_list;
    while (current)
    {
        next = current->next;
        if (current->file)
            free(current->file);
        free(current);
        current = next;
    }
}

void	free_tokens(char **tokens)
{
    int	i;

    if (!tokens)
        return ;
    i = 0;
    while (tokens[i])
    {
        free(tokens[i]);
        i++;
    }
    free(tokens);
}
