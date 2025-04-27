#include <iostream>
#include <unistd.h>

const int width = 10;
const int height = 20;

int field[height][width];

int playerX = width / 2;
int playerY = 0;

void Draw()
{
    system("clear");

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (x == playerX && y == playerY)
                std::cout << "O";
            else if (field[y][x] == 0)
                std::cout << ".";
            else
                std::cout << "#";
        }
        std::cout << std::endl;
    }
}

void Update()
{
    playerY++;

    if (playerY >= height)
    {
        playerY = 0;
        playerX = rand() % width;
    }
}

int main()
{
    while (true)
    {
        Draw();
        Update();
        usleep(100000); // Sleep for 0.1 seconds
    }
    return 0;
}