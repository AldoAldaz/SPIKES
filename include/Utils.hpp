#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics.hpp>
#include <string>

// Declaración de funciones auxiliares
void configurarTexto(sf::Text &texto, sf::Font &fuente, std::string mensaje, int tamano, sf::Color color, float x, float y);
void configurarSpriteUI(sf::Sprite &sprite, sf::Texture &texture, float x, float y);

#endif