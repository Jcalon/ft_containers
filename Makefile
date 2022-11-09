SHELL := /bin/bash

NAME	= ft_containers

NAME_STD = std_containers

OBJS_PATH = objs/
DEPS_PATH = deps/

SRCS 	=	main.cpp

OBJS 		= ${SRCS:%.cpp=${OBJS_PATH}%.o}
OBJS_STD	= ${SRCS:%.cpp=%.o}
DEPS		= ${SRCS:%.cpp=${DEPS_PATH}%.d}

CXX 		= c++
CXXFLAGS 	= -Wall -Wextra -Werror -std=c++98

INCLUDES = -I containers

all: 	${NAME}

${OBJS_PATH}%.o: %.cpp ${DEPS_PATH}%.d
		@mkdir -p ${@D}
		${CXX} ${CXXFLAGS} ${INCLUDES} -MMD -MF ${DEPS_PATH}$*.d -c $< -o $@

${DEPS_PATH}%.d: %.cpp
		@mkdir -p ${@D}

${NAME}: Makefile ${OBJS}
		@echo -e "\n----Compiling ft_containers----\n"
		${CXX} ${CXXFLAGS} ${OBJS} ${INCLUDES} -o ${NAME}
		@echo -e "\nft_containers Compiled!\n"

-include ${DEPS}

.cpp.o:
		$(CXX) $(CXXFLAGS) ${INCLUDES} -D TEST=1  -c -o $@ $<

${NAME_STD}: ${OBJS_STD}
		@echo -e "\n----Compiling std_containers----\n"
		${CXX} ${CXXFLAGS} ${OBJS_STD} ${INCLUDES} -D TEST=1 -o ${NAME_STD}
		@echo -e "\nstd_containers Compiled!\n"

standard: ${NAME_STD}

diff:	all standard
		@./ft_containers > TEST.tmp
		@./std_containers > TEST_STD.tmp
		@diff TEST.tmp TEST_STD.tmp; [ $$? -eq 1 ]
		@rm TEST.tmp TEST_STD.tmp

time:	all standard
		time ./ft_containers > TEST.tmp
		@sleep 1
		@echo -e "\n"
		time ./std_containers > TEST_STD.tmp
		@rm TEST.tmp TEST_STD.tmp

clean:
		@rm -rf ${OBJS_PATH}
		@rm -rf ${DEPS_PATH}
		@rm -f ${OBJS_STD}

fclean: clean
		@rm -f ${NAME} ${NAME_STD}
		@echo -e "\nDeleting everything!\n"

re:		fclean 
		make all

bonus: ${NAME_BONUS}

re_bonus: fclean bonus

.PHONY: all clean fclean re re_bonus bonus