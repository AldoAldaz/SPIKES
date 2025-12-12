# Arquitectura del Proyecto

Este documento describe la estructura técnica de **SPIKES!**.

## Flujo del Programa (Game Loop)

El juego utiliza un bucle principal estándar de SFML que gestiona tres fases en cada frame (60 FPS):

1.  **Input (Entrada):** Procesa teclado y mouse.
2.  **Update (Actualización):** Calcula física, movimiento de obstáculos y colisiones.
3.  **Render (Dibujado):** Limpia la pantalla y dibuja la nueva posición de los elementos.

## Máquina de Estados

El juego utiliza una máquina de estados finitos simple (`enum EstadoJuego`) para gestionar la navegación:

- `MENU`: Espera input del usuario para iniciar.
- `JUGANDO`: Ejecuta la lógica del juego.
- `GAMEOVER`: Muestra resultados y permite reiniciar.

## Generación Procedural

Los obstáculos se generan mediante un algoritmo de probabilidad ponderada:

- **Longitud:** Decide aleatoriamente si generar una columna simple o un "túnel" (grupo de columnas).
- **Dificultad:** Asigna una apertura (Fácil/Media/Difícil) con un 33% de probabilidad cada una.
