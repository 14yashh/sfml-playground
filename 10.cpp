#include <SFML/Graphics.hpp>
#include <random>

float getRandomFloat(float min, float max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);

    return dis(gen);
}

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Random Velocity");
    window.setFramerateLimit(60);

    sf::CircleShape ball(20.f);
    ball.setOrigin({20.f, 20.f});
    ball.setFillColor(sf::Color::Cyan);
    ball.setPosition({100.f, 100.f});

    sf::CircleShape ball2(20.f);
    ball2.setOrigin({20.f, 20.f});
    ball2.setFillColor(sf::Color::Red);
    ball2.setPosition({700.f, 100.f});

    float randomX = getRandomFloat(-600.f, 600.f);
    float randomY = getRandomFloat(-600.f, 600.f);
    
    float randomX1 = getRandomFloat(-600.f, 600.f);
    float randomY1 = getRandomFloat(-600.f, 600.f);

    sf::Clock clock;
    sf::Vector2f velocity = {randomX, randomY};
    sf::Vector2f velocity1 = {randomX1, randomY1};
    

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
        ball2.move(velocity1 * dtSeconds);

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

        if(ball2.getPosition().x > 760) {
            velocity1.x = -std::abs(velocity1.x);
        }
        if(ball2.getPosition().x < 0) {
            velocity1.x = std::abs(velocity1.x);
        }
        if(ball2.getPosition().y < 0) {
            velocity1.y = std::abs(velocity1.y);
        }
        if(ball2.getPosition().y > 560) {
            velocity1.y = -std::abs(velocity1.y);
        }

        sf::Vector2f pos1 = ball.getPosition();
        sf::Vector2f pos2 = ball2.getPosition();

        float dx = pos1.x - pos2.x;
        float dy = pos1.y - pos2.y;

        float distanceSquared = (dx * dx) + (dy * dy);

        const float minDistSq = 1600.f;

        if(distanceSquared < minDistSq) {
            velocity = -velocity;
            velocity1 = -velocity1;

            ball.setFillColor(sf::Color::Green);
        }

        window.clear(sf::Color::Black);
        window.draw(ball);
        window.draw(ball2);
        window.display();
    }
}