#include "../include/game.hpp"
#include "../include/player.hpp"
#include "../include/health_bar.hpp"
#include "../include/window.hpp"
#include "../include/menu.hpp"
#include "../include/button.hpp"
#include "../include/scene.hpp"
#include "../include/soundEffect.hpp"
#include "../include/soundMusic.hpp"
#include "../include/utilities.hpp"
#include <algorithm>
#include <SDL2/SDL.h>
#include <iostream>

// Define screen dimensions
#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768

// Initialize static members of the Game class
Game* Game::game_ = nullptr;
bool Game::RUNNING = true;
GameStatus Game::gameStatus = MAIN_MENU;
Scene* Game::scene = nullptr;
std::vector<Player*> Game::players;
std::vector<HealthBar*> Game::health_bars;
Window* Game::appWindow;
EffectMap SoundEffect::e_SoundMap;
MusicMap SoundMusic::m_SoundMap;

// Game class constructor
Game::Game()
{
    // Initialize the application window
    appWindow = new Window;
    appWindow->createWindow("POO-Game", SCREEN_WIDTH, SCREEN_HEIGHT);

    // Create players and add them to the player vector
    players.push_back(new Player("assets/images/players/player1.png", 2.5));
    players.push_back(new Player("assets/images/players/player2.png", 2.5));

    // Create health bars and add them to the health bar vector
    health_bars.push_back(new HealthBar(75, 10, SCREEN_WIDTH / 4, SCREEN_WIDTH / 16));
    health_bars.push_back(new HealthBar(950, 10, SCREEN_WIDTH / 4, SCREEN_WIDTH / 16));

    // Initialize the scene
    scene = new Scene();
    save_sound = NONE;
    RUNNING = true;
}

