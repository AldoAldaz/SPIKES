# SPIKES!

Un videojuego de habilidad y precisión inspirado en la mecánica de "nave" de Geometry Dash y el estilo de Flappy Bird.
El proyecto está desarrollado sobre MinGW64 utilizando Msys2 y Visual Studio Code.

## Prerequisitos

Para compilar y ejecutar este proyecto necesitas:

- Compilador de C++ (g++)
- Herramientas de construcción (Make)
- Librería SFML (Graphics, Window, System, Audio)

## Estructura del Proyecto

- **src/**: Código fuente del juego (main.cpp).
- **include/**: Archivos de cabecera (.hpp).
- **assets/**: Recursos multimedia.
  - `images/`: Sprites y texturas.
  - `music/`: Música y efectos de sonido.
  - `fonts/`: Tipografías.
- **bin/**: Ejecutable compilado.

## Como ejecutar el juego

1. Asegúrate de tener todas las dependencias instaladas.
2. Abre una terminal en la raíz del proyecto.
3. Compila el juego con el comando:

   > make

4. Ejecuta el juego con el comando:
   > make run

## Controles

- **Clic Izquierdo / Espacio**: Impulsar la nave hacia arriba.
- **Esc**: Salir del juego (o desde el menú).

## Créditos

- **Desarrollado por:** Aldo Gael Aldaz Rosales
- **Materia:** Programación Avanzada
