#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "02 window");
    window.setFramerateLimit(60);

    sf::CircleShape circle(50.f);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition({100.f, 100.f});

    sf::CircleShape sun(50.f);
    sun.setFillColor(sf::Color::Yellow);
    sun.setPosition({700.f, 0.f});

    sf::RectangleShape rect({120.f, 60.f});
    rect.setFillColor(sf::Color::Red);
    rect.setPosition({400.f, 300.f});

    sf::RectangleShape ground({800.f, 200.f});
    ground.setFillColor(sf::Color::Blue);
    ground.setPosition({0.f, 400.f});

    while(window.isOpen()) {
        while(const std::optional event = window.pollEvent()) {
            if(event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        window.draw(ground);
        window.draw(sun);
        window.display();
    }
}