SPHERE_SRC	:=	Sphere.cpp
SPHERE_OBJ	:=	$(SPHERE_SRC:.cpp=.o)
SPHERE_BIN	:=	$(PLUGINS_DIR)/raytracer_primitive_sphere.so

include $(BASE_DIR)/common.mk

all:	$(SPHERE_BIN)

$(SPHERE_BIN):	$(SPHERE_OBJ)

clean:
	$(RM) $(SPHERE_OBJ)

fclean:	clean
	$(RM) $(SPHERE_BIN)

re:	fclean all

.PHONY:	all clean fclean re
