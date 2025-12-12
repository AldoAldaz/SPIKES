# Directorios de origen y destino
SRC_DIR := src
BIN_DIR := bin

# Librerias (SFML y Audio)
# Nota: Si usaste Box2D, agrega -lbox2d al final de esta linea
SFML := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Nombre de tu ejecutable final
TARGET := $(BIN_DIR)/SpikesGame.exe

# Obtener todos los archivos .cpp en el directorio de origen
CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)

# Regla por defecto: Compilar el juego
all:
	g++ $(CPP_FILES) -o $(TARGET) $(SFML) -Iinclude

# Regla para ejecutar el juego
run:
	./$(TARGET)

# Regla para limpiar los archivos generados
clean:
	rm -f $(BIN_DIR)/*.exe

.PHONY: all run clean