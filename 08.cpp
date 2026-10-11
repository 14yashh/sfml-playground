#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main() {
    sf::Clock clock;
    float speed = 600.f;
    
    int score = 0;
    bool hasScored = false;

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Sound effects and Font rendering");
    window.setFramerateLimit(60);

    sf::CircleShape sun(50.f);
    sun.setFillColor(sf::Color::Yellow);
    sun.setPosition({700.f, 0.f});

    sf::RectangleShape ground({800.f, 100.f});
    ground.setFillColor(sf::Color::Blue);
    ground.setPosition({0.f, 500.f});

    sf::Texture texture;
    if(!texture.loadFromFile("assets/mushroom.png")) {
        std::cout << "Error: Failed to load assets/mushroom.png\n";
        return -1;
    }

    sf::Sprite mushroom(texture);

    sf::Vector2u size = texture.getSize();
    mushroom.setOrigin({(float)size.x / 2, (float)size.y / 2});

    mushroom.setPosition({400.f, 300.f});
    mushroom.setScale({0.5f, 0.5f});

    sf::Font font;
    if(!font.openFromFile("assets/arial.ttf")) {
        std::cout << "Error: Failed to load assets/arial.ttf\n";
        return -1;
    }

    sf::Text scoreText(font);

    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({10.f, 10.f});


    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("assets/boom.wav")) {
        std::cout << "Error: Failed to load assets/boom.wav\n";
        return -1;
    }


    sf::Sound bounceSound(buffer); 
    bounceSound.setVolume(50.f);   

    while(window.isOpen()) {
        sf::Time dt = clock.restart();
        float dtSeconds = dt.asSeconds();
        
        while(const std::optional event = window.pollEvent()) {
            if(event->is<sf::Event::Closed>()) {
                window.close();
            }

            if(const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                if(keyEvent->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
            }
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            ground.setFillColor(sf::Color::White);
        }
        else {
            ground.setFillColor(sf::Color::Blue);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            sun.move({-0.f, -speed * dtSeconds});
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            sun.move({-speed * dtSeconds, 0.f});
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            sun.move({0.f, speed * dtSeconds});
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            sun.move({speed * dtSeconds, 0.f});
        }

        if(sun.getGlobalBounds().findIntersection(ground.getGlobalBounds())) {
            sun.setFillColor(sf::Color::Magenta);

            if(hasScored == false) {
                score++;
                scoreText.setString("Score: " + std::to_string(score));
                bounceSound.play();
                hasScored = true;
            }

        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            sun.setFillColor(sf::Color::Red);
            hasScored = false;
        }
        else {
            sun.setFillColor(sf::Color::Yellow);
            hasScored = false;
        }

        mushroom.rotate(sf::degrees(90.f * dtSeconds));

        window.clear(sf::Color::Black);

        window.draw(sun);
        window.draw(ground);
        // window.draw(mushroom);
        window.draw(scoreText);
        
        window.display();
    }
    return 0;
}