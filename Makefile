# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/11 14:02:02 by fmoulin           #+#    #+#              #
#    Updated: 2025/09/11 16:59:03 by fmoulin          ###   ########.fr        #
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
IFLAGS = -Iinclude -Ilibft
RM = rm -f

LIBS = -lreadline -lhistory -lncurses

# Libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Regle par defaut
all: $(LIBFT) $(NAME)

# Libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Executable principal
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) $(LIBFT)

# Compilation des objets
$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re