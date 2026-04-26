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

SRC	:=	$(COMMON_SRC) \
		$(MATH_SRC) \
		src/main.cpp \
		src/Raytracer.cpp \
		src/Factory.cpp \
		src/Config.cpp \
		src/DLLoader.cpp \
		src/Camera.cpp \
		src/Ray.cpp

OBJ	:=	$(SRC:.cpp=.o)

BINARY	:=	raytracer

all:	plugins $(BINARY)

plugins: primitives lights

primitives:
	$(MAKE) -C src/primitives

lights:
	$(MAKE) -C src/lights

$(BINARY):	$(OBJ)
	$(CXX) -o $(BINARY) $(OBJ) $(LDFLAGS) $(LDLIBS)

clean:
	$(MAKE) -C src/primitives clean
	$(MAKE) -C src/lights clean
	$(RM) $(OBJ)

fclean:	clean
	$(MAKE) -C src/primitives fclean
	$(MAKE) -C src/lights fclean
	$(RM) $(BINARY)

re:	fclean all

.PHONY:	all clean fclean re
