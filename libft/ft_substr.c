/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:06:12 by fmoulin           #+#    #+#             */
/*   Updated: 2025/05/14 14:08:28 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	char	*alloc_new_str;
	size_t	i;

	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	new_str = &((char *)s)[start];
	i = 0;
	while (i < len)
	{
		i++;
	}
	alloc_new_str = malloc(sizeof(char) * (i + 1));
	if (!alloc_new_str)
		return (NULL);
	ft_memmove(alloc_new_str, new_str, len);
	alloc_new_str[i] = '\0';
	return (alloc_new_str);
}

// #include	<stdio.h>

// int	main(void)
// {
// 	char	*str = "bjr";
// 	unsigned int	start = 0;
// 	char	*ret = ft_substr(str, start, 3);
// 	printf("%s\n", ret);
// 	// size_t	len;

// 	// start = 15;
// 	// len = 5;
// 	// new_str = ft_substr(s, start, len);
// 	// printf("%s\n", new_str);
// 	return (0);
// }