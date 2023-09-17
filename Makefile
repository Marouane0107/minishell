CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

NAME = minishell

SRCS = mini/main.c mini/linkd_list.c mini/utils.c mini/utils1.c mini/parss.c mini/utils2.c mini/utils3.c builtins/cd.c builtins/env.c \
		builtins/echo.c builtins/exit.c builtins/pwd.c builtins/unset.c builtins/export.c mini/excution.c mini/utils4.c \
		mini/changing_files.c mini/get_env.c mini/filldata.c  mini/openherd.c mini/utils5.c mini/utils6.c mini/free.c mini/excution_utils.c 

OBJS = $(SRCS:.c=.o)


all: $(NAME)
$(NAME): $(OBJS)
	@make all -C mini/libft
	$(CC)  $(CFLAGS) $(OBJS) mini/libft/libft.a -lreadline  -o $(NAME)  
	
clean:
	@rm -f $(OBJS)
	@make clean -C mini/libft

fclean: clean
	@rm -f $(NAME)
	@ rm -f mini/libft/libft.a

re: fclean all
