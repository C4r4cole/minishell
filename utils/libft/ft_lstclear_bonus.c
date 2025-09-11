/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:14:22 by fmoulin           #+#    #+#             */
/*   Updated: 2025/05/13 11:27:44 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	del(void *content)
// {
// 	free(content);
// }

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!*lst || !del)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->content)
			del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
}

// #include <stdio.h>

// int main(void)
// {
//     t_list *node1 = ft_lstnew(ft_strdup("nihao"));
// 	t_list *node2 = ft_lstnew(ft_strdup("ciao"));
// 	t_list *chain = NULL;

// 	ft_lstadd_back(&chain, node1);
// 	ft_lstadd_back(&chain, node2);
// 	ft_lstclear(&chain, del);
//     return (0);
// }