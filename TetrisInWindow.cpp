#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

const int width = 10;
const int height = 20;
const int blockSize = 30; // Grootte van een blokje in pixels

int field[height][width] = {0}; // Initialiseer het veld met nullen

int playerX = width / 2;
int playerY = 0;

// Toetsenbord input verwerken
void ProcessInput(sf::RenderWindow &window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && playerX > 0)
        playerX--;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && playerX < width - 1)
        playerX++;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        playerY++;
}

void Update()
{
    playerY++;

    if (playerY >= height || field[playerY][playerX] != 0)
    {
        // Blokje plaatsen op de vorige positie
        if (playerY > 0)
            field[playerY - 1][playerX] = 1;

        // Reset speler positie
        playerY = 0;
        playerX = rand() % width;
    }
}

void DrawField(sf::RenderWindow &window)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            sf::RectangleShape block(sf::Vector2f(blockSize - 1, blockSize - 1));
            block.setPosition(sf::Vector2f(x * blockSize, y * blockSize)); // Fixed

            if (x == playerX && y == playerY)
                block.setFillColor(sf::Color::Red); // Speler
            else if (field[y][x] == 0)
                block.setFillColor(sf::Color::Black); // Leeg veld
            else
                block.setFillColor(sf::Color::Blue); // Gevulde blokjes

            window.draw(block);
        }
    }
}

int main()
{
    srand(static_cast<unsigned>(time(0))); // Initialiseer de willekeurige generator

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(width * blockSize, height * blockSize)), "Tetris App!"); // Fixed
    window.setFramerateLimit(10);                                                                               // Beperkt de snelheid van het spel

    sf::Clock clock;
    float timer = 0, delay = 0.3f;

    while (window.isOpen())
    {
        std::optional<sf::Event> eventOpt;      // Use std::optional
        while ((eventOpt = window.pollEvent())) // pollEvent returns std::optional
        {
            sf::Event event = *eventOpt;         // Dereference the optional
            if (event.type == sf::Event::Closed) // Access event type
                window.close();
        }

        ProcessInput(window);

        if (timer > delay)
        {
            Update();
            timer = 0;
        }

        window.clear();
        DrawField(window);
        window.display();
    }

    return 0;
}