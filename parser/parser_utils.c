/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:49:39 by fmoulin           #+#    #+#             */
/*   Updated: 2025/10/17 11:11:02 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redir *ft_redirnew(char *type, char *file)
{
    t_redir *new;
	
	new = malloc(sizeof(t_redir));
    if (!new)
        return (NULL);
    if (ft_strcmp(type, "<") == 0)
        new->type = REDIRECTION_IN, new->file = ft_strdup(file);
    else if (ft_strcmp(type, ">") == 0)
        new->type = REDIRECTION_OUT, new->file = ft_strdup(file);
    else if (ft_strcmp(type, "<<") == 0)
        new->type = HEREDOC, new->file = ft_strdup(file);
    else if (ft_strcmp(type, ">>") == 0)
        new->type = REDIRECTION_APPEND, new->file = ft_strdup(file);
    new->next = NULL;
    return (new);
}

t_cmd	*ft_cmdnew(char **argv, t_redir *redir)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->argv = argv;
	new->redir = redir;
	new->next = NULL;
	return (new);
}

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*current_elem;
	
	if (!lst || !new)
	return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current_elem = *lst;
	while (current_elem->next != NULL)
	{
		current_elem = current_elem->next;
	}
	current_elem->next = new;
}

void	ft_rediradd_back(t_redir **lst, t_redir *new)
{
	t_redir	*current_elem;
	
	if (!lst || !new)
	return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current_elem = *lst;
	while (current_elem->next != NULL)
	{
		current_elem = current_elem->next;
	}
	current_elem->next = new;
}
