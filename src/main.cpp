#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

// --- DEFINICIÓN DE ESTADOS ---
enum EstadoJuego
{
    MENU,
    JUGANDO,
    GAMEOVER
};

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

// Función auxiliar Hitbox Pincho
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

// Función auxiliar para configurar texto
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

// Función auxiliar para configurar Sprites de UI
void configurarSpriteUI(sf::Sprite &sprite, sf::Texture &texture, float x, float y)
{
    sprite.setTexture(texture);
    sf::Vector2u tam = texture.getSize();
    sprite.setOrigin(tam.x / 2.0f, tam.y / 2.0f);
    sprite.setPosition(x, y);
}

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // =================================================================================
    // PARÁMETRO GLOBAL DE COLOR
    // =================================================================================
    sf::Color colorColumnasGlobal = sf::Color::White;
    // =================================================================================

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SPIKES!", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    sf::View view(sf::FloatRect(0, 0, 800, 600));
    window.setView(view);

    EstadoJuego estadoActual = MENU;

    // --- RECURSOS ---
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        std::cout << "Advertencia: Fuente no encontrada." << std::endl;
    }

    sf::Text textoScore;
    textoScore.setFont(font);
    textoScore.setString("0");
    textoScore.setCharacterSize(40);
    textoScore.setFillColor(sf::Color::White);
    textoScore.setPosition(400, 50);

    sf::Text textoAutor;
    configurarTexto(textoAutor, font, "Aldo Gael Aldaz Rosales - 24310322", 20, sf::Color::White, 400, 550);

    sf::Text textoScoreFinal;

    // TEXTURAS UI
    sf::Texture texLogo, texBtnJugar, texBtnSalir, texBtnReintentar, texBtnMenu, texGameOver;
    bool uiLoaded = true;

    if (!texLogo.loadFromFile("assets/logo.png"))
        uiLoaded = false;
    if (!texBtnJugar.loadFromFile("assets/btn_jugar.png"))
        uiLoaded = false;
    if (!texBtnSalir.loadFromFile("assets/btn_salir.png"))
        uiLoaded = false;
    if (!texBtnReintentar.loadFromFile("assets/btn_reintentar.png"))
        uiLoaded = false;
    if (!texBtnMenu.loadFromFile("assets/btn_menu.png"))
        uiLoaded = false;
    if (!texGameOver.loadFromFile("assets/img_game_over.png"))
        uiLoaded = false;

    if (!uiLoaded)
        std::cout << "ERROR: Faltan imagenes de interfaz en assets/" << std::endl;

    // CONFIGURAR SPRITES DE UI
    sf::Sprite spriteLogo, spriteBtnJugar, spriteBtnSalir, spriteGameOver, spriteBtnReintentar, spriteBtnMenu;
    if (uiLoaded)
    {
        // --- MENÚ ---
        configurarSpriteUI(spriteLogo, texLogo, 400, 150);
        spriteLogo.setScale(0.6f, 0.6f); // <--- NUEVO: Modifica el tamaño del LOGO (0.8 es un ejemplo)

        configurarSpriteUI(spriteBtnJugar, texBtnJugar, 400, 300);
        spriteBtnJugar.setScale(0.57f, 0.57f); // <--- NUEVO: Haz más chicos o grandes los botones

        configurarSpriteUI(spriteBtnSalir, texBtnSalir, 400, 420);
        spriteBtnSalir.setScale(0.25f, 0.25f); // <--- NUEVO: Aplica lo mismo al botón Salir

        // --- GAME OVER ---
        configurarSpriteUI(spriteGameOver, texGameOver, 400, 150);
        spriteGameOver.setScale(0.5f, 0.5f); // <--- NUEVO

        configurarSpriteUI(spriteBtnReintentar, texBtnReintentar, 400, 350);
        spriteBtnReintentar.setScale(0.5f, 0.5f); // <--- NUEVO

        configurarSpriteUI(spriteBtnMenu, texBtnMenu, 400, 470);
        spriteBtnMenu.setScale(0.6f, 0.6f); // <--- NUEVO
    }

    // TEXTURAS JUEGO
    sf::Texture texturaNave, texturaMuro, texturaPincho;
    bool hayNave = texturaNave.loadFromFile("assets/nave.png");
    bool hayMuro = texturaMuro.loadFromFile("assets/muro.png");
    if (hayMuro)
        texturaMuro.setRepeated(true);
    bool hayPincho = texturaPincho.loadFromFile("assets/pincho.png");

    sf::Texture texturaFondoMenu, texturaFondoJuego;
    sf::Sprite spriteFondoMenu, spriteFondoJuego;
    bool hayFondoMenu = texturaFondoMenu.loadFromFile("assets/fondo_menu.png");
    if (hayFondoMenu)
    {
        spriteFondoMenu.setTexture(texturaFondoMenu);
        spriteFondoMenu.setScale(800.0f / texturaFondoMenu.getSize().x, 600.0f / texturaFondoMenu.getSize().y);
    }
    bool hayFondoJuego = texturaFondoJuego.loadFromFile("assets/fondo_juego.png");
    if (hayFondoJuego)
    {
        spriteFondoJuego.setTexture(texturaFondoJuego);
        spriteFondoJuego.setScale(800.0f / texturaFondoJuego.getSize().x, 600.0f / texturaFondoJuego.getSize().y);
    }

    // AUDIO
    sf::Music musicaJuego;
    bool hayMusicaJuego = musicaJuego.openFromFile("assets/musica.ogg");
    if (hayMusicaJuego)
    {
        musicaJuego.setLoop(true);
        musicaJuego.setVolume(50.0f);
    }

    sf::Music musicaMenu;
    bool hayMusicaMenu = musicaMenu.openFromFile("assets/menu.ogg");
    if (hayMusicaMenu)
    {
        musicaMenu.setLoop(true);
        musicaMenu.setVolume(50.0f);
        musicaMenu.play();
    }

    sf::SoundBuffer bufferPunto, bufferChoque;
    sf::Sound sonidoPunto, sonidoChoque;
    if (bufferPunto.loadFromFile("assets/punto.wav"))
    {
        sonidoPunto.setBuffer(bufferPunto);
        sonidoPunto.setVolume(80.0f);
    }
    if (bufferChoque.loadFromFile("assets/explosion.wav"))
    {
        sonidoChoque.setBuffer(bufferChoque);
        sonidoChoque.setVolume(100.0f);
    }

    long long score = 0;

    sf::ConvexShape naveHitbox;
    naveHitbox.setPointCount(3);
    naveHitbox.setPoint(0, sf::Vector2f(0, 0));
    naveHitbox.setPoint(1, sf::Vector2f(0, 30));
    naveHitbox.setPoint(2, sf::Vector2f(40, 15));
    naveHitbox.setFillColor(sf::Color(0, 255, 255, 0));
    naveHitbox.setPosition(100, 300);
    naveHitbox.setOrigin(20, 15);

    sf::Sprite spriteNave;
    if (hayNave)
    {
        spriteNave.setTexture(texturaNave);
        sf::Vector2u tam = texturaNave.getSize();
        spriteNave.setOrigin(tam.x / 2.0f, tam.y / 2.0f);
        float escala = 90.0f / tam.x;
        spriteNave.setScale(escala, escala);
    }

    float velocidadY = 0.0f;
    float gravedad = 0.6f;
    float impulso = -0.8f;
    float velocidadMaxima = 8.0f;
    std::vector<Obstaculo> listaObstaculos;
    float velocidadJuego = 5.0f;
    int tiempoSpawn = 0;
    int framesParaNuevoSpawn = 70;
    int paresRestantesPorGenerar = 0;
    int alturaTunelPosY = 0;
    int alturaHuecoSize = 200;
    int multiplicadorActual = 1;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();

            if (estadoActual == MENU)
            {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (uiLoaded && spriteBtnJugar.getGlobalBounds().contains(mousePos))
                    {
                        estadoActual = JUGANDO;
                        naveHitbox.setPosition(100, 300);
                        velocidadY = 0;
                        listaObstaculos.clear();
                        score = 0;
                        textoScore.setString("0");
                        if (hayMusicaMenu)
                            musicaMenu.stop();
                        if (hayMusicaJuego)
                            musicaJuego.play();
                    }
                    if (uiLoaded && spriteBtnSalir.getGlobalBounds().contains(mousePos))
                    {
                        window.close();
                    }
                }
            }
            else if (estadoActual == GAMEOVER)
            {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (uiLoaded && spriteBtnReintentar.getGlobalBounds().contains(mousePos))
                    {
                        estadoActual = JUGANDO;
                        naveHitbox.setPosition(100, 300);
                        velocidadY = 0;
                        listaObstaculos.clear();
                        tiempoSpawn = 0;
                        framesParaNuevoSpawn = 70;
                        paresRestantesPorGenerar = 0;
                        score = 0;
                        textoScore.setString("0");
                        if (hayMusicaJuego)
                        {
                            musicaJuego.stop();
                            musicaJuego.play();
                        }
                    }
                    if (uiLoaded && spriteBtnMenu.getGlobalBounds().contains(mousePos))
                    {
                        estadoActual = MENU;
                        if (hayMusicaMenu)
                            musicaMenu.play();
                    }
                }
            }
        }

        if (estadoActual == JUGANDO)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                velocidadY += impulso;
            }
            else
            {
                velocidadY += gravedad;
            }
            if (velocidadY > velocidadMaxima)
                velocidadY = velocidadMaxima;
            if (velocidadY < -velocidadMaxima)
                velocidadY = -velocidadMaxima;

            naveHitbox.move(0, velocidadY);
            naveHitbox.setRotation(velocidadY * 3);
            if (hayNave)
            {
                spriteNave.setPosition(naveHitbox.getPosition());
                spriteNave.setRotation(naveHitbox.getRotation());
            }

            if (naveHitbox.getPosition().y < 0)
                naveHitbox.setPosition(naveHitbox.getPosition().x, 0);
            if (naveHitbox.getPosition().y > 600)
            {
                estadoActual = GAMEOVER;
                configurarTexto(textoScoreFinal, font, "Score Final: " + std::to_string(score), 40, sf::Color::White, 400, 250);
                if (hayMusicaJuego)
                    musicaJuego.stop();
                sonidoChoque.play();
            }

            tiempoSpawn++;
            if (tiempoSpawn >= framesParaNuevoSpawn)
            {
                if (paresRestantesPorGenerar <= 0)
                {
                    int dadoLongitud = rand() % 21;
                    if (dadoLongitud < 6)
                        paresRestantesPorGenerar = 1;
                    else if (dadoLongitud < 11)
                        paresRestantesPorGenerar = 2;
                    else if (dadoLongitud < 15)
                        paresRestantesPorGenerar = 3;
                    else if (dadoLongitud < 18)
                        paresRestantesPorGenerar = 4;
                    else if (dadoLongitud < 20)
                        paresRestantesPorGenerar = 5;
                    else
                        paresRestantesPorGenerar = 6;

                    int dadoDificultad = rand() % 3;
                    if (dadoDificultad == 0)
                    {
                        alturaHuecoSize = 200;
                        multiplicadorActual = 1;
                    }
                    else if (dadoDificultad == 1)
                    {
                        alturaHuecoSize = 170;
                        multiplicadorActual = 2;
                    }
                    else
                    {
                        alturaHuecoSize = 140;
                        multiplicadorActual = 3;
                    }

                    alturaTunelPosY = rand() % (600 - alturaHuecoSize - 100) + 50;
                }

                Obstaculo obs;
                int anchoColumna = 50;

                // =========================================================================
                // AJUSTES DE PINCHOS (¡AQUÍ MODIFICAS EL TAMAÑO!)
                // =========================================================================
                // 1. Altura (Alto): Qué tan largo es el pico hacia arriba/abajo (antes 30)
                float alturaPincho = 50.0f;

                // 2. Escala de Ancho (Grosor): Multiplicador visual.
                // 1.0 = Ancho normal del muro.
                // 1.3 = 30% más ancho (se verá más grueso y sobresaldrá)
                float escalaVisualAncho = 1.3f;
                // =========================================================================

                obs.multiplicador = multiplicadorActual;

                obs.rectTop.setSize(sf::Vector2f(anchoColumna, alturaTunelPosY));
                obs.rectTop.setPosition(850, 0);
                if (hayMuro)
                {
                    obs.rectTop.setTexture(&texturaMuro);
                    obs.rectTop.setTextureRect(sf::IntRect(0, 0, anchoColumna, alturaTunelPosY));
                    obs.rectTop.setFillColor(colorColumnasGlobal);
                }
                else
                    obs.rectTop.setFillColor(colorColumnasGlobal);

                float posYInicioAbajo = alturaTunelPosY + alturaHuecoSize;
                float alturaAbajo = 600 - (posYInicioAbajo + alturaPincho);
                obs.rectBottom.setSize(sf::Vector2f(anchoColumna, alturaAbajo));
                obs.rectBottom.setPosition(850, posYInicioAbajo + alturaPincho);
                if (hayMuro)
                {
                    obs.rectBottom.setTexture(&texturaMuro);
                    obs.rectBottom.setTextureRect(sf::IntRect(0, 0, anchoColumna, alturaAbajo));
                    obs.rectBottom.setFillColor(colorColumnasGlobal);
                }
                else
                    obs.rectBottom.setFillColor(colorColumnasGlobal);

                // PINCHO ARRIBA
                obs.spikeTop = crearHitboxPincho(anchoColumna, alturaPincho, false);
                obs.spikeTop.setPosition(850, alturaTunelPosY);
                if (hayPincho)
                {
                    obs.spriteSpikeTop.setTexture(texturaPincho);
                    sf::Vector2u tP = texturaPincho.getSize();
                    obs.spriteSpikeTop.setOrigin(tP.x / 2.0f, tP.y / 2.0f);
                    obs.spriteSpikeTop.setPosition(850 + anchoColumna / 2.0f, alturaTunelPosY + alturaPincho / 2.0f);
                    obs.spriteSpikeTop.setRotation(180);
                    // AQUÍ APLICAMOS LA ESCALA VISUAL
                    obs.spriteSpikeTop.setScale((anchoColumna * escalaVisualAncho) / (float)tP.x, alturaPincho / (float)tP.y);
                }

                // PINCHO ABAJO
                obs.spikeBottom = crearHitboxPincho(anchoColumna, alturaPincho, true);
                obs.spikeBottom.setPosition(850, posYInicioAbajo);
                if (hayPincho)
                {
                    obs.spriteSpikeBottom.setTexture(texturaPincho);
                    sf::Vector2u tP = texturaPincho.getSize();
                    obs.spriteSpikeBottom.setOrigin(tP.x / 2.0f, tP.y / 2.0f);
                    obs.spriteSpikeBottom.setPosition(850 + anchoColumna / 2.0f, posYInicioAbajo + alturaPincho / 2.0f);
                    obs.spriteSpikeBottom.setRotation(0);
                    // AQUÍ APLICAMOS LA ESCALA VISUAL
                    obs.spriteSpikeBottom.setScale((anchoColumna * escalaVisualAncho) / (float)tP.x, alturaPincho / (float)tP.y);
                }

                listaObstaculos.push_back(obs);
                paresRestantesPorGenerar--;
                if (paresRestantesPorGenerar > 0)
                    framesParaNuevoSpawn = 10;
                else
                    framesParaNuevoSpawn = 80 + (rand() % 40);
                tiempoSpawn = 0;
            }

            for (size_t i = 0; i < listaObstaculos.size(); i++)
            {
                listaObstaculos[i].rectTop.move(-velocidadJuego, 0);
                listaObstaculos[i].spikeTop.move(-velocidadJuego, 0);
                listaObstaculos[i].spriteSpikeTop.move(-velocidadJuego, 0);
                listaObstaculos[i].rectBottom.move(-velocidadJuego, 0);
                listaObstaculos[i].spikeBottom.move(-velocidadJuego, 0);
                listaObstaculos[i].spriteSpikeBottom.move(-velocidadJuego, 0);

                if (!listaObstaculos[i].contado && listaObstaculos[i].rectTop.getPosition().x + 50 < naveHitbox.getPosition().x)
                {
                    score += listaObstaculos[i].multiplicador;
                    listaObstaculos[i].contado = true;
                    sonidoPunto.play();
                    textoScore.setString(std::to_string(score));
                    sf::FloatRect bounds = textoScore.getLocalBounds();
                    textoScore.setOrigin(bounds.width / 2.0f, 0);
                }
            }
            if (!listaObstaculos.empty() && listaObstaculos[0].rectTop.getPosition().x < -100)
            {
                listaObstaculos.erase(listaObstaculos.begin());
            }

            sf::FloatRect cajaNave = naveHitbox.getGlobalBounds();
            for (auto &obs : listaObstaculos)
            {
                if (cajaNave.intersects(obs.rectTop.getGlobalBounds()) ||
                    cajaNave.intersects(obs.spikeTop.getGlobalBounds()) ||
                    cajaNave.intersects(obs.rectBottom.getGlobalBounds()) ||
                    cajaNave.intersects(obs.spikeBottom.getGlobalBounds()))
                {
                    estadoActual = GAMEOVER;
                    configurarTexto(textoScoreFinal, font, "Score Final: " + std::to_string(score), 40, sf::Color::White, 400, 250);
                    if (hayMusicaJuego)
                        musicaJuego.stop();
                    sonidoChoque.play();
                    break;
                }
            }
        }

        // --- DRAW ---
        window.clear(sf::Color::Black);

        if (estadoActual == MENU)
        {
            if (hayFondoMenu)
                window.draw(spriteFondoMenu);
            if (uiLoaded)
            {
                window.draw(spriteLogo);
                window.draw(spriteBtnJugar);
                window.draw(spriteBtnSalir);
            }
            window.draw(textoAutor);
        }
        else if (estadoActual == JUGANDO)
        {
            if (hayFondoJuego)
                window.draw(spriteFondoJuego);
            for (size_t i = 0; i < listaObstaculos.size(); i++)
            {
                window.draw(listaObstaculos[i].rectTop);
                window.draw(listaObstaculos[i].rectBottom);
                if (hayPincho)
                {
                    window.draw(listaObstaculos[i].spriteSpikeTop);
                    window.draw(listaObstaculos[i].spriteSpikeBottom);
                }
                else
                {
                    window.draw(listaObstaculos[i].spikeTop);
                    window.draw(listaObstaculos[i].spikeBottom);
                }
            }
            if (hayNave)
                window.draw(spriteNave);
            else
                window.draw(naveHitbox);
            window.draw(textoScore);
        }
        else if (estadoActual == GAMEOVER)
        {
            if (hayFondoJuego)
                window.draw(spriteFondoJuego);

            if (uiLoaded)
            {
                window.draw(spriteGameOver);
                window.draw(spriteBtnReintentar);
                window.draw(spriteBtnMenu);
            }
            window.draw(textoScoreFinal);
        }

        window.display();
    }

    return 0;
}