/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:48:50 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/16 16:52:00 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// ======================== //
// ====== LIBRAIRIES ====== //
// ======================== //

# include "../minishell.h"
# include "../utils/utils.h"

// ======================== //
// ====== STRUCTURES ====== //
// ======================== //

typedef struct s_splitter
{
	char				**input_split;
	char				**final_split;
	int					count;
	int					start;
	struct s_splitter	*next;
}				t_splitter;

// ======================= //
// ====== FONCTIONS ====== //
// ======================= //

char **input_splitter(char *input);


#endif