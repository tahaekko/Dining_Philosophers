
CC = cc
FLAGS = -Wall -Werror -Wextra
NAME = philo

SRC = philo.c	philo_utils.c	philo_utils_plus.c	ft_init.c	ft_check_arg.c	ft_end.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o : %.c philo.h
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all