// Run the game loop
void Game::run()
{
    SDL_Event event;

    // Initialize sounds and menus
    initSound();
    initMainMenu();
    initChooseSkinPlayer1();
    initChooseSkinPlayer2();
    scene->load_scene("assets/configs/arena.json");
    initEndMenu();

    // Load player skins for selection
    Sprite skinPlayer1("assets/images/players/player1.png", 15);
    skinPlayer1.setPos(SCREEN_WIDTH / 2 - 10 - 48 * 15 / 2, SCREEN_HEIGHT / 2 - 200 - 48 * 15 / 2);
    Sprite skinPlayer2("assets/images/players/player2.png", 15);
    skinPlayer2.setPos(SCREEN_WIDTH / 2 - 10 - 48 * 15 / 2, SCREEN_HEIGHT / 2 - 200 - 48 * 15 / 2);

    // Paths to player sprites
    std::vector<const char*> paths_to_sprites = {
        "assets/images/players/player1.png",
        "assets/images/players/player2.png"
    };

    // Load font for text rendering
    TTF_Font* m_font = TTF_OpenFont("assets/ttf/liberation.ttf", 50);
    if (!m_font)
    {
        throw std::runtime_error("Failed to load font");
    }

    SDL_Color textColor = {255, 255, 255}; // White text color

    // Render text for player win messages
    SDL_Surface* textSurfaceP1 = TTF_RenderText_Solid(m_font, "Player 1 win !", textColor);
    SDL_Texture* P1_textTexture = SDL_CreateTextureFromSurface(appWindow->renderer, textSurfaceP1);

    SDL_Surface* textSurfaceP2 = TTF_RenderText_Solid(m_font, "Player 2 win !", textColor);
    SDL_Texture* P2_textTexture = SDL_CreateTextureFromSurface(appWindow->renderer, textSurfaceP2);

    SDL_Rect winPos = {
        (appWindow->WIDTH - textSurfaceP1->w) / 2 + 10,
        3 * appWindow->HEIGHT / 5,
        textSurfaceP1->w,
        textSurfaceP1->h
    };
    SDL_FreeSurface(textSurfaceP1); textSurfaceP1 = nullptr;
    SDL_FreeSurface(textSurfaceP2); textSurfaceP2 = nullptr;
    TTF_CloseFont(m_font); m_font = nullptr;

    // Initialize variables for player skin selection
    int x_p1 = 0;
    int x_p2 = 1;

    // Main game loop
    while (RUNNING)
    {
        // Event handling
        while (SDL_PollEvent(&event))
        {
            appWindow->handleEvents(event);
            players[0]->handle_events(event);
            players[1]->handle_events(event);

            // Handle events based on game status
            switch (gameStatus)
            {
                case MAIN_MENU:
                    mainMenu->handleEvents(event);
                    break;

                case GAME:
                    break;

                case SKIN_MENU_1:
                    mainChooseSkin1->handleEvents(event);
                    break;

                case SKIN_MENU_2:
                    mainChooseSkin2->handleEvents(event);
                    break;

                case DEATH:
                    endMenu->handleEvents(event);
                    break;

                default:
                    break;
            }
        }

        // Clear the renderer
        SDL_RenderClear(appWindow->renderer);

        // Render based on game status
        switch (gameStatus)
        {
            case MAIN_MENU:
                mainMenu->displayMenu();
                break;

            case GAME:
                update();
                renderGame();
                break;

            case SKIN_MENU_1:
                skinPlayer1.update();
                mainChooseSkin1->displayMenu();
                skinPlayer1.draw();
                break;

            case SKIN_MENU_2:
                skinPlayer2.update();
                mainChooseSkin2->displayMenu();
                skinPlayer2.draw();
                break;

            case SKIN1_RIGHT:
                x_p1 += 1;
                if (x_p1 > 1) { x_p1 = 0; }
                skinPlayer1.change_skin(paths_to_sprites[x_p1]);
                players[0]->change_skin(paths_to_sprites[x_p1]);
                gameStatus = SKIN_MENU_1;
                skinPlayer1.update();
                mainChooseSkin1->displayMenu();
                skinPlayer1.draw();
                break;

            case SKIN1_LEFT:
                x_p1 -= 1;
                if (x_p1 < 0) { x_p1 = 1; }
                skinPlayer1.change_skin(paths_to_sprites[x_p1]);
                players[0]->change_skin(paths_to_sprites[x_p1]);
                gameStatus = SKIN_MENU_1;
                skinPlayer1.update();
                mainChooseSkin1->displayMenu();
                skinPlayer1.draw();
                break;

            case SKIN2_RIGHT:
                x_p2 += 1;
                if (x_p2 > 1) { x_p2 = 0; }
                skinPlayer2.change_skin(paths_to_sprites[x_p2]);
                players[1]->change_skin(paths_to_sprites[x_p2]);
                gameStatus = SKIN_MENU_2;
                skinPlayer2.update();
                mainChooseSkin2->displayMenu();
                skinPlayer2.draw();
                break;

            case SKIN2_LEFT:
                x_p2 -= 1;
                if (x_p2 < 0) { x_p2 = 1; }
                skinPlayer2.change_skin(paths_to_sprites[x_p2]);
                players[1]->change_skin(paths_to_sprites[x_p2]);
                gameStatus = SKIN_MENU_2;
                skinPlayer2.update();
                mainChooseSkin2->displayMenu();
                skinPlayer2.draw();
                break;

            case DEATH:
                update();
                renderGame();
                SDL_RenderCopy(appWindow->renderer, fin_texture, NULL, NULL);
                endMenu->displayMenu(false);
                if (players[0]->get_alive())
                    SDL_RenderCopy(appWindow->renderer, P1_textTexture, NULL, &winPos);
                else
                    SDL_RenderCopy(appWindow->renderer, P2_textTexture, NULL, &winPos);
                break;

            case INIT_PLAYERS:
                players[0]->initSprite();
                players[1]->initSprite();
                players[0]->initPlayer();
                players[1]->initPlayer();
                players[0]->setPos(100, 200);
                players[1]->setPos(1366 - 200.5, 200);
                gameStatus = GAME;
                scene->drawScene();
                break;

            default:
                break;
        }

        // Play background music and sound effects
        playSound();

        // Present the updated renderer
        SDL_RenderPresent(appWindow->renderer);
        SDL_Delay(10);
    }

    // Clean up textures
    SDL_DestroyTexture(P1_textTexture); P1_textTexture = nullptr;
    SDL_DestroyTexture(P2_textTexture); P2_textTexture = nullptr;
    destroyGame();
}

