# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/30 13:19:53 by rcini-ha          #+#    #+#              #
#    Updated: 2025/05/21 13:26:37 by thodavid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCDIR = src
OBJDIR = obj
INCDIR = includes

SRC_MAIN	=	main.c
SRC_HANDLERS	=	handlers/signals.c
SRC_TOKENS	=	tokenisations/lexer.c

SRC_BUILTINS	=	builtins/ft_builtins.c builtins/ft_cd.c builtins/ft_cd_utils.c builtins/ft_export.c
SRC_UTILS		=	utils/envp.c

SRC = $(SRC_MAIN) $(SRC_HANDLERS) $(SRC_TOKENS) $(SRC_BUILTINS) $(SRC_UTILS)
OBJ = $(SRC:.c=.o)
SRC := $(addprefix $(SRCDIR)/, $(SRC))
OBJ := $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(OBJ))

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
LIBFT_INCLUDE := $(LIBFT_DIR)

LDFLAGS =  -L$(LIBFT_DIR)  -lreadline -lncurses
LIBS =  $(LIBFT)

# Archiver
AR = ar
ARFLAGS = rcs

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -g3  -I$(LIBFT_INCLUDE) -I

VERBOSE ?= 1
ifeq ($(VERBOSE),1)
  V :=
else
  V := @
endif

RED     := "\033[1;31m"
GREEN   := "\033[1;32m"
RESET   := "\033[0m"

all: $(OBJDIR) $(LIBFT) $(NAME)

$(OBJDIR):
	$(V)mkdir -p $(OBJDIR) || true

DEP = $(OBJ:.o=.d)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(V)$(CC) $(CFLAGS)  -MMD -MP -c $< -o $@

-include $(DEP)

$(NAME): $(OBJ) $(LIBFT)
	$(V)$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(BONUS_OBJ) $(LIBS) -o $(NAME)
	$(V)echo $(GREEN)"[$(NAME)] Executable created ✅"$(RESET)

$(LIBFT):
	$(V)$(MAKE) --silent -C $(LIBFT_DIR)
	$(V)echo '[$(NAME)] Libft build successfully'

clean:
	$(V)echo $(RED)'[$(NAME)] Cleaning objects'd$(RESET)
	$(V)rm -rf $(OBJDIR)

fclean: clean
	$(V)echo $(RED)'[$(NAME)] Cleaning all files'$(RESET)
	$(V)rm -f $(NAME)
	$(V)$(MAKE) --silent -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus regen
.DEFAULT_GOAL := all
