# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tguth <tguth@student.42wolfsburg.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/24 16:09:33 by ben               #+#    #+#              #
#    Updated: 2023/02/01 05:47:26 by tguth            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_test

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

CC			= c++

RM			= rm -fr

CFLAGS		= -Wall -Wextra -Werror -std=c++98 -ggdb3

GREEN			=	\033[0;32m
RED				=	\033[0;31m
RESET			=	\033[0m

test: $(NAME)

$(NAME): $(OBJS)
		#${CC} ${CFLAGS} main.cpp -o $(NAME)
		 ${CC} ${CFLAGS} test_main.cpp -o test_main
		 ${CC} ${CFLAGS} main.cpp -o ft_test
		 ${CC} ${CFLAGS} main.cpp -o std_test -D STD
		# ./ft_test > ft_test_file && ./std_test > std_test_file
		# diff -y ./ft_test_file ./std_test_file

performance:
		${CC} ${CFLAGS} intra_main_ft.cpp -o ftcontainer
		${CC} ${CFLAGS} intra_main_std.cpp -o stdcontainer
		@echo "$(GREEN)FT times:$(RESET)"
		@time -p ./ftcontainer 42
		@echo "$(GREEN)STD times:$(RESET)"
		@time -p ./stdcontainer 42

difference:
		./ft_test > ft_test_file && ./std_test > std_test_file
		diff -y ./ft_test_file ./std_test_file

clean:
		${RM} $(OBJS) ft_test ft_test_file std_test std_test_file ftcontainer stdcontainer
		@echo "$(RED)cleaned$(RESET)"

fclean: clean
		${RM} ${NAME}
		@echo "$(RED)fcleaned$(RESET)"

re:		fclean test performance difference

.PHONY:	test performance