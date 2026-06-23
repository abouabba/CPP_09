CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
NAME = btc
SRCS = main.cpp BitcoinExchange.cpp
HEADRS = BitcoinExchange.hpp
OBGS = ${SRCS:.cpp=.o}

all: ${NAME}

${NAME}: ${OBGS}
	${CC} ${CFLAGS} -o ${NAME} ${OBGS}

%.o: %.cpp ${HEADRS}
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -rf ${OBGS}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: clean