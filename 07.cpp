#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::Clock clock;
    float speed = 600.f;

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Texture rotate");
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
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            sun.setFillColor(sf::Color::Red);
        }
        else {
            sun.setFillColor(sf::Color::Yellow);
        }

        mushroom.rotate(sf::degrees(90.f * dtSeconds));

        window.clear(sf::Color::Black);

        window.draw(sun);
        window.draw(ground);
        window.draw(mushroom);
        
        window.display();
    }
    return 0;
}