INCLUDES	+= ftls.o ftls_l.o ftls_sorts.o
INCLUDES	+= ftls_print.o ftls_read.o ftls_set.o
INCLUDES	:= $(addprefix src/, $(INCLUDES))
FLAGS		+= -Iinclude/ -Ilibft/include/ -Wall -Wextra -Werror
# FLAGS		+= -g
NAME		:= ft_ls

.PHONY: clean fclean re all

all: $(NAME)

$(NAME): $(INCLUDES) libft/libftprintf.a
	@echo 'Building $(NAME)'
	@gcc $(FLAGS) $(FLAGSLIB) $^ -o $@

%.o: %.c
	@gcc $(FLAGS) -c $^ -o $@

libft/libftprintf.a:
	@make -C libft/

clean:
	@echo 'Removing $(NAME)--object files'
	@rm -rf $(INCLUDES)
	@make -C libft/ clean

fclean: clean
	@echo 'Removing $(NAME)'
	@rm -rf $(NAME)
	@make -C libft/ fclean

re: fclean all
