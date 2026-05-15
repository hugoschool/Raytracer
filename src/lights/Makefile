COMMON_SRC	:=	$(COMMON_SRC) \
				$(MATH_SRC) \
				ALight.cpp

POINT_LIGHT_SRC	:=	$(COMMON_SRC) \
				PointLight.cpp
POINT_LIGHT_OBJ	:=	$(POINT_LIGHT_SRC:.cpp=.o)
POINT_LIGHT_BIN	:=	$(PLUGINS_DIR)/raytracer_light_point.so

DIRECTIONAL_LIGHT_SRC	:=	$(COMMON_SRC) \
							DirectionalLight.cpp
DIRECTIONAL_LIGHT_OBJ	:=	$(DIRECTIONAL_LIGHT_SRC:.cpp=.o)
DIRECTIONAL_LIGHT_BIN	:=	$(PLUGINS_DIR)/raytracer_light_directional.so

include $(BASE_DIR)/common.mk

all:	$(POINT_LIGHT_BIN) $(DIRECTIONAL_LIGHT_BIN)

$(POINT_LIGHT_BIN):	$(POINT_LIGHT_OBJ)

$(DIRECTIONAL_LIGHT_BIN):	$(DIRECTIONAL_LIGHT_OBJ)

clean:
	$(RM) $(POINT_LIGHT_OBJ)
	$(RM) $(DIRECTIONAL_LIGHT_OBJ)

fclean:	clean
	$(RM) $(POINT_LIGHT_BIN)
	$(RM) $(DIRECTIONAL_LIGHT_BIN)

re:	fclean all

.PHONY:	all clean fclean re