// Update game state
void Game::update()
{
    for (auto& player : players)
        player->update();
}

// Render game elements
void Game::renderGame()
{
    scene->drawScene();
    drawPlayers();
    drawHealthBars();
}

// Draw health bars
void Game::drawHealthBars()
{
    std::vector<HealthBar*> hb;
    for (auto& health_bar : health_bars)
        hb.push_back(health_bar);

    health_bars[0]->actualDamages(players[0]->life, players[0]->max_life);
    health_bars[1]->actualDamages(players[1]->life, players[1]->max_life);

    if (!(players[0]->get_alive() && players[1]->get_alive()))
    {
        gameStatus = DEATH;
    }

    for (auto& health_bar : hb)
        health_bar->render();
}

// Draw players
void Game::drawPlayers()
{
    std::vector<Player*> p;
    for (auto& player : players)
        p.push_back(player);

    std::sort(p.begin(), p.end(), [](Player*& a, Player*& b) { return a->y < b->y; });

    for (auto& player : p)
        player->draw();
}

// Destroy game resources
void Game::destroyGame()
{
    for (auto& player : players)
        delete player;
    for (auto& hb : health_bars)
        delete hb;

    players.clear();
    health_bars.clear();

    delete mainMenu;
    mainMenu = nullptr;
    delete mainChooseSkin1;
    mainChooseSkin1 = nullptr;
    delete mainChooseSkin2;
    mainChooseSkin2 = nullptr;
    delete scene;
    scene = nullptr;
    delete appWindow;
    appWindow = nullptr;
    SDL_DestroyTexture(fin_texture);
    fin_texture = nullptr;
    delete endMenu;
    endMenu = nullptr;
    delete music;
    music = nullptr;
    delete soundEffect;
    soundEffect = nullptr;
}

// Game class destructor
Game::~Game()
{
    destroyGame();
}

// Initialize the main menu
void Game::initMainMenu()
{
    mainMenu = new Menu();
    mainMenu->setBackground("assets/images/backgrounds_elements/menu/foggy.png");

    std::vector<std::string> buttonImagePaths = {
        "assets/images/backgrounds_elements/menu/buttons/button_normal.png",
        "assets/images/backgrounds_elements/menu/buttons/button_hover.png",
        "assets/images/backgrounds_elements/menu/buttons/button_pressed.png"
    };

    // Create and add buttons to the main menu
    Button* combatButton = new Button(
        (SCREEN_WIDTH - 220) / 2, (SCREEN_HEIGHT - 80) / 2 - 100,
        220, 80, buttonImagePaths,
        "assets/ttf/liberation.ttf", "Combat", INIT_PLAYERS
    );
    mainMenu->addButton(combatButton);
    combatButton->setSoundEffect(soundEffect, "button");

    Button* chooseSkinButton1 = new Button(
        (SCREEN_WIDTH - 220) / 2, (SCREEN_HEIGHT - 80) / 2,
        220, 80, buttonImagePaths,
        "assets/ttf/liberation.ttf", "Player 1 Skin", SKIN_MENU_1
    );
    mainMenu->addButton(chooseSkinButton1);
    chooseSkinButton1->setSoundEffect(soundEffect, "button");

    Button* chooseSkinButton2 = new Button(
        (SCREEN_WIDTH - 220) / 2, (SCREEN_HEIGHT - 80) / 2 + 100,
        220, 80, buttonImagePaths,
        "assets/ttf/liberation.ttf", "Player 2 Skin", SKIN_MENU_2
    );
    mainMenu->addButton(chooseSkinButton2);
    chooseSkinButton2->setSoundEffect(soundEffect, "button");
}

