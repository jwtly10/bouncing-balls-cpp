#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>

struct Ball {
    sf::CircleShape circle;
    sf::Vector2f velocity;
};

struct Loc {
    int x;
    int y;
};

sf::Color generateRandomColor();
void createBall(std::vector<Ball>& balls, int, int);

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Bouncing Ball");

    sf::CircleShape ball(20.f);

    double bounceSpeed = 1.05;
    bool create = false;
    Loc locationSpawn = {0, 0};

    std::vector<Ball> balls;
    std::vector<Ball> pendingBalls;

    createBall(balls, rand() % 1000, rand() % 800);

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

        window.clear();

        create = false;
        locationSpawn.x = 0;
        locationSpawn.y = 0;
        for (Ball& ball : balls) {

            if (ball.circle.getPosition().x < 0 ||
                ball.circle.getPosition().x + 2 * ball.circle.getRadius() >
                    window.getSize().x) {

                ball.velocity.x = -ball.velocity.x * bounceSpeed;

                if (!create) {
                    create = true;
                    locationSpawn.x = ball.circle.getPosition().x;
                    locationSpawn.y = ball.circle.getPosition().y;
                }
            }

            if (ball.circle.getPosition().y < 0 ||
                ball.circle.getPosition().y + 2 * ball.circle.getRadius() >
                    window.getSize().y) {

                ball.velocity.y = -ball.velocity.y * bounceSpeed;

                if (!create) {
                    create = true;
                    locationSpawn.x = ball.circle.getPosition().x;
                    locationSpawn.y = ball.circle.getPosition().y;
                }
            }

            ball.circle.move(ball.velocity);

            window.draw(ball.circle);
        }

        if (create) {
            /* createBall(balls, locationSpawn.x, locationSpawn.y); */
            createBall(balls, rand() % 1000, rand() % 800);
        }

        window.display();

        sleep(sf::milliseconds(5));
    }

    return 0;
}

sf::Color generateRandomColor() {
    sf::Uint8 r = rand() % 255;
    sf::Uint8 g = rand() % 255;
    sf::Uint8 b = rand() % 255;
    return sf::Color(r, g, b);
}

void createBall(std::vector<Ball>& balls, int x, int y) {
    Ball ball;
    ball.circle.setRadius(20.f);
    ball.circle.setFillColor(generateRandomColor());
    /* ball.circle.setPosition(rand() % 1000, rand() % 800); */
    ball.circle.setPosition(x, y);

    // Ensure we never have a ball with zero velocity in both directions
    ball.velocity.x = (rand() % 2 == 0) ? 2.f : -2.f;

    // Randomize the y-component as before
    ball.velocity.y = (rand() % 2 == 0) ? 2.f : -2.f;
    balls.push_back(ball);
}
