CC=CC
FLAGS= -Wall -Werror -Wextra
RM=rm -rf
NAME=pipex
BONUS=pipex_bonus

FILES = pipex ft_memmove ft_split ft_strjoin ft_strnstr ft_substr pipex_utls \
		ft_free_ppx

BFILES = pipex_bonus pipex_bonus_utls ft_memmove ft_split ft_strjoin ft_strnstr ft_substr \
		 get_next_line get_next_line_utils here_doc_bonus ft_free_bonus

OBJ=$(FILES:=.o)
BOBJ=$(BFILES:=.o)

all: $(NAME)

%_bonus.o: %_bonus.c pipex_bonus.h
	$(CC) $(FLAGS) -c $<

bonus: $(BOBJ)
	@$(CC) $(BOBJ) -o $(BONUS)

%.o: %.c pipex.h
	$(CC) $(FLAGS) -c $<

$(NAME): $(OBJ) pipex.h pipex_bonus.h
	@$(CC)  $(OBJ) -o $(NAME)

clean:
	@$(RM) $(OBJ) $(BOBJ)

fclean: clean
	@$(RM) $(NAME) $(BONUS)

re: fclean all bonus