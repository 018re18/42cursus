NAME		= brain

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98
RM			= rm -f

SRCS		= main.cpp Animal.cpp Dog.cpp Cat.cpp Brain.cpp \
			  WrongAnimal.cpp WrongCat.cpp
OBJS		= $(SRCS:.cpp=.o)
HEADERS		= Animal.hpp Dog.hpp Cat.hpp Brain.hpp \
			  WrongAnimal.hpp WrongCat.hpp

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o:		%.cpp $(HEADERS)
			$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
