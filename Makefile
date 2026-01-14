# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilemos-c <ilemos-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/06 10:22:37 by ingrid            #+#    #+#              #
#    Updated: 2026/01/14 14:42:50 by ilemos-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS =  -Wall -Wextra -Werror
THREAD = -pthread #adicionar quando estiver trabalhando com threads

SRCS = main.c philo.c parse.c utils.c monitor.c mutex.c

OBJS = $(SRCS:.c=.o)

RESET =\033[0m
GREEN =\033[1;32m
YELLOW = \033[1;33m
RED = \033[1;31m

all: $(NAME)

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
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

