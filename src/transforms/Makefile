COMMON_SRC	:=	$(COMMON_SRC) \
				$(MATH_SRC) \
				ATransform.cpp

DEFAULT_SRC	:=	$(COMMON_SRC) \
				Default.cpp
DEFAULT_OBJ	:=	$(DEFAULT_SRC:.cpp=.o)
DEFAULT_BIN	:=	$(PLUGINS_DIR)/raytracer_transform_default.so

include $(BASE_DIR)/common.mk

all:	$(DEFAULT_BIN)

$(DEFAULT_BIN):	$(DEFAULT_OBJ)

clean:
	$(RM) $(DEFAULT_OBJ)

fclean:	clean
	$(RM) $(DEFAULT_BIN)

re:	fclean all

.PHONY:	all clean fclean re
