CC = gcc 
CREAT = ar -rc
# CFLAGS = -Wall -Werror -Wextra
RM = rm -f
FILES = ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_strlen \
	   ft_toupper ft_tolower ft_strchr ft_strrchr ft_strcmp \
	   ft_strnstr ft_strlcpy ft_strlcat ft_atoi ft_strdup \
	   ft_substr  ft_memcpy ft_memmove ft_memset ft_strncmp \
	   ft_memcmp ft_memchr ft_bzero ft_calloc \
	   ft_strjoin ft_strtrim ft_split ft_itoa ft_strmapi ft_striteri\
	   ft_putchar_fd ft_isprint ft_putendl_fd ft_putstr_fd ft_putnbr_fd

OBJ = $(FILES:=.o)
NAME = libft.a


all: $(NAME)

$(NAME): $(OBJ)
	$(CREAT) $(NAME) $(OBJ)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
