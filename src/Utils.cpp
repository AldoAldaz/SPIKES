#include "Utils.hpp"

void configurarTexto(sf::Text &texto, sf::Font &fuente, std::string mensaje, int tamano, sf::Color color, float x, float y)
{
    texto.setFont(fuente);
    texto.setString(mensaje);
    texto.setCharacterSize(tamano);
    texto.setFillColor(color);
    sf::FloatRect bounds = texto.getLocalBounds();
    texto.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    texto.setPosition(x, y);
}

void configurarSpriteUI(sf::Sprite &sprite, sf::Texture &texture, float x, float y)
{
    sprite.setTexture(texture);
    sf::Vector2u tam = texture.getSize();
    sprite.setOrigin(tam.x / 2.0f, tam.y / 2.0f); // Centrar origen
    sprite.setPosition(x, y);
}