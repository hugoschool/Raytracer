COMMON_SRC	:=	$(COMMON_SRC) \
				$(MATH_SRC) \
				AMaterial.cpp

FLAT_COLOR_SRC	:=	$(COMMON_SRC) \
					FlatColor.cpp
FLAT_COLOR_OBJ	:=	$(FLAT_COLOR_SRC:.cpp=.o)
FLAT_COLOR_BIN	:=	$(PLUGINS_DIR)/raytracer_material_flatcolor.so


METALLIC_SRC	:=	$(COMMON_SRC) \
					Metallic.cpp
METALLIC_OBJ	:=	$(METALLIC_SRC:.cpp=.o)
METALLIC_BIN	:=	$(PLUGINS_DIR)/raytracer_material_metallic.so

TRANSPARENT_SRC	:=	$(COMMON_SRC) \
					Transparent.cpp
TRANSPARENT_OBJ	:=	$(TRANSPARENT_SRC:.cpp=.o)
TRANSPARENT_BIN	:=	$(PLUGINS_DIR)/raytracer_material_transparent.so

CHESSBOARD_SRC	:=	$(COMMON_SRC) \
					Chessboard.cpp
CHESSBOARD_OBJ	:=	$(CHESSBOARD_SRC:.cpp=.o)
CHESSBOARD_BIN	:=	$(PLUGINS_DIR)/raytracer_material_chessboard.so

include $(BASE_DIR)/common.mk

all:	$(FLAT_COLOR_BIN) $(METALLIC_BIN) $(TRANSPARENT_BIN) $(CHESSBOARD_BIN)

$(METALLIC_BIN): $(METALLIC_OBJ)

$(FLAT_COLOR_BIN): $(FLAT_COLOR_OBJ)

$(TRANSPARENT_BIN): $(TRANSPARENT_OBJ)

$(CHESSBOARD_BIN): $(CHESSBOARD_OBJ)

clean:
	$(RM) $(FLAT_COLOR_OBJ)
	$(RM) $(METALLIC_OBJ)
	$(RM) $(TRANSPARENT_OBJ)
	$(RM) $(CHESSBOARD_OBJ)

fclean:	clean
	$(RM) $(FLAT_COLOR_BIN)
	$(RM) $(METALLIC_BIN)
	$(RM) $(TRANSPARENT_BIN)
	$(RM) $(CHESSBOARD_BIN)

re:	fclean all

.PHONY:	all clean fclean re
