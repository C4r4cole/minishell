/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:03:01 by fmoulin           #+#    #+#             */
/*   Updated: 2025/05/13 11:27:39 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

// #include <stdio.h>

// int main(void)
// {
//     t_list *node1 = ft_lstnew("nihao");
// 	t_list *node2 = ft_lstnew("ciao");
// 	t_list *chain = NULL;

// 	ft_lstadd_front(&chain, node1);
// 	ft_lstadd_front(&chain, node2);

// 	while (chain != NULL)
// 	{
// 		printf("%s\n", (char *)chain->content);
// 		chain = chain->next;
// 	}
//     return (0);
// }