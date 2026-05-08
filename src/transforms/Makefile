COMMON_SRC	:=	$(COMMON_SRC) \
				$(MATH_SRC) \
				ATransform.cpp

DEFAULT_SRC	:=	$(COMMON_SRC) \
				Default.cpp
DEFAULT_OBJ	:=	$(DEFAULT_SRC:.cpp=.o)
DEFAULT_BIN	:=	$(PLUGINS_DIR)/raytracer_transform_default.so

SCALE_SRC	:=	$(COMMON_SRC) \
				Scale.cpp
SCALE_OBJ	:=	$(SCALE_SRC:.cpp=.o)
SCALE_BIN	:=	$(PLUGINS_DIR)/raytracer_transform_scale.so

include $(BASE_DIR)/common.mk

all:	$(DEFAULT_BIN) $(SCALE_BIN)

$(DEFAULT_BIN):	$(DEFAULT_OBJ)

$(SCALE_BIN):	$(SCALE_OBJ)

clean:
	$(RM) $(DEFAULT_OBJ)
	$(RM) $(SCALE_OBJ)

fclean:	clean
	$(RM) $(DEFAULT_BIN)
	$(RM) $(SCALE_BIN)

re:	fclean all

.PHONY:	all clean fclean re
