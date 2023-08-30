CC = CC
CFLAGS = -Wall -Werror -Wextra 
RM = rm -f
FILES = pipex utils ft_split get_next_line_utils pars

FILESB = pipex_bonus here_cmd_bonus utils_bonus pars_bonus ft_split_bonus \
get_next_line_bonus get_next_line_utils_bonus
OBJ = $(FILES:=.o)
OBJB = $(FILESB:=.o)

NAME = pipex
NAME2 = pipex_bonus


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) 

bonus : $(NAME2)

$(NAME2) : $(OBJB)
		$(CC) -o $(NAME2) $(OBJB)  

clean:
	@$(RM) $(OBJ) $(OBJB)

fclean: clean
	@$(RM) $(NAME) $(NAME2)

re: fclean all bonus
