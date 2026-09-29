NAME		= aform

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98
RM			= rm -f

SRCS		= main.cpp Bureaucrat.cpp AForm.cpp \
			  ShrubberyCreationForm.cpp RobotomyRequestForm.cpp \
			  PresidentialPardonForm.cpp
OBJS		= $(SRCS:.cpp=.o)
HEADERS		= Bureaucrat.hpp AForm.hpp \
			  ShrubberyCreationForm.hpp RobotomyRequestForm.hpp \
			  PresidentialPardonForm.hpp

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o:		%.cpp $(HEADERS)
			$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)
			$(RM) *_shrubbery

re:			fclean all

.PHONY:		all clean fclean re
