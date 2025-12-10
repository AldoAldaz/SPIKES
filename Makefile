# Nombre de tu ejecutable final
TARGET = bin/SpikesGame.exe

# Compilador y banderas
CXX = g++
CXXFLAGS = -Wall -std=c++17 -O2

# Librerías de SFML (Gráficos, Ventana, Sistema, Audio)
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Archivos fuente (busca todos los .cpp dentro de la carpeta src)
SRC = $(wildcard src/*.cpp)

# Regla principal: Compilar el juego
all:
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS) $(LIBS)

# Regla para limpiar (borrar el ejecutable antiguo)
clean:
	del /Q bin\*.exe