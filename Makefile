# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/11 14:02:02 by fmoulin           #+#    #+#              #
#    Updated: 2025/11/12 10:43:39 by ilsedjal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'executable
NAME = minishell

SRCS_DIR = .
OBJS_DIR = obj

# Sources comunes
SRCS =	minishell.c parser/cleaner.c parser/expand.c parser/lexer.c parser/parser.c parser/syntax.c parser/tokens.c \
		parser/quoting/quoting_double_quotes.c parser/quoting/quoting_others.c parser/quoting/quoting_redirections.c \
		parser/quoting/quoting_single_quotes.c \
		utils/redir_utils.c utils/cmd_utils.c utils/env_utils.c utils/lexer_utils.c utils/lexer_split_utils.c \
		utils/tokens_utils.c utils/parser_utils.c \
		exec/exec_cmd_list.c exec/exec_utils1.c exec/exec_utils2.c exec/exec_utils3.c exec/exec_utils4.c \
		exec/exec_redirections_cmds.c exec/exec_redirections_builtins.c exec/exec_signals.c exec/exec_builtins1.c exec/exec_builtins2.c  \
		exec/exec_heredoc.c exec/exec_heredoc_utils.c exec/exec_piped_cmd.c exec/exec_piped_utils.c exec/exec_builtins_child.c exec/exec_piped_logic.c \
		parser/tokens_helpers.c 

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