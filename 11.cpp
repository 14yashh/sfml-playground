#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Window Resize");
    window.setFramerateLimit(60);

    sf::ConvexShape triangle;

    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(70, 0));
    triangle.setPoint(1, sf::Vector2f(20, 100));
    triangle.setPoint(2, sf::Vector2f(120, 100));

    triangle.setFillColor(sf::Color::Cyan);

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

            if(const auto* resizeEvent = event->getIf<sf::Event::Resized>()) {
                sf::Vector2f newSize = sf::Vector2f(resizeEvent->size);

                if(newSize.x > 0 && newSize.y > 0) {
                    sf::View newView(newSize / 2.f, newSize);
                    window.setView(newView);
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(triangle);
        window.display();
    }
}