// Initialize the menu to choose the skin for player 1
void Game::initChooseSkinPlayer1()
{
    mainChooseSkin1 = new Menu();
    mainChooseSkin1->setBackground("assets/images/backgrounds_elements/menu/foggy.png");

    // Initialize arrow buttons to choose the character
    std::vector<std::string> buttonImagePaths_right = {
        "assets/images/backgrounds_elements/menu/buttons/left.png",
        "assets/images/backgrounds_elements/menu/buttons/left.png",
        "assets/images/backgrounds_elements/menu/buttons/left.png"
    };
    std::vector<std::string> buttonImagePaths_left = {
        "assets/images/backgrounds_elements/menu/buttons/right.png",
        "assets/images/backgrounds_elements/menu/buttons/right.png",
        "assets/images/backgrounds_elements/menu/buttons/right.png"
    };

    Button* playButton_right = new Button(
        (SCREEN_WIDTH - 160) / 2 + 250, (SCREEN_HEIGHT) * 3 / 4,
        160, 80, buttonImagePaths_right,
        "assets/ttf/liberation.ttf", "", SKIN1_RIGHT
    );
    Button* playButton_left = new Button(
        (SCREEN_WIDTH - 160) / 2 - 250, (SCREEN_HEIGHT) * 3 / 4,
        160, 80, buttonImagePaths_left,
        "assets/ttf/liberation.ttf", "", SKIN1_LEFT
    );
    playButton_right->setSoundEffect(soundEffect, "button");
    playButton_left->setSoundEffect(soundEffect, "button");

    mainChooseSkin1->addButton(playButton_right);
    mainChooseSkin1->addButton(playButton_left);

    // Initialize the button to go back to the menu
    std::vector<std::string> buttonImagePaths = {
        "assets/images/backgrounds_elements/menu/buttons/button_normal.png",
        "assets/images/backgrounds_elements/menu/buttons/button_hover.png",
        "assets/images/backgrounds_elements/menu/buttons/button_pressed.png"
    };
    Button* goBackButton = new Button(
        (SCREEN_WIDTH - 220) / 2, (SCREEN_HEIGHT) * 3 / 4,
        220, 80, buttonImagePaths,
        "assets/ttf/liberation.ttf", "Select", MAIN_MENU
    );
    mainChooseSkin1->addButton(goBackButton);
    goBackButton->setSoundEffect(soundEffect, "button");
}

// Initialize the menu to choose the skin for player 2
void Game::initChooseSkinPlayer2()
{
    mainChooseSkin2 = new Menu();
    mainChooseSkin2->setBackground("assets/images/backgrounds_elements/menu/foggy.png");

    // Initialize arrow buttons to choose the character
    std::vector<std::string> buttonImagePaths_right = {
        "assets/images/backgrounds_elements/menu/buttons/left.png",
        "assets/images/backgrounds_elements/menu/buttons/left.png",
        "assets/images/backgrounds_elements/menu/buttons/left.png"
    };
    std::vector<std::string> buttonImagePaths_left = {
        "assets/images/backgrounds_elements/menu/buttons/right.png",
        "assets/images/backgrounds_elements/menu/buttons/right.png",
        "assets/images/backgrounds_elements/menu/buttons/right.png"
    };

    Button* playButton_right = new Button(
        (SCREEN_WIDTH - 160) / 2 + 250, (SCREEN_HEIGHT) * 3 / 4,
        160, 80, buttonImagePaths_right,
        "assets/ttf/liberation.ttf", "", SKIN2_RIGHT
    );
    Button* playButton_left = new Button(
        (SCREEN_WIDTH - 160) / 2 - 250, (SCREEN_HEIGHT) * 3 / 4,
        160, 80, buttonImagePaths_left,
        "assets/ttf/liberation.ttf", "", SKIN2_LEFT
    );
    playButton_right->setSoundEffect(soundEffect, "button");
    playButton_left->setSoundEffect(soundEffect, "button");

    mainChooseSkin2->addButton(playButton_right);
    mainChooseSkin2->addButton(playButton_left);

    // Initialize the button to go back to the menu
    std::vector<std::string> buttonImagePaths = {
        "assets/images/backgrounds_elements/menu/buttons/button_normal.png",
        "assets/images/backgrounds_elements/menu/buttons/button_hover.png",
        "assets/images/backgrounds_elements/menu/buttons/button_pressed.png"
    };
    Button* goBackButton = new Button(
        (SCREEN_WIDTH - 220) / 2, (SCREEN_HEIGHT) * 3 / 4,
        220, 80, buttonImagePaths,
        "assets/ttf/liberation.ttf", "Select", MAIN_MENU
    );
    mainChooseSkin2->addButton(goBackButton);
    goBackButton->setSoundEffect(soundEffect, "button");
}

