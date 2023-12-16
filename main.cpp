#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>

sf::Color generateRandomColor();

int main() {
  srand(static_cast<unsigned int>(time(nullptr)));
  sf::RenderWindow window(sf::VideoMode(800, 600), "Bouncing Ball");

  sf::CircleShape ball(20.f);
  ball.setFillColor(generateRandomColor());

  sf::Vector2f velocity(2.f, 2.f);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyPressed)
        if (event.key.code == sf::Keyboard::Escape)
          window.close();
    }

    ball.move(velocity);

    if (ball.getPosition().x < 0 ||
        ball.getPosition().x + 2 * ball.getRadius() > window.getSize().x)
      velocity.x = -velocity.x;

    if (ball.getPosition().y < 0 ||
        ball.getPosition().y + 2 * ball.getRadius() > window.getSize().y)
      velocity.y = -velocity.y;

    window.clear();
    window.draw(ball);
    window.display();
    sleep(sf::milliseconds(10));
  }

  return 0;
}

sf::Color generateRandomColor() {
  sf::Uint8 r = rand() % 255;
  sf::Uint8 g = rand() % 255;
  sf::Uint8 b = rand() % 255;
  return sf::Color(r, g, b);
}
