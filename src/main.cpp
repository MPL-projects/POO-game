#include "../include/game.hpp"

// Main function, entry point of the application
int main(int argc, char **argv)
{
    // Create an instance of the Game class
    Game* game = Game::GetInstance();

    // Run the game loop
    game->run();

    // Return 0 to indicate successful execution
    return 0;
}
