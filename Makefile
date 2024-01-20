NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g3 

CC = cc

DIR_SRC = ./src/

DIR_OBJ = ./.obj/

DIR_INC = ./include/

LIST_SRC =	main.c \
			parsing.c \
			prompt.c \
			builtins.c \
			b_env.c \
			b_unset.c \
			b_export.c \
			b_echo.c \
			b_cd.c \
			b_exit.c \
			init.c \
			env_utils.c \
			checks.c \
			ft_utils.c \
			exec.c \
			ft_pre_split.c \
			ft_pre_split_2.c \
			exec_redir.c \
			exec_pipe.c \
			error.c \
			error2.c \
			signal.c \
			dups.c \
			here_doc.c \
			add_to_lst.c \
			expand.c \
			expand_2.c \
			expand_3.c \
			check_quote.c \
			check_quote_2.c \
			export_utils.c \
			export_tools.c \
			new_join.c \
			free.c \
			pipe_utils.c \
			no_env.c \

LIST_INC = minishell.h

LIST_OBJ = ${LIST_SRC:.c=.o}

SRC = $(addprefix $(DIR_SRC), $(LIST_SRC))

OBJ = $(addprefix $(DIR_OBJ), $(LIST_OBJ))

INC = $(addprefix $(DIR_INC), $(LIST_INC))

DIR_LIBFT = libft

LIBFT = libft/libft.a

all : $(NAME)

$(DIR_OBJ) :
	mkdir -p $(DIR_OBJ)

$(LIBFT) : $(DIR_LIBFT)
	$(MAKE) -C $(DIR_LIBFT)

$(DIR_OBJ)%.o : $(DIR_SRC)%.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(DIR_INC) -I/opt/homebrew/opt/readline/include

$(NAME) : $(DIR_OBJ) $(OBJ) $(INC) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline -L/opt/homebrew/opt/readline/lib

bonus :
	$(MAKE) -C bonus

clean:
	rm -rf $(DIR_OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean $(NAME)

.PHONY : clean fclean re all bonus
