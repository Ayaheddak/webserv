CC = c++ 

SRC =  src/parsing/main.cpp src/parsing/parsing.cpp src/parsing/error_codes.cpp src/parsing/parsing1.cpp src/parsing/send.cpp src/parsing/parsing2.cpp src/parsing/parsing_request.cpp

NAME = webserv

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(SRC) -o $(NAME)

clean:
	rm -f $(NAME) 

fclean: clean	
	rm -f $(NAME) 

re : fclean all