# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clecalie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/15 16:24:08 by clecalie          #+#    #+#              #
#    Updated: 2018/02/15 12:32:17 by clecalie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in

PATH_SRCS = srcs/

HEADERS_FILES = includes/

SRCS =	$(PATH_SRCS)main.c

OBJS = $(SRCS:.c=.o)

OBJS_FILTERED = $(notdir $(OBJS))

LIB_OBJS = libft/*.o

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS_FILTERED)
	@/bin/echo -n "Compiling libft..."
	@make -C libft/
	@echo " [\033[0;32mOK\033[0m]"
	@/bin/echo -n "Compiling lem_in..."
	@gcc $(FLAGS) $(OBJS_FILTERED) $(LIB_OBJS) -o $(NAME)
	@echo " [\033[0;32mOK\033[0m]"

%.o: $(PATH_SRCS)%.c
	@gcc -c $< $(FLAGS) -I libft/includes -I $(HEADERS_FILES)

clean:
	@make -C libft/ clean
	@/bin/echo "Libft cleaned!"
	@rm -f $(OBJS_FILTERED)
	@/bin/echo "Objects files cleaned!"

fclean: clean
	@make -C libft/ fclean
	@rm -f $(NAME)
	@/bin/echo "Binaries files cleaned!"

re: fclean all

.PHONY: all clean fclean re
