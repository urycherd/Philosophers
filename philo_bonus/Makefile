# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/11 11:28:30 by urycherd          #+#    #+#              #
#    Updated: 2022/07/18 12:43:27 by urycherd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 	philo

SRCS =	main_bonus.c parse_bonus.c utils_bonus.c simulation_bonus.c
OBJS = 	$(SRCS:.c=.o)

HEAD =	philo_bonus.h

CC = 	cc
FLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g
RM = 	rm -f

all:	$(NAME)

$(NAME): $(OBJS) $(HEAD)
	$(CC) $(FLAGS) $(OBJS) -I $(HEAD) -o $(NAME)


bonus: $(NAME)

.c.o: $(HEAD)
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

clean:
	${RM} ${OBJS} $(B_OBJS)

fclean: clean
	$(RM) $(NAME) $(B_NAME)

re: fclean all

.PHONY: all clean fclean re bonus