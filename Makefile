CXX	:=	clang++
CXXFLAGS	:=	-std=c++20 -Wall -Wextra
CPPFLAGS	:=	-I ./include/

ifeq ($(ENV), dev)
	CXXFLAGS	+=	-fsanitize=address
	LDLIBS	+=	-fsanitize=address
endif

ifeq ($(ENV), dev-g3)
	CXXFLAGS	+=	-g3
endif

SRC	:=	src/main.cpp

OBJ	:=	$(SRC:.cpp=.o)

BINARY	:=	raytracer

all:	$(BINARY)

$(BINARY):	$(OBJ)
	$(CXX) -o $(BINARY) $(OBJ) $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(BINARY)

re:	fclean all

.PHONY:	all clean fclean re
