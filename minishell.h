/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:52:30 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/10 19:31:23 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ======================== //
// ====== LIBRAIRIES ====== //
// ======================== //

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <stdlib.h>
# include <stdio.h>
# include "utils/libft/libft.h"
# include "utils/libft/ft_printf.h"
# include "utils/libft/get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include "exec/exec_header.h"
# include "parser/parser.h"
# include "exec/exec_header.h"

#endif