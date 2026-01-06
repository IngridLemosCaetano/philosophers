# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/06 10:22:37 by ingrid            #+#    #+#              #
#    Updated: 2026/01/06 10:34:42 by ingrid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c philo.c utils.c monitor.c mutex.c

OBJS = (SRCS)/%.c=/%.o

all: $(NAME)

$(OBJS)/%.o: /%.c philo.h $(CC) $(CFLAGS) -I -c $< -o $@
		@echo "Compiled $< → $@"

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $@
		@echo "✅ Created $(NAME)"

clean:
		@rm -f $(OBJS)
		@echo "🧹 Removed object files"

fclean:
		@rm -f $(NAME)
		@echo "🗑️ Removed executables"

re: fclean all

