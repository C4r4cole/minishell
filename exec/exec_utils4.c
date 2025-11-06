/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:27:42 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/11/05 16:07:22 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

int	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int	ft_exit_return_code(char **argv)
{
	if (argv[1] && !ft_isnumber(argv[1]))
	{
		return (2);
	}
	if (argv[1])
		return (ft_atoi(argv[1]) % 256);
	return (0);
}
