# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/06 10:22:37 by ingrid            #+#    #+#              #
#    Updated: 2026/01/30 16:15:11 by ingrid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

# ================= FLAGS =================
CFLAGS =  -Wall -Wextra -Werror
THREAD = -pthread

# ================= FILES =================
SRCS = main.c parse.c init.c utils.c monitor.c thread.c routine.c
OBJS = $(SRCS:.c=.o)

# ================= COLORS =================
RESET =\033[0m
GREEN =\033[1;32m
YELLOW = \033[1;33m
RED = \033[1;31m

# ================= RULES =================
all: $(NAME)

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $(THREAD) $(OBJS) -o $(NAME)
		@echo "$(GREEN)[OK]$(RESET) $(NAME) compiled successfully."

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
		@rm -f $(OBJS)
		@echo "$(YELLOW)[CLEAN]$(RESET) Object files successfully removed."

fclean: clean
		@rm -f $(NAME)
		@echo "$(RED)[FCLEAN]$(RESET) Executable '$(NAME)' Removed."

re: fclean all

.PHONY: all clean fclean re

