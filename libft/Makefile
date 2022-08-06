NAME =	libft.a

SRC =	ft_bzero.c		ft_memccpy.c	ft_memcpy.c		ft_memmove.c\
		ft_memset.c		ft_tolower.c	ft_toupper.c	ft_isprint.c\
		ft_isascii.c	ft_isalnum.c	ft_isdigit.c	ft_isalpha.c\
		ft_atoi.c		ft_strncmp.c	ft_strlen.c		ft_memchr.c\
		ft_memcmp.c		ft_strchr.c		ft_strrchr.c	ft_calloc.c\
		ft_strdup.c		ft_strlcpy.c	ft_strlcat.c	ft_strnstr.c\
		ft_substr.c		ft_strjoin.c	ft_strtrim.c	ft_split.c\
		ft_itoa.c		ft_strmapi.c	ft_putchar_fd.c	ft_putstr_fd.c\
		ft_putendl_fd.c	ft_putnbr_fd.c

SRC_B = ft_lstnew.c\
		ft_lstadd_front.c\
		ft_lstsize.c\
		ft_lstlast.c\
		ft_lstadd_back.c\
		ft_lstdelone.c\
		ft_lstclear.c\
		ft_lstiter.c\
		ft_lstmap.c

SRC_ADD = get_next_line.c	ft_showerr.c	ft_strcmp.c	ft_split_some.c

FLAGS = -Wall -Werror -Wextra
OBJ = $(SRC:.c=.o)
OBJ_B = $(SRC_B:.c=.o)
OBJ_ADD =$(SRC_ADD:.c=.o)
HEADER = libft.h
OBJ_VAR = $(OBJ) $(OBJ_B) $(OBJ_ADD)

R = \033[1;31m
G = \033[0;32m
B = \033[0;34m
C = \033[0;36m
P = \033[0;35m
DF = \033[0m

all : $(NAME)

$(NAME) : $(OBJ_VAR) $(HEADER)
	@ar rcs $@ $^
	@echo "$(G)Libft$(DF) ready."

%.o: %.c 
	gcc $(FLAGS) -c $<

clean :
	@rm -f $(OBJ) $(OBJ_B) $(OBJ_ADD)

fclean : clean
	@rm -f $(NAME)

re : fclean all

bonus : $(OBJ) $(OBJ_B) $(HEADER)
	@ar rcs $(NAME) $^

.PHONY : all clean fclean re bonus full
