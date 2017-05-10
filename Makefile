INCLUDES = ft_ls.o \
			ft_btreenew.o \
			ft_btreeadd.o \
			ft_btreeiof.o \
			ft_btreermmin.o \
			ftls_sorts.o

FLAGS 	 = -Llibft -lft
FLAGS2	 = -Ilibft -I. -Wall -Wextra -Werror -g
NAME	 = ft_ls

$(NAME): $(INCLUDES)
	make -C libft
	gcc $(FLAGS2) $(FLAGS) $^ -o $@

%.o: %.c
	gcc $(FLAGS2) -c $^ -o $@

clean:
	rm -rf $(INCLUDES)
	make -C libft clean

fclean: clean
	rm -rf $(NAME)
	make -C libft fclean

re: fclean all

all: $(NAME)
