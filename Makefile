CC = c++ 

SRC =  src/parsing/parsing.cpp src/parsing/error_codes.cpp src/parsing/parsing1.cpp src/parsing/send.cpp src/parsing/parsing2.cpp src/parsing/parsing_request.cpp\
		src/networking/Client.cpp src/networking/main.cpp src/networking/Server.cpp

NAME = webserv

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(SRC) -o $(NAME)

clean:
	rm -f $(NAME) 

fclean: clean	
	rm -f $(NAME) 

re : fclean all