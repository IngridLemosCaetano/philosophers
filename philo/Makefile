# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/06 10:22:37 by ingrid            #+#    #+#              #
#    Updated: 2026/02/28 23:21:10 by ingrid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj

# ================= FLAGS =================
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I$(INC_DIR)
THREAD = -pthread

# ================= FILES =================
SRCS = $(SRC_DIR)/main.c \
	$(SRC_DIR)/parse.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/monitor.c \
	$(SRC_DIR)/thread.c \
	$(SRC_DIR)/routine.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ================= COLORS =================
RESET =\033[0m
GREEN =\033[1;32m
YELLOW = \033[1;33m
RED = \033[1;31m

# ================= RULES =================
all: $(NAME)

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) $(THREAD) -o $(NAME)
		@echo "$(GREEN)[OK]$(RESET) $(NAME) compiled successfully."

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/philo.h
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) $(THREAD) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)[CLEAN]$(RESET) Object files successfully removed."

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)[FCLEAN]$(RESET) Executable '$(NAME)' Removed."

re: fclean all

.PHONY: all clean fclean re

