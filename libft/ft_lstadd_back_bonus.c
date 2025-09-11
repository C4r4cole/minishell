/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:54:00 by francoismou       #+#    #+#             */
/*   Updated: 2025/05/13 11:27:32 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current_elem;

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

// #include <stdio.h>

// int main(void)
// {
//     t_list *node1 = ft_lstnew("nihao");
// 	t_list *node2 = ft_lstnew("ciao");
// 	t_list *chain = NULL;

// 	ft_lstadd_back(&chain, node1);
// 	ft_lstadd_back(&chain, node2);

// 	while (chain != NULL)
// 	{
// 		printf("%s\n", (char *)chain->content);
// 		chain = chain->next;
// 	}
//     return (0);
// }