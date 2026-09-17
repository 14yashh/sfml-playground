#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Input Test");
    window.setFramerateLimit(60);

    sf::CircleShape sun(50.f);
    sun.setFillColor(sf::Color::Yellow);
    sun.setPosition({700.f, 0.f});

    sf::RectangleShape ground({800.f, 100.f});
    ground.setFillColor(sf::Color::Blue);
    ground.setPosition({0.f, 500.f});

    while(window.isOpen()) {
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

        window.clear(sf::Color::Black);
        window.draw(sun);
        window.draw(ground);
        window.display();
    }
    return 0;
}