COMMON_SRC	:=	$(COMMON_SRC) \
				AGraphical.cpp

SFML_SRC	:=	$(COMMON_SRC) \
				SFML.cpp
SFML_OBJ	:=	$(SFML_SRC:.cpp=.o)
SFML_BIN	:=	$(PLUGINS_DIR)/raytracer_graphical_sfml.so

include $(BASE_DIR)/common.mk

all:	$(SFML_BIN)

$(SFML_BIN):	LDLIBS	+=	-lsfml-system -lsfml-graphics -lsfml-window
$(SFML_BIN):	$(SFML_OBJ)

clean:
	$(RM) $(SFML_OBJ)

fclean:	clean
	$(RM) $(SFML_BIN)

re:	fclean all

.PHONY:	all clean fclean re
