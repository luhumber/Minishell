.PHONY : clean fclean re bonus 

NAME = libft.a
CFLAGS = -Wall -Wextra -Werror

SRCS = 	ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strlen.c \
		ft_strlcpy.c \
		ft_striteri.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_strncmp.c \
		ft_atoi.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_split_charset.c \
		ft_split_char_2.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_printf.c \
		ft_printf_utils.c \
		ft_printf_utils_2.c \
		ft_printf_fd.c \
		ft_printf_fd_utils.c \
		get_next_line_bonus.c \
		get_next_line_utils_bonus.c \
		

SRCS_BONUS = ft_lstnew_bonus.c \
	  		ft_lstadd_front_bonus.c \
	  		ft_lstsize_bonus.c \
	  		ft_lstlast_bonus.c \
	  		ft_lstadd_back_bonus.c \
	  		ft_lstdelone_bonus.c \
	  		ft_lstclear_bonus.c \
	  		ft_lstiter_bonus.c \
	  		ft_lstmap_bonus.c

LIST_HEADERS = libft.h get_next_line_bonus.h ft_printf.h
LIST_OBJS = $(SRCS:.c=.o)
LIST_OBJS_BONUS = $(SRCS_BONUS:.c=.o)


DIR_HEADERS = ./
DIR_OBJS = .objs/

OBJS_BONUS = $(addprefix $(DIR_OBJS), $(LIST_OBJS_BONUS))
OBJS = $(addprefix $(DIR_OBJS),$(LIST_OBJS))
HEADERS = $(addprefix $(DIR_HEADERS), $(LIST_HEADERS))

all : $(NAME)

$(NAME) : $(DIR_OBJS) $(OBJS) $(HEADERS) Makefile
	ar rcs ${NAME} ${OBJS}

$(DIR_OBJS)%.o: %.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) -c $<  -o $@ -I $(DIR_HEADERS)

clean:
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean $(NAME)

bonus : $(DIR_OBJS) $(OBJS_BONUS) $(HEADERS) Makefile
	ar rcs ${NAME} ${OBJS_BONUS}

$(DIR_OBJS) :
	mkdir -p $(DIR_OBJS)
