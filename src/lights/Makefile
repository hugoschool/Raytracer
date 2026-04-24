COMMON_SRC	:=	$(COMMON_SRC) \
				$(MATH_SRC) \
				ALight.cpp

POINT_LIGHT_SRC	:=	$(COMMON_SRC) \
				PointLight.cpp
POINT_LIGHT_OBJ	:=	$(POINT_LIGHT_SRC:.cpp=.o)
POINT_LIGHT_BIN	:=	$(PLUGINS_DIR)/raytracer_light_point.so

include $(BASE_DIR)/common.mk

all:	$(POINT_LIGHT_BIN)

$(POINT_LIGHT_BIN):	$(POINT_LIGHT_OBJ)

clean:
	$(RM) $(POINT_LIGHT_OBJ)

fclean:	clean
	$(RM) $(POINT_LIGHT_BIN)

re:	fclean all

.PHONY:	all clean fclean re
