NAME = lem_in

PATH_SRCS = srcs/

HEADERS_FILES = includes/

SRCS =	$(PATH_SRCS)main.c \
		$(PATH_SRCS)init_data.c \
		$(PATH_SRCS)ft_list_push_back.c \
		$(PATH_SRCS)move_ant.c \
		$(PATH_SRCS)lem_in.util.c \
		$(PATH_SRCS)get_room.c \
		$(PATH_SRCS)get_pipe.c \
		$(PATH_SRCS)get_path.c \
		$(PATH_SRCS)get_path.util.c \
		$(PATH_SRCS)free_func.c \
		$(PATH_SRCS)handle_command.c \
		$(PATH_SRCS)handle_error.c

OBJS = $(SRCS:.c=.o)

OBJS_FILTERED = $(notdir $(OBJS))

LIB_OBJS = libft/ft_putstr.o \
		   libft/ft_atoi.o \
		   libft/ft_itoa.o \
		   libft/ft_lstdel.o \
		   libft/ft_lstnew.o \
		   libft/ft_putchar.o \
		   libft/ft_putendl.o \
		   libft/ft_putnbr.o \
		   libft/ft_putstr_fd.o \
		   libft/ft_strcmp.o \
		   libft/ft_strchr.o \
		   libft/ft_strdel.o \
		   libft/ft_strdup.o \
		   libft/ft_strequ.o \
		   libft/ft_strsplit.o \
		   libft/get_next_line.o \
		   libft/ft_isprint.o \
		   libft/ft_lstdelone.o \
		   libft/ft_memalloc.o \
		   libft/ft_memcpy.o \
		   libft/ft_putchar_fd.o \
		   libft/ft_strcpy.o \
		   libft/ft_strlen.o \
		   libft/ft_strnew.o \
		   libft/ft_strrev.o \
		   libft/ft_strsub.o \
		   libft/ft_bzero.o \
		   libft/ft_memset.o \
		   libft/ft_isdigit.o

FLAGS = -Wall -Werror -Wextra #-fsanitize=address

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
