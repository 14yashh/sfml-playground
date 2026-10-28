#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Acceleration");
    window.setFramerateLimit(60);

    sf::CircleShape ball(50.f);
    ball.setOrigin({50.f, 50.f});
    ball.setFillColor(sf::Color::Red);
    ball.setPosition({400.f, 400.f});

    sf::Vector2f velocity = {0.f, 0.f};
    float moveSpeed = 1000.f;

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time time;
        time = clock.restart();
        float dtSeconds = time.asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (const auto *keyEvent = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyEvent->code == sf::Keyboard::Key::Escape)
                {
                    window.close();
                }
            }

            if (const auto *resizeEvent = event->getIf<sf::Event::Resized>())
            {
                sf::Vector2f newSize = sf::Vector2f(resizeEvent->size);

                if (newSize.x > 0 && newSize.y > 0)
                {
                    sf::View newView(newSize / 2.f, newSize);
                    window.setView(newView);
                }
            }
        }

        sf::Vector2u windowSize = window.getSize();
        float width = static_cast<float>(windowSize.x);
        float height = static_cast<float>(windowSize.y);

        sf::Vector2f acceleration = {0.f, 0.f};

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            acceleration.y = -moveSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            acceleration.y = moveSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            acceleration.x = -moveSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            acceleration.x = moveSpeed;
        }

        velocity += acceleration * dtSeconds;
        ball.move(velocity * dtSeconds);

        sf::Vector2f pos = ball.getPosition();

        if (pos.x < 50.f)
        {
            ball.setPosition({50.f, pos.y});   
            velocity.x = std::abs(velocity.x); 
        }

        if (pos.x > width - 50.f)
        {
            ball.setPosition({width - 50.f, pos.y}); 
            velocity.x = -std::abs(velocity.x);      
        }

        if (pos.y < 50.f)
        {
            ball.setPosition({pos.x, 50.f});   
            velocity.y = std::abs(velocity.y); 
        }

        if (pos.y > height - 50.f)
        {
            ball.setPosition({pos.x, height - 50.f}); 
            velocity.y = -std::abs(velocity.y);       
        }

        window.clear(sf::Color::Black);
        window.draw(ball);
        window.display();
    }
}