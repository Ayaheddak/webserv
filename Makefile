NAME	=	webserv

UTILS	=	 src/parsing/parsing.cpp src/parsing/error_codes.cpp src/parsing/parsing1.cpp src/parsing/Response.cpp src/parsing/parsing2.cpp src/parsing/parsing_request.cpp\
		src/request/Client.cpp src/networking/main.cpp src/networking/Server.cpp

FLAGS	=	-Wall -Wextra -Werror -std=c++98 -fsanitize=address -g

RM		=	rm -f

CC		=	c++

OBJS 	= ${UTILS:.cpp=.o}

all		:	$(NAME)

$(NAME)	:	$(UTILS)	
	@$(CC) $(FLAGS) $(UTILS) -o $(NAME)

clean :
	@${RM} $(OBJCT)

fclean :	clean
	@${RM} ${NAME}

re : fclean all