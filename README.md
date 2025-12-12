# SPIKES!

## 📝 Descripción del Proyecto

**SPIKES!** es un videojuego de habilidad y precisión inspirado en la mecánica de "nave" de Geometry Dash y el estilo arcade de Flappy Bird. El jugador debe pilotar una nave espacial a través de túneles generados procedimentalmente, esquivando muros y pinchos mortales.

El proyecto está diseñado con una arquitectura modular en C++, separando la lógica del juego, las definiciones y las utilidades para mantener un código limpio y escalable.

### 🎯 Objetivo del Juego

El objetivo principal es sobrevivir el mayor tiempo posible volando a través de un túnel infinito. El jugador debe acumular la mayor puntuación posible cruzando las columnas de obstáculos sin chocar. A mayor dificultad del obstáculo cruzado, mayor será la recompensa en puntos.

### 🎮 Controles

- **Clic Izquierdo / Barra Espaciadora**: Volar (Impulso vertical hacia arriba).
- **Gravedad**: Al soltar el control, la nave cae automáticamente.
- **ESC**: Salir del juego (funciona en el Menú y durante el juego).
- **Mouse**: Interacción con los botones del menú (Jugar, Salir, Reintentar).

### ⚙️ Mecánicas

- **Física de Vuelo**: Sistema de gravedad constante con impulso instantáneo para simular el vuelo de una nave arcade.
- **Generación Procedural Ponderada**: Los obstáculos no son totalmente aleatorios; el juego decide inteligentemente cuándo crear columnas simples o "túneles" largos, y qué tan estrechos serán.
- **Sistema de Riesgo/Recompensa**:
  - Huecos grandes (Fáciles) = x1 Puntos.
  - Huecos medianos (Normales) = x2 Puntos.
  - Huecos estrechos (Difíciles) = x3 Puntos.
- **Máquina de Estados**: Gestión fluida entre el Menú Principal, la Partida (Gameplay) y la pantalla de Game Over.
- **Colisiones Precisas**: Uso de Hitboxes invisibles (Triangulares y Rectangulares) separadas de los Sprites visuales para una detección de choque justa.

### 🏆 Características

- Generación infinita de niveles (Endless Runner).
- Dificultad progresiva mediante variación de apertura de obstáculos.
- Sistema de puntuación con multiplicadores visuales.
- Efectos de sonido y música de fondo con gestión de estados (la música cambia según la pantalla).
- Interfaz gráfica (UI) personalizada con botones reactivos.
- Soporte para Pantalla Completa (Fullscreen) con ajuste de vista (View) independiente de la resolución.

### 👥 Equipo

- **Líder/Desarrollador**: Aldo Gael Aldaz Rosales (24310322)

### 🛠️ Tecnologías

- **Lenguaje**: C++ (Estándar C++17)
- **Librería Multimedia**: SFML (Simple and Fast Multimedia Library) 2.5+
- **Compilador**: MinGW (g++)
- **Sistema de Construcción**: GNU Make
- **Entorno**: Visual Studio Code con MSYS2

### 📜 Créditos

- **Assets Gráficos**: Kenney Assets (Space Shooter / Platformer Pack).
- **Fuentes**: Tipografía estilo Arcade/Pixel (DaFont).
- **Efectos de Sonido**: Recursos libres de copyright (OpenGameArt).
- **Agradecimientos**: Al profesor de Programación Avanzada Jose Ramon Navarro Marquez por la guía en la arquitectura del repositorio y el uso de Makefiles.

---

## 🚀 Instrucciones de Instalación y Ejecución

Para compilar y ejecutar este proyecto en un entorno Windows con MinGW:

1. **Compilar el juego:**
   Abre la terminal en la carpeta raíz del proyecto y ejecuta:
   ```bash
   mingw32-make
   ```
