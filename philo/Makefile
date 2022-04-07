CC	= gcc
FLAGS	= -Wall -Wextra -Werror
RM	= rm -f
PFLAG	= -pthread
NAME	= philo
INCLUDE	= -I include
SRC	= srcs/
FILES	= philo.c \
	  init.c \
	  life.c \
	  utils.c
SRCS	= $(addprefix $(SRC), $(FILES))
OBJS	= $(SRCS:%.c=%.o)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(PFLAG) $(INCLUDE) $(OBJS) -o $(NAME)

all: $(NAME)

clean:	
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: $(NAME)
	@echo "\n\n1 philosopher"
	./philo 1 10 10 10
	@echo "\n\n1 philosopher + meal"
	./philo 1 10 10 10 2
	@echo "\n\n2 philosophers die"
	./philo 2 10 10 10
	@echo "\n\n10 philosophers die"
	./philo 10 10 10 10
	@echo "\n\n2 philosophers finish 3 meals"
	./philo 2 100 10 10 3
	@echo "\n\n10 philosophers finish 2 meals"
	./philo 10 100 10 10 2

leaks: $(NAME)
	@echo "\n\n1 philosopher"
	leaks --atExit -- ./philo 1 10 10 1
	@echo "\n\n1 philosopher + meal"
	leaks --atExit -- ./philo 1 10 10 10 2
	@echo "\n\n2 philosophers die"
	leaks --atExit -- ./philo 2 10 10 10
	@echo "\n\n10 philosophers die"
	leaks --atExit -- ./philo 10 10 10 10
	@echo "\n\n2 philosophers finish 3 meals"
	leaks --atExit -- ./philo 2 100 10 10 3
	@echo "\n\n10 philosophers finish 2 meals"
	leaks --atExit -- ./philo 10 100 10 10 2

.PHONY: all clean fclean re philo
