/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:26:57 by fmoulin           #+#    #+#             */
/*   Updated: 2025/05/06 16:48:30 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	if (((unsigned char *)dest) < ((const unsigned char *)src))
		ft_memcpy(((unsigned char *)dest), ((const unsigned char *)src), size);
	if (((unsigned char *)dest) > ((const unsigned char *)src))
	{
		while (size != 0)
		{
			--size;
			((unsigned char *)dest)[size] = ((unsigned char *)src)[size];
		}
	}
	return (dest);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	src[6] = "hello";
// 	char	dest[6];

// 	printf("%s\n", (char *)memmove(dest, src, sizeof(dest)));
// 	printf("%s\n", (char *)ft_memmove(dest, src, sizeof(dest)));
// 	return (0);
// }