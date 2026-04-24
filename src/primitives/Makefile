COMMON_SRC	:=	$(COMMON_SRC) \
				$(MATH_SRC) \
				APrimitive.cpp

SPHERE_SRC	:=	$(COMMON_SRC) \
				Sphere.cpp
SPHERE_OBJ	:=	$(SPHERE_SRC:.cpp=.o)
SPHERE_BIN	:=	$(PLUGINS_DIR)/raytracer_primitive_sphere.so


PLANE_SRC	:=	$(COMMON_SRC) \
				Plane.cpp
PLANE_OBJ	:=	$(PLANE_SRC:.cpp=.o)
PLANE_BIN	:=	$(PLUGINS_DIR)/raytracer_primitive_plane.so

include $(BASE_DIR)/common.mk

all:	$(SPHERE_BIN) $(PLANE_BIN)

$(SPHERE_BIN):	$(SPHERE_OBJ)

$(PLANE_BIN): $(PLANE_OBJ)

clean:
	$(RM) $(SPHERE_OBJ)
	$(RM) $(PLANE_OBJ)

fclean:	clean
	$(RM) $(SPHERE_BIN)
	$(RM) $(PLANE_OBJ)

re:	fclean all

.PHONY:	all clean fclean re
