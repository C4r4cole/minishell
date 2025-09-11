# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/26 11:07:46 by fmoulin           #+#    #+#              #
#    Updated: 2025/06/25 17:17:06 by fmoulin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

# Répertoire des objets
OBJ_DIR = obj

# Fichiers source
SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
	ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
	ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
	ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
	ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
	ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
	ft_lstmap_bonus.c ft_printf.c print_char.c print_digit.c print_digit_upperhexa.c \
	print_format.c print_pointer_address.c print_str.c get_next_line_utils.c get_next_line.c

# Fichiers objets dans obj/
OBJS = $(SRCS:.c=.o)
OBJS := $(addprefix $(OBJ_DIR)/, $(OBJS))

# Compilateur & outils
CC = cc
AR = ar -rc
RM = rm -f

# Options de compilation
CFLAGS = -Wall -Wextra -Werror

# Règle principale
all: $(NAME)

# Compilation de la bibliothèque
$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

# Règle pour créer les .o dans obj/
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
