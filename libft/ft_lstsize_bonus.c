/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:28:39 by francoismou       #+#    #+#             */
/*   Updated: 2025/05/12 14:39:17 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

// #include <stdio.h>

// int main(void)
// {
//     t_list  *elem0;
//     t_list  elem1;
//     t_list  elem2;
//     t_list  elem3;

//     elem0 = &elem1;
//     elem1.next = &elem2;
//     elem2.next = &elem3;
//     elem3.next = 0;

//     printf("%d", ft_lstsize(elem0));
//     return (0);
// }