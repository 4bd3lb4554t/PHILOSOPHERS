NAME = philo



SRC = $(wildcard *.c)
SRC_libft = $(wildcard libft/*.c)
OBJECTS = $(SRC:.c=.o)
OBJECTS_LIBFT = $(SRC_libft:.c=.o)

CC = cc
 
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address	# -fsanitize=thread -g3

all: $(NAME) 
	@rm -rf *.o
$(NAME): $(OBJECTS)  $(OBJECTS_LIBFT)
	@$(CC) $(CFLAGS)  $(OBJECTS)  $(OBJECTS_LIBFT) $(libft)  -o $(NAME)

%.o: %.c 
	@$(CC) $(CFLAGS) -c -o $@ $< 

clean:
	@rm -f   $(OBJECTS)  $(OBJECTS_LIBFT) && rm -rf *.o > /dev/null
fclean: clean
	@rm -rf ./philo

re: fclean all

.PHONY: all clean  fclean re bonus

.SECONDARY: 
