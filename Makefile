# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/06 10:22:37 by ingrid            #+#    #+#              #
#    Updated: 2026/01/11 13:22:01 by ingrid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c philo.c parse.c utils.c monitor.c mutex.c

OBJS = $(SRCS:.c=.o)

%.o:%.c
	$(CC) $(CFLAGS) $(OBJS)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS)
		@echo "✅ Created $(NAME)"

clean:
		@rm -f $(OBJS)
		@echo "🧹 Removed object files"

fclean: clean
		@rm -f $(NAME)
		@echo "🗑️ Removed executables"

re: fclean all

.PHONY: all clean fclean re

