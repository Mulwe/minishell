
NAME = minishell
CC = gcc

CFLAGS = -g -Wall -Wextra -Werror #-fsanitize=address
# ---------------------------------------------------------------------------
# если не работает $(USER) заменить на свой login
# RL_INC = -I/Users/$(USER)/.brew/opt/readline/include
# ----------------------------- OS ------------------------------------------
OS := $(shell uname -s)
ifeq ($(OS), Linux)
	RL_LIB	:= -lreadline
	RL_INC	:=
	PROMT 	:= "readline library"
endif
ifeq ($(OS), Darwin)
	RL_LIB	:= -lreadline -L ~/.brew/opt/readline/lib
	RL_INC	:= -I/Users/$(USER)/.brew/opt/readline/include
	PROMT 	:= "readline library from brew"
endif
# ------------------------------ Colors -------------------------------------
BLACK		=	"\033[30m"	# черный
RED			=	"\033[31m"	# красный
GREEN		=	"\033[32m"	# зеленый
YELLOW		=	"\033[33m"	# желтый
YELL		= 	\033[2;33m
BLUE		=	"\033[34m"	# синий
PURPLE 		=	"\033[35m"	# фиолетовый
CYAN		=	"\033[36m"	# голубой
GRAY		=	"\033[37m"	# серый (белый?)
DEF			=	"\033[0m"	# по умолчанию
WHT			=	 \033[0m
# к о ж з г с ф => red yellow green cyan blue purple
# ---------------------------------------------------------------------------

LIBFT = libft.a
LIBFT_DIR = libft/
LIBA  = $(LIBFT_DIR)$(LIBFT)

INC = ./includes/
SRCS_DIR = srcs/
MAIN_DIR = $(SRCS_DIR)main_part/
BUILT_DIR = $(SRCS_DIR)builtins/

BUILT_SRCS =	echo.c		cd.c\
				export.c	export_utils.c\
				exit.c		unset.c			builtins_utils.c

SRCS =	args.c				builtin_checker.c		main.c				signal.c\
		cmds_bash.c			cmds_bin.c				cmds.c				cmds_utils.c\
		env.c				utils.c					pipe.c				pipe_utils.c\
		parser.c			parser_utils.c			parser_utils_2.c\
		readline.c			readline_utils.c		cmds_bin_utils.c		

OBJ_DIR = objs/
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o)  $(BUILT_SRCS:.c=.o))

all: $(NAME)

$(LIBA):	$(wildcard ${LIBFT_DIR}/*.c)
	@$(MAKE) -C ./$(LIBFT_DIR) --silent
	@cp $(LIBFT_DIR)/libft.h ./includes

$(OBJ_DIR)%.o : $(BUILT_DIR)%.c
	@mkdir -p ${dir $@}
	@$(CC) $(CFLAGS) -I $(INC) -c $< -o $@
	@echo $(RED)$(CC)$(YELLOW)$(CFLAGS)$(GREEN)-I $(INC) $(CYAN)-c $< $(BLUE)-o $(PURPLE)$@ $(DEF)

$(OBJ_DIR)%.o : $(MAIN_DIR)%.c
	@mkdir -p ${dir $@}
	@$(CC) $(CFLAGS) -I $(INC) -c $< -o $@
	@echo $(RED)$(CC)$(YELLOW)$(CFLAGS)$(GREEN)-I $(INC) $(CYAN)-c $< $(BLUE)-o $(PURPLE)$@ $(DEF)

$(OBJ_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p ${dir $@}
	@$(CC) $(CFLAGS) -I $(INC) -c $< -o $@
	@echo $(RED)$(CC)$(YELLOW)$(CFLAGS)$(GREEN)-I $(INC) $(CYAN)-c $< $(BLUE)-o $(PURPLE)$@ $(DEF)

$(NAME): $(LIBA) $(OBJS) Makefile $(wildcard includes/*.h)
	@$(CC) $(CFLAGS) -I $(INC) $(OBJS) ${RL_INC} $(LIBFT_DIR)$(LIBFT) $(RL_LIB) -ltermcap -o $(NAME)
	@echo $(RED)$(CC)$(YELLOW)$(CFLAGS)$(GREEN)-I $(INC) $(CYAN)"  "$(OBJS)$(BLUE)${RL_INC} $(LIBFT_DIR)$(LIBFT) $(RL_LIB) -ltermcap -o $(PURPLE)$(NAME)$(DEF)
	@echo $(BLACK)"--------------------------------------------------------------------------------------------------------------------------------------------------"$(DEF)
	@echo "Your OS is"$(GREEN)$(OS)"."$(DEF)"Minishell requires an installed"$(YELLOW)$(PROMT)"!"$(DEF) "(╮°-°)╮┳━━┳"
#Ubuntu -lreadline -ltermcap
#MAC OS	 specific
# curl -fsSl https://raw.githubusercontent.com/kube/42homebrew/master/install.sh | zsh

clean:
	@$(MAKE) -C $(LIBFT_DIR) fclean --silent 
	@rm -f $(INC)/libft.h
	@rm -rf $(OBJ_DIR)
	@echo All$(BLUE).obj$(DEF) files are cleaned.

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean --silent
	@rm -f $(NAME)
	@echo All$(BLUE).obj$(DEF) files and$(PURPLE)./$(NAME)$(DEF) binary are cleaned. "(╮°-°)╮┳━━┳ ( ╯°□°)╯ ┻━━┻"
re: fclean all

.PHONY: clean fclean re all

# добавить -lreadline при компиляции иначе ссылки на readline не будут найдены



norme:
		@make -s -i norm
norm:
		@echo "${YELL} norminette | grep Error ${WHT}"
		@norminette | grep Error
