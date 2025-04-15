# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/04 18:20:53 by gribeiro          #+#    #+#              #
#    Updated: 2025/04/04 18:20:53 by gribeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# Srcs
SRCS = src/main.c src/init.c src/init2.c src/memclean.c src/signals.c src/input.c src/ft_printf_fd.c \
	src/echo.c src/expand.c src/parsing.c src/split_quotes.c src/utils.c src/execute.c src/process.c \
	src/execute2.c src/memclean2.c src/child.c
OBJS = $(SRCS:.c=.o)

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Libs
INCLUDES = -I./libft
LIBS = -lreadline -L./libft -lft

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@make bonus -C ./libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@make clean -C ./libft
	rm -f $(OBJS)

fclean: clean
	@make fclean -C ./libft
	rm -f $(NAME)

re: fclean all

valgrind: all
	@valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --trace-children=yes --suppressions=rl.supp -s -q ./minishell

.PHONY: all clean fclean re