// Initialize the end menu
void Game::initEndMenu()
{
    endMenu = new Menu();

    std::vector<std::string> buttonImagePaths = {
        "assets/images/backgrounds_elements/menu/buttons/button_normal.png",
        "assets/images/backgrounds_elements/menu/buttons/button_hover.png",
        "assets/images/backgrounds_elements/menu/buttons/button_pressed.png"
    };

    // Create and add buttons to the end menu
    Button* playButton_main_menu = new Button(
        (SCREEN_WIDTH - 220) / 2, (SCREEN_HEIGHT - 80) / 2,
        220, 80, buttonImagePaths,
        "assets/ttf/liberation.ttf", "Menu", MAIN_MENU
    );
    Button* playButton_retry = new Button(
        (SCREEN_WIDTH - 220) / 2, (SCREEN_HEIGHT - 80) / 2 - 100,
        220, 80, buttonImagePaths,
        "assets/ttf/liberation.ttf", "Retry", INIT_PLAYERS
    );

    endMenu->addButton(playButton_main_menu);
    endMenu->addButton(playButton_retry);

    playButton_main_menu->setSoundEffect(soundEffect, "button");
    playButton_retry->setSoundEffect(soundEffect, "button");

    // Create a transparent texture for the end menu
    createTransparentTexture(fin_texture, 180);
}

// Create a transparent texture
void Game::createTransparentTexture(SDL_Texture*& texture_fin, Uint8 alpha)
{
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_PIXELFORMAT_RGBA32);
    SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
    SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 0, 0, 0, alpha));
    texture_fin = SDL_CreateTextureFromSurface(appWindow->renderer, surface);
    SDL_FreeSurface(surface);
    surface = nullptr;
}

// Initialize game sounds
void Game::initSound()
{
    music = new SoundMusic();
    music->loadSound("mainMenu", "assets/musics/themes/menu.ogg");
    music->loadSound("game", "assets/musics/themes/desperate_battle.ogg");
    music->loadSound("endMenu", "assets/musics/themes/endmenu.ogg");

    soundEffect = new SoundEffect();
    soundEffect->loadSound("button", "assets/musics/effects/click-button.wav");
    soundEffect->setVolume(20);
}

// Play background music and sound effects
void Game::playSound()
{
    if (gameStatus != save_sound && gameStatus != SKIN_MENU_1 && gameStatus != SKIN_MENU_2)
    {
        switch (gameStatus)
        {
            case MAIN_MENU:
                music->setVolume(10);
                music->playSound("mainMenu");
                break;

            case GAME:
                music->setVolume(5);
                music->playSound("game");
                break;

            case DEATH:
                music->setVolume(10);
                music->playSound("endMenu");
                break;

            default:
                break;
        }

        save_sound = gameStatus;
    }
}
