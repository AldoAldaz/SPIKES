#include "Obstaculos.hpp"

// Implementación de la función
sf::ConvexShape crearHitboxPincho(float anchoBase, float alturaPunta, bool apuntaHaciaArriba)
{
    sf::ConvexShape pincho;
    pincho.setPointCount(3);
    if (apuntaHaciaArriba)
    {
        pincho.setPoint(0, sf::Vector2f(0, alturaPunta));
        pincho.setPoint(1, sf::Vector2f(anchoBase, alturaPunta));
        pincho.setPoint(2, sf::Vector2f(anchoBase / 2, 0));
    }
    else
    {
        pincho.setPoint(0, sf::Vector2f(0, 0));
        pincho.setPoint(1, sf::Vector2f(anchoBase, 0));
        pincho.setPoint(2, sf::Vector2f(anchoBase / 2, alturaPunta));
    }
    pincho.setFillColor(sf::Color(255, 0, 0, 0)); // Invisible
    return pincho;
}