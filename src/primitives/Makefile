COMMON_SRC	:=	$(COMMON_SRC) \
				$(MATH_SRC) \
				APrimitive.cpp

SPHERE_SRC	:=	$(COMMON_SRC) \
				Sphere.cpp
SPHERE_OBJ	:=	$(SPHERE_SRC:.cpp=.o)
SPHERE_BIN	:=	$(PLUGINS_DIR)/raytracer_primitive_sphere.so

CYLINDER_SRC	:=	$(COMMON_SRC) \
				Cylinder.cpp
CYLINDER_OBJ	:=	$(CYLINDER_SRC:.cpp=.o)
CYLINDER_BIN	:=	$(PLUGINS_DIR)/raytracer_primitive_cylinder.so

PLANE_SRC	:=	$(COMMON_SRC) \
				Plane.cpp
PLANE_OBJ	:=	$(PLANE_SRC:.cpp=.o)
PLANE_BIN	:=	$(PLUGINS_DIR)/raytracer_primitive_plane.so

TRIANGLE_SRC	:=	$(COMMON_SRC) \
				Triangle.cpp
TRIANGLE_OBJ	:=	$(TRIANGLE_SRC:.cpp=.o)
TRIANGLE_BIN	:=	$(PLUGINS_DIR)/raytracer_primitive_triangle.so

CUBE_SRC	:=	$(COMMON_SRC) \
				Cube.cpp
CUBE_OBJ	:=	$(CUBE_SRC:.cpp=.o)
CUBE_BIN	:=	$(PLUGINS_DIR)/raytracer_primitive_cube.so

include $(BASE_DIR)/common.mk

all:	$(SPHERE_BIN) $(PLANE_BIN) $(TRIANGLE_BIN) $(CUBE_BIN) $(CYLINDER_BIN)

$(SPHERE_BIN):	$(SPHERE_OBJ)

$(CYLINDER_BIN):	$(CYLINDER_OBJ)

$(PLANE_BIN):	$(PLANE_OBJ)

$(TRIANGLE_BIN): $(TRIANGLE_OBJ)

$(CUBE_BIN): $(CUBE_OBJ)

clean:
	$(RM) $(SPHERE_OBJ)
	$(RM) $(PLANE_OBJ)
	$(RM) $(TRIANGLE_OBJ)
	$(RM) $(CYLINDER_OBJ)
	$(RM) $(CUBE_OBJ)

fclean:	clean
	$(RM) $(SPHERE_BIN)
	$(RM) $(PLANE_BIN)
	$(RM) $(TRIANGLE_BIN)
	$(RM) $(CYLINDER_BIN)
	$(RM) $(CUBE_BIN)

re:	fclean all

.PHONY:	all clean fclean re
