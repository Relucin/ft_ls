INCLUDES	:= ftls.o ftls_l.o ftls_sorts.o
INCLUDES	:= $(addprefix src/, $(INCLUDES))
FLAGS		+= -Iinclude/ -Wall -Wextra -Werror
FLAGSLIB	+= -L. -lftprintf
FLAGS		+= -g
NAME		:= ft_ls

$(NAME): $(INCLUDES)
	gcc $(FLAGS) $(FLAGSLIB) $^ -o $@

%.o: %.c
	gcc $(FLAGS) -c $^ -o $@

clean:
	rm -rf $(INCLUDES)

fclean: clean
	rm -rf $(NAME)

re: fclean all

all: $(NAME)
