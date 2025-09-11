/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:24:28 by fmoulin           #+#    #+#             */
/*   Updated: 2025/05/07 11:07:52 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen(little);
	if (little[0] == '\0')
		return ((char *)big);
	if (len == 0)
		return (0);
	while (big[i] != '\0' && i < len - size + 1)
	{
		if (ft_strncmp(&big[i], little, size) == 0)
			return (&((char *)big)[i]);
		i++;
	}
	return (NULL);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char big[42] = "siamo solo conchiglie sparse sulla sabbia";
// 	char little[7] = "sparse";

// 	printf("%s\n", ft_strnstr(big, little, sizeof(big)));
// 	return (0);
// }