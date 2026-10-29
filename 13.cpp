#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Mouse Drag");
    window.setFramerateLimit(60);

    sf::CircleShape ball(50.f);
    ball.setOrigin({50.f, 50.f});
    ball.setFillColor(sf::Color::Red);
    ball.setPosition({400.f, 400.f});

    sf::Vector2f velocity = {0.f, 0.f};
    float moveSpeed = 1000.f;

    bool isDragging = false;
    sf::Vector2f lastMousePos;

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
            if (const auto *btnPress = event->getIf<sf::Event::MouseButtonPressed>()) 
            {
                if(btnPress->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

                    if (ball.getGlobalBounds().contains(worldPos)) 
                    {
                        isDragging = true;
                        velocity = {0.f, 0.f};
                    }
                }
            }
            if (const auto* btnRelease = event->getIf<sf::Event::MouseButtonReleased>())
            {
                if(btnRelease->button == sf::Mouse::Button::Left) {
                    isDragging = false;
                }
            }
        }

        sf::Vector2u windowSize = window.getSize();
        float width = static_cast<float>(windowSize.x);
        float height = static_cast<float>(windowSize.y);

        sf::Vector2f acceleration = {0.f, 0.f};

        if(isDragging) {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

            ball.setPosition(mousePos);

            velocity = (mousePos - lastMousePos) / dtSeconds;
            lastMousePos = mousePos;
        }
        else {
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

        }
        window.clear(sf::Color::Black);
        window.draw(ball);
        window.display();
    }
}