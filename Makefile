NAME	=	webserv

UTILS	= src/parsing/error_codes.cpp  src/parsing/Response.cpp  src/parsing/Response_pars.cpp src/parsing/parsing_request.cpp src/CGI/cgi.cpp\
		src/networking/Client.cpp src/networking/main.cpp src/networking/Server.cpp src/parse/parsing.cpp src/parse/locationconf.cpp src/parse/handle_files.cpp

FLAGS	=	-Wall -Wextra -Werror -std=c++98 -fsanitize=address

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