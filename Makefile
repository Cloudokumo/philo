NAME	=	philo

CC		=	gcc
INCLUDE	=	includes
CFLAGS	=	-Wall -Wextra -Werror -I$(INCLUDE)
RM		=	rm -f

SRCS	=	srcs/philo.c \
			srcs/utils.c \
			srcs/initialization.c \
			srcs/philo_help.c \
			srcs/philo_routine.c 

OBJS	=	$(SRCS:%.c=%.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

.c.o:
			@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
			@$(RM) $(OBJS)
			
fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re