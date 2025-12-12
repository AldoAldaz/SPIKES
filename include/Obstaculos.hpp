#ifndef OBSTACULOS_HPP
#define OBSTACULOS_HPP

#include <SFML/Graphics.hpp>

// Estructura de obstáculo
struct Obstaculo
{
    sf::RectangleShape rectTop;
    sf::ConvexShape spikeTop;
    sf::Sprite spriteSpikeTop;

    sf::RectangleShape rectBottom;
    sf::ConvexShape spikeBottom;
    sf::Sprite spriteSpikeBottom;

    bool contado = false;
    int multiplicador = 1;
};

// Declaración de la función (Prototipo)
sf::ConvexShape crearHitboxPincho(float anchoBase, float alturaPunta, bool apuntaHaciaArriba);

#endif