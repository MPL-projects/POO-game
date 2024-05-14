#include "../include/game.hpp"
#include "../include/player.hpp"
#include "../include/window.hpp"
#include "../include/menu.hpp"
#include "../include/button.hpp"
#include "../include/scenesheet.hpp"
#include "../include/scene.hpp"
#include <algorithm>

#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768

bool Game::RUNNING = true;
int Game::gameStatus = 0;
Scene *Game::scene = nullptr;
std::vector<Player *> Game::players;

// void renderCross1(SDL_Surface *screenSurface, int x, int y, int w, Uint32 color) {
//     SDL_Rect rect = {x, y - w / 2, 1, w};
//     SDL_FillRect(screenSurface, &rect, color);

//     rect = {x - w / 2, y, w, 1};
//     SDL_FillRect(screenSurface, &rect, color);
// }

// void renderCross(SDL_Surface *screenSurface , int x, int y, float x1, float x2) {
//     renderCross1(screenSurface, x, y, 20, SDL_MapRGB(screenSurface->format, 0x99, 0x99, 0x99));
//     renderCross1(screenSurface, x + x1 * SCREEN_WIDTH * 0.2f, y + x2 * SCREEN_HEIGHT * 0.2f,
//             10, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xAA));
// }

Game::Game()
{
    appWindow = new Window;
    appWindow->createWindow("POO-Game", SCREEN_WIDTH, SCREEN_HEIGHT);

    screenSurface = appWindow->screenSurface;

    // players = new Player;
    players.push_back(new Player(appWindow->renderer, "assets/images/players/player1.png"));
    players.push_back(new Player(appWindow->renderer, "assets/images/players/player2.png"));

    // players[i]->controller->registerWithEventHandlers(eventHandler);

    RUNNING = true;
}

void Game::run()
{
    SDL_Event event;
    intiMainMenu();
    initArena();
    while (RUNNING)
    {
        while (SDL_PollEvent(&event))
        {
            appWindow->handleEvents(event);
            players[1]->handle_events(event);
            players[0]->handle_events(event);

            mainMenu->handleEvents(event);
        }
        SDL_RenderClear(appWindow->renderer);
        switch (gameStatus)
        {
        case 0:
            mainMenu->displayMenu("assets/images/backgrounds_elements/menu/background1.jpg");
            break;
        case 1:
            update();
            renderGame();
        }
        SDL_RenderPresent(appWindow->renderer);

        // SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0x33, 0x33, 0x33));
        // eventHandler.handleEvents();
        // update();
        // renderGame();
        // SDL_UpdateWindowSurface(window);
        // SDL_UpdateWindowSurface(appWindow->mainWindow);
    }

    SDL_Quit();
    SDL_DestroyRenderer(appWindow->renderer);
}

void Game::update()
{
    // players[0]->controller->getMove();
    // players[1]->controller->getMove();
    players[0]->update();
    players[1]->update();
}

void Game::renderGame()
{
    // SDL_RenderClear(appWindow->renderer);
    SDL_SetRenderDrawColor(appWindow->renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(appWindow->renderer, nullptr);
    scene->drawScene(appWindow->renderer);
    drawPlayers();
    SDL_Delay(10);
    // SDL_RenderPresent(appWindow->renderer);
}

void Game::drawPlayers()
{
    std::vector<Player *> p;
    for (auto &player : players)
        p.push_back(player);
    std::sort(p.begin(), p.end(), [](Player* &a, Player* &b){ return a->y < b->y; });
    for (auto &player : p)
        player->draw(appWindow->renderer);
}

Game::~Game()
{
    for (auto &player : players)
    {
        delete player;
    }
    players.clear();
    delete appWindow;
    delete scene;
    delete screenSurface;
    delete mainMenu;
    appWindow->destroyWindow();
}

void Game::intiMainMenu()
{
    mainMenu = new Menu(appWindow->renderer, appWindow->mainWindow);
    std::vector<std::string> buttonImagePaths = {"assets/images/backgrounds_elements/menu/buttons/button_normal.png", "assets/images/backgrounds_elements/menu/buttons/button_hover.png", "assets/images/backgrounds_elements/menu/buttons/button_pressed.png"};
    Button *playButton = new Button(appWindow->renderer, (SCREEN_WIDTH - 160) / 2, (SCREEN_HEIGHT - 80) / 2, 160, 80, buttonImagePaths, "assets/ttf/liberation.ttf", "Play", 1);
    mainMenu->addButton(playButton);
}

void Game::initArena()
{
    scene = new Arena(appWindow->renderer);
}