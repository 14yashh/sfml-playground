#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode({640, 480}), "SFML Window");

    window.setFramerateLimit(60);

    while(window.isOpen()) {
        while(const std::optional event = window.pollEvent()) {
            if(event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        std::cout << "Frame!" << std::endl;
        window.clear();
        window.display();
    }
    return 0;
}