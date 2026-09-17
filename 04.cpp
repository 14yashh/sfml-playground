#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::Clock clock;
    float speed = 600.f;

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Movement");
    window.setFramerateLimit(60);

    sf::CircleShape sun(50.f);
    sun.setFillColor(sf::Color::Yellow);
    sun.setPosition({700.f, 0.f});

    sf::RectangleShape ground({800.f, 100.f});
    ground.setFillColor(sf::Color::Blue);
    ground.setPosition({0.f, 500.f});

    while(window.isOpen()) {

        sf::Time dt = clock.restart();
        float dtSeconds = dt.asSeconds();
        // std::cout << dtSeconds << std::endl;

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

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            sun.setFillColor(sf::Color::Red);
        }
        else {
            sun.setFillColor(sf::Color::Yellow);
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            ground.setFillColor(sf::Color::White);
        }
        else {
            ground.setFillColor(sf::Color::Blue);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            sun.move({0.f, speed * dtSeconds * (-1)});
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            sun.move({speed * dtSeconds * (-1), 0.f});
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            sun.move({0.f, speed * dtSeconds});
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            sun.move({speed * dtSeconds, 0.f});
        }

        window.clear(sf::Color::Black);
        window.draw(sun);
        window.draw(ground);
        window.display();
    }
    return 0;
}