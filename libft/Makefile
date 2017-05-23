NAME		:= libftprintf.a
CC			:= gcc
FLAGS		+= -Wall -Wextra -Werror
# FLAGS		+=-g
CTYPE_DIR	:= src/ft_ctype
STDIO_DIR	:= src/ft_stdio
STDLIB_DIR	:= src/ft_stdlib
STRING_DIR	:= src/ft_string
STRINGS_DIR	:= src/ft_strings
PRINTF_DIR	:= src/ft_stdio/ft_printf
LIST_DIR	:= src/data_structs/ft_list
BTREE_DIR	:= src/data_structs/ft_btree
##LIBFT
#ftstrings(bstring)
SS_FILES	:= ft_bzero
SS_FILES	:= $(addprefix $(STRINGS_DIR)/, $(SS_FILES))
#ftstring(bstring)
S_FILES		+= ft_memset ft_memcpy ft_memccpy
S_FILES		+= ft_memmove ft_memchr ft_memcmp
#ftstring(bstring)--extra
S_FILES		+= ft_memalloc ft_memdel
#ftstring
S_FILES		+= ft_strlen ft_strcat ft_strchr
S_FILES		+= ft_strcmp ft_strcpy ft_strncat
S_FILES		+= ft_strncmp ft_strncpy ft_strrchr
S_FILES		+= ft_strstr ft_strdup ft_strlcat
S_FILES		+= ft_strnstr
#ftstring--extra
S_FILES		+= ft_strnew ft_strdel ft_strclr
S_FILES		+= ft_striter ft_striteri ft_strmap
S_FILES		+= ft_strmapi ft_strequ ft_strnequ
S_FILES		+= ft_strsub ft_strjoin ft_strtrim
S_FILES		+= ft_strsplit ft_strcatmulti ft_strupper
S_FILES		+= ft_strcrep
S_FILES		:= $(addprefix $(STRING_DIR)/, $(S_FILES))
#ftstdlib
LIB_FILES	:= ft_atoi ft_itoa
LIB_FILES	:= $(addprefix $(STDLIB_DIR)/, $(LIB_FILES))
#ftctype
CTYPE_FILES	+= ft_isalpha ft_isdigit ft_isalnum
CTYPE_FILES	+= ft_isascii ft_isprint ft_toupper
CTYPE_FILES	+= ft_tolower
CTYPE_FILES	:= $(addprefix $(CTYPE_DIR)/, $(CTYPE_FILES))
#ftstdio
IO_FILES	+= ft_putchar
#ftstdio--extra
IO_FILES	+= ft_putstr ft_putendl ft_putnbr
IO_FILES	+= ft_putchar_fd ft_putstr_fd ft_putendl_fd
IO_FILES	+= ft_putnbr_fd
IO_FILES	:= $(addprefix $(STDIO_DIR)/, $(IO_FILES))
#dstruct/list
DL_FILES	+= ft_lstnew ft_lstdelone ft_lstdel
DL_FILES	+= ft_lstadd ft_lstiter ft_lstmap
DL_FILES	+= ft_lstdelnode ft_lstaddback
DL_FILES	:= $(addprefix $(LIST_DIR)/, $(DL_FILES))
#dstruct/btree
DB_FILES	+= ft_btreeadd ft_btreeiof ft_btreenew
DB_FILES	+= ft_btreermmin
DB_FILES	:= $(addprefix $(BTREE_DIR)/, $(DB_FILES))
#LIBFT--OBJECTS
FT_OBJECT	+= $(addsuffix .o, $(SS_FILES) $(S_FILES) $(LIB_FILES))
FT_OBJECT	+= $(addsuffix .o, $(IO_FILES) $(CTYPE_FILES) $(DL_FILES))
FT_OBJECT	+= $(addsuffix .o, $(DB_FILES))
##PRINTF
PF_FILES	+= ft_printf ftpf_checks ftpf_helpers
PF_FILES	+= ftpf_strings ftpf_numbers ftpf_otypes
PF_FILES	+= ftpf_parse
PF_FILES	:= $(addprefix $(PRINTF_DIR)/, $(PF_FILES))
#PRINTF--OBJECTS
PF_OBJECT	:= $(addsuffix .o, $(PF_FILES))

.PHONY: clean fclean re all

all: $(NAME)

$(NAME): $(FT_OBJECT) $(PF_OBJECT)
	@echo 'Building $(NAME)'
	@ar rc $@ $^

%.o: %.c
	@$(CC) -c -Iinclude/ $(FLAGS) $< -o $@

clean:
	@echo 'Removing $(NAME)--object files'
	@rm -rf $(FT_OBJECT) $(PF_OBJECT)

fclean: clean
	@echo 'Removing $(NAME)'
	@rm -rf $(NAME)

re: fclean all
