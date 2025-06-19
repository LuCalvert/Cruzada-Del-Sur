# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -Wextra -I.

# Archivos fuente y ejecutable
SRC = main.cpp \
      CampoDeBatalla.cpp \
      Carta.cpp \
      CartaReabastecimiento.cpp \
      CartaTropa.cpp \
      Jugador.cpp \
      LectorCartas.cpp \
      Mapa.cpp

OBJ = $(SRC:.cpp=.o)
EXEC = cruzada_del_sur

# Regla por defecto
all: $(EXEC)

# Enlazado
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilación de archivos .cpp a .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -f $(OBJ) $(EXEC)

# Para evitar que se interpreten como archivos
.PHONY: all clean
