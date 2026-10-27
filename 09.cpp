#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Bounce off edges");
    window.setFramerateLimit(60);

    sf::CircleShape ball(20.f);
    ball.setFillColor(sf::Color::Cyan);
    ball.setPosition({100.f, 100.f});

    sf::Clock clock;

    sf::Vector2f velocity = {1000.f, 1000.f};

    while(window.isOpen()) {

        sf::Time time;
        time = clock.restart();
        float dtSeconds = time.asSeconds();

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
        ball.move(velocity * dtSeconds);

        if(ball.getPosition().x > 760) {
            velocity.x = -std::abs(velocity.x);
        }
        if(ball.getPosition().x < 0) {
            velocity.x = std::abs(velocity.x);
        }
        if(ball.getPosition().y < 0) {
            velocity.y = std::abs(velocity.y);
        }
        if(ball.getPosition().y > 560) {
            velocity.y = -std::abs(velocity.y);
        }

        window.clear(sf::Color::Black);
        window.draw(ball);
        window.display();
    }
}