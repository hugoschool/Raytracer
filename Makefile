CXX	:=	clang++
CXXFLAGS	:=	-std=c++20 -Wall -Wextra -O3
CPPFLAGS	:=	-I ./include/
LDLIBS	:=	-lconfig++

ifeq ($(ENV), dev)
	CXXFLAGS	+=	-fsanitize=address
	LDLIBS	+=	-fsanitize=address
endif

ifeq ($(ENV), dev-g3)
	CXXFLAGS	+=	-g3
endif

MATH_SRC	:=	src/Math/Point3D.cpp \
				src/Math/Rectangle3D.cpp \
				src/Math/Vector3D.cpp \
				src/Math/Matrix3x3.cpp \
				src/Math/Matrix3x1.cpp

LIGHT_SRC := src/lights/Light.cpp

PRIMITIVES_SRC	:=	src/primitives/Sphere.cpp
				

SRC	:=	$(MATH_SRC) \
		$(PRIMITIVES_SRC) \
		$(LIGHT_SRC) \
		src/main.cpp \
		src/Raytracer.cpp \
		src/Camera.cpp \
		src/Ray.cpp \
		src/HitInfo.cpp

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
