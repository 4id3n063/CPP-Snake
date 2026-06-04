#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <random>
 
int main()
{
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    sf::RenderWindow window(sf::VideoMode({800, 800}), "Snake");
    int score = 0;
    // Load a sprite to display
    const sf::Texture texture("snake.png");
    sf::Sprite sprite(texture);
    const sf::Texture texture2("apple.png");
    sf::Sprite apple(texture2);
    float scale = 100.f / 16.f; 
    sprite.setScale(sf::Vector2f(scale, scale));
    apple.setScale(sf::Vector2f(scale, scale));
 
    // Create a graphical text to display
    const sf::Font font("arial.ttf");
    sf::Text text(font, "SCORE: 0", 30);
    sf::Text spcoord(font, "", 30);
    float xdir = 0.f;
    float ydir = 0.f;
    const float stepSize = 100.f;
    const sf::Time stepDelay = sf::seconds(0.5f);
    sf::Clock clock;
    sf::Time timeSinceMove = sf::Time::Zero;
    std::uniform_int_distribution<> distrib(0, 700);
    apple.setPosition(sf::Vector2f(std::round(distrib(gen) / 100.0) * 100.0, std::round(distrib(gen) / 100.0) * 100.0));
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            xdir = -1.f;
            ydir = 0.f;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            xdir = 1.f;
            ydir = 0.f;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            ydir = -1.f;
            xdir = 0.f;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            ydir = 1.f;
            xdir = 0.f;
        }

        timeSinceMove += clock.restart();
        if (timeSinceMove >= stepDelay) {
            sprite.move(sf::Vector2f(xdir * stepSize, ydir * stepSize));
            timeSinceMove -= stepDelay;
        }
        if (sprite.getPosition().x < 0) {
            window.close();
        } else if (sprite.getPosition().x > 701) {
            window.close();
        } else if (sprite.getPosition().y < 0) {
            window.close();
        } else if (sprite.getPosition().y > 701) {
            window.close();
        }
        if (sprite.getPosition().x == apple.getPosition().x && sprite.getPosition().y == apple.getPosition().y) {
            apple.setPosition(sf::Vector2f(std::round(distrib(gen) / 100.0) * 100.0, std::round(distrib(gen) / 100.0) * 100.0));
            score++;
            text.setString("SCORE: " + std::to_string(score));
        }
        // Update sprite coordinates display
        auto pos = sprite.getPosition();
        std::ostringstream oss;
        oss << "X: " << pos.x << " Y: " << pos.y;
        spcoord.setString(oss.str());
        spcoord.setPosition(sf::Vector2f(0, 30));
        // Clear screen
        window.clear();
 
        // Draw the sprite
        window.draw(sprite);
        window.draw(apple);
 
        // Draw the string
        window.draw(text);
        window.draw(spcoord);
        // Update the window
        window.display();
    }
}