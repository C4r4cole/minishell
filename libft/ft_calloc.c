/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:23:28 by fmoulin           #+#    #+#             */
/*   Updated: 2025/05/02 13:01:56 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*alloc;

	if (!nmemb || !size)
		return (malloc(0));
	if (nmemb * size > FT_INT_MAX)
		return (NULL);
	alloc = malloc(nmemb * size);
	if (!alloc)
		return (NULL);
	ft_bzero(alloc, nmemb * size);
	return (alloc);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int	nmemb;
// 	char size = sizeof(char);
// 	char *ptr;
// 	char	*ptr_true;	
// 	nmemb = 10;
// 	ptr = (char *)ft_calloc(nmemb, size);
// 	ptr_true = (char *)calloc(nmemb, size);

// 	printf("%d\n", ptr[0]);
// 	printf("%d\n", ptr[1]);
// 	printf("%d\n", ptr[2]);
// 	printf("%d\n", ptr[3]);
// 	printf("%d\n", ptr[4]);
// 	printf("%d\n", ptr[5]);
// 	printf("%d\n", ptr[6]);
// 	printf("%d\n", ptr[7]);
// 	printf("%d\n", ptr[8]);
// 	printf("%d\n", ptr[9]);
// 	printf("%d\n", ptr[10]);
// 	printf("%d\n", ptr[11]);
// 	printf("\n");
// 	printf("%d\n", ptr_true[0]);
// 	printf("%d\n", ptr_true[1]);
// 	printf("%d\n", ptr_true[2]);
// 	printf("%d\n", ptr_true[3]);
// 	printf("%d\n", ptr_true[4]);
// 	printf("%d\n", ptr_true[5]);
// 	printf("%d\n", ptr_true[6]);
// 	printf("%d\n", ptr_true[7]);
// 	printf("%d\n", ptr_true[8]);
// 	printf("%d\n", ptr_true[9]);
// 	printf("%d\n", ptr_true[10]);
// 	printf("%d\n", ptr_true[11]);
// 	return (0);
// }
