# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/11 14:02:02 by fmoulin           #+#    #+#              #
#    Updated: 2025/09/11 15:20:23 by fmoulin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'executable
NAME = minishell

SRCS_DIR = .
OBJS_DIR = obj

# Sources comunes
SRCS =	minishell.c utils/error.c utils/list_utils.c utils/str_utils.c parser/expand.c parser/lexer.c \
		parser/parser.c parser/quotes.c parser/syntax.c parser/tokens.c

# Mains
MAIN = minishell.c

# Objets
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

# Compilation
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

LIBS = -lreadline -lhistory -lncurses

# Regle par defaut
all: $(NAME)

# Executable principal
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Compilation des objets
$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re