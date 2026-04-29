COMMON_SRC	:=	$(COMMON_SRC) \
				$(MATH_SRC) \
				AMaterial.cpp

FLAT_COLOR_SRC	:=	$(COMMON_SRC) \
					FlatColor.cpp
FLAT_COLOR_OBJ	:=	$(FLAT_COLOR_SRC:.cpp=.o)
FLAT_COLOR_BIN	:=	$(PLUGINS_DIR)/raytracer_material_flatcolor.so

include $(BASE_DIR)/common.mk

all:	$(FLAT_COLOR_BIN)

$(FLAT_COLOR_BIN): $(FLAT_COLOR_OBJ)

clean:
	$(RM) $(FLAT_COLOR_OBJ)

fclean:	clean
	$(RM) $(FLAT_COLOR_OBJ)

re:	fclean all

.PHONY:	all clean fclean re
