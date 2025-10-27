# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/11 14:02:02 by fmoulin           #+#    #+#              #
#    Updated: 2025/10/27 17:11:43 by fmoulin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'executable
NAME = minishell

SRCS_DIR = .
OBJS_DIR = obj

# Sources comunes
SRCS =	minishell.c utils/error.c utils/list_utils.c utils/banner.c parser/cleaner.c \
		parser/expand.c parser/lexer.c parser/parser.c parser/syntax.c \
		parser/tokens.c parser/quoting/quoting_00.c parser/quoting/quoting_01.c \
		parser/quoting/quoting_02.c parser/quoting/quoting_03.c parser/quoting/quoting_04.c \
		parser/quoting/quoting_symbols.c exec/exec_builtins1.c exec/exec_cmd.c exec/exec_utils.c \
		parser/parser_utils.c parser/quoting/quoting_05.c exec/exec_heredoc.c \
		exec/exec_redirections.c exec/exec_signals.c \

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
LIBFT_DIR = utils/libft
LIBFT = $(LIBFT_DIR)/libft.a

# Regle par defaut
all: $(LIBFT) $(NAME)

# Libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Executable principal
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) $(LIBFT) -g

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

test: all
	@valgrind \
	 --memcheck:leak-check=full \
	 --memcheck:track-fds=yes \
	 --memcheck:suppressions=./minishell.supp \
	 --memcheck:track-origins=yes \
	 --memcheck:show-leak-kinds=all \
	 --memcheck:show-reachable=no \
	 --memcheck:show-error-list=yes \
	 --log-file=valgrind.log ./minishell; \
	 cat valgrind.log; \
	 rm -f valgrind.log

.PHONY: all bonus clean fclean re