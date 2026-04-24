BASE_DIR	:=	$(realpath .)
PLUGINS_DIR	:=	$(BASE_DIR)/plugins

CXX	:=	clang++
CXXFLAGS	:=	-std=c++20 -Wall -Wextra -O3
CPPFLAGS	:=	-I $(BASE_DIR)/include/
LDLIBS	:=	-lconfig++

ifeq ($(ENV), dev)
	CXXFLAGS	+=	-fsanitize=address
	LDLIBS	+=	-fsanitize=address
endif

ifeq ($(ENV), dev-g3)
	CXXFLAGS	+=	-g3
endif

MATH_SRC	:=	$(BASE_DIR)/src/Math/Point3D.cpp \
				$(BASE_DIR)/src/Math/Rectangle3D.cpp \
				$(BASE_DIR)/src/Math/Vector3D.cpp \
				$(BASE_DIR)/src/Math/Matrix3x3.cpp \
				$(BASE_DIR)/src/Math/Matrix3x1.cpp

# Shared between the main core and the plugins
COMMON_SRC	:=	$(BASE_DIR)/src/HitInfo.cpp

# Make all calls to other makefiles inherit those variables
export BASE_DIR
export PLUGINS_DIR
export CXX
export CXXFLAGS
export CPPFLAGS
export LDFLAGS
export LDLIBS
export MATH_SRC
export COMMON_SRC

# Disable "Entering directory" for every -C option
MAKEFLAGS += --no-print-directory

LIGHT_SRC :=	src/lights/ALight.cpp \
				src/lights/PointLight.cpp

SRC	:=	$(COMMON_SRC) \
		$(MATH_SRC) \
		$(LIGHT_SRC) \
		src/main.cpp \
		src/Raytracer.cpp \
		src/Camera.cpp \
		src/Ray.cpp

OBJ	:=	$(SRC:.cpp=.o)

BINARY	:=	raytracer

all:	plugins .WAIT $(BINARY)

plugins: primitives

primitives:
	$(MAKE) -C src/primitives

$(BINARY):	$(OBJ)
	$(CXX) -o $(BINARY) $(OBJ) $(LDFLAGS) $(LDLIBS)

clean:
	$(MAKE) -C src/primitives clean
	$(RM) $(OBJ)

fclean:	clean
	$(MAKE) -C src/primitives fclean
	$(RM) $(BINARY)

re:	fclean all

.PHONY:	all clean fclean re
