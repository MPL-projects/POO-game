 #define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../include/game.hpp"
#include "../include/player.hpp"
#include "../include/health_bar.hpp"
#include "../include/window.hpp"
#include "../include/menu.hpp"
#include "../include/button.hpp"
#include "../include/scene.hpp"
#include "../include/soundEffect.hpp"
#include "../include/soundMusic.hpp"


TEST_CASE("Window Creation", "[window]") {
    Window window;
    window.createWindow("Test Window", 800, 600);

    REQUIRE(window.mainWindow != nullptr); // Check if the main window was created successfully
    REQUIRE(window.renderer != nullptr); // Check if the renderer was created successfully
    REQUIRE(window.WIDTH == 800); // Check the window width
    REQUIRE(window.HEIGHT == 600); // Check the window height

    // Clean up SDL
    TTF_Quit();
    SDL_Quit();
}

TEST_CASE("Button Construction", "[button]") {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("Failed to initialize SDL: " + std::string(SDL_GetError()));
    }
    if (TTF_Init() == -1) {
        throw std::runtime_error("Failed to initialize SDL_ttf: " + std::string(TTF_GetError()));
    }

    // Ensure Game::appWindow is properly initialized
    Game::appWindow = new Window();
    Game::appWindow->createWindow("Test Window", 800, 600);

    // Go to Combat Button
    std::vector<std::string> buttonImagePaths = {"assets/images/backgrounds_elements/menu/buttons/button_normal.png", "assets/images/backgrounds_elements/menu/buttons/button_hover.png", "assets/images/backgrounds_elements/menu/buttons/button_pressed.png"};
	Button *combatButton = new Button(10, 20, 100, 50, buttonImagePaths, "assets/ttf/liberation.ttf", "Combat", GAME);

    // Verify that the button's attributes are correctly initialized
    REQUIRE(combatButton->get_x() == 10);
    REQUIRE(combatButton->get_y() == 20);
    REQUIRE(combatButton->get_w() == 100);
    REQUIRE(combatButton->get_h() == 50);

    // Clean up SDL
    delete combatButton;
    delete Game::appWindow;
    
    TTF_Quit();
    SDL_Quit();
}


TEST_CASE("Player Construction", "[player]") {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("Failed to initialize SDL: " + std::string(SDL_GetError()));
    }
    if (TTF_Init() == -1) {
        throw std::runtime_error("Failed to initialize SDL_ttf: " + std::string(TTF_GetError()));
    }

    // Ensure Game::appWindow is properly initialized
    Game::appWindow = new Window();
    Game::appWindow->createWindow("Test Window", 800, 600);

    // Create a player with specific image and position
    // const char* imagePath = "assets/images/players/player1.png";
    double x = 100;
    double y = 200;

    // Debugging prints
    std::cout << "Creating Player..." << std::endl;
    std::cout << "Image path: " << "assets/images/players/player1.png" << std::endl;
    std::cout << "Player position: (" << x << ", " << y << ")" << std::endl;

    Player *player = new Player("assets/images/players/player1.png",2.5);

    // Verify that the player's attributes are correctly initialized
    REQUIRE(player->life == player->max_life);
    player->take_damage(20);
    REQUIRE(player->life == player->max_life-20);


    // Clean up SDL
    delete player;
    delete Game::appWindow;
    TTF_Quit();
    SDL_Quit();
}

TEST_CASE("HealthBar Construction", "[healthbar]") {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("Failed to initialize SDL: " + std::string(SDL_GetError()));
    }
    if (TTF_Init() == -1) {
        throw std::runtime_error("Failed to initialize SDL_ttf: " + std::string(TTF_GetError()));
    }

    // Ensure Game::appWindow is properly initialized
    Game::appWindow = new Window();
    Game::appWindow->createWindow("Test Window", 800, 600);

    // Create a health bar with specific position and size
    double x = 100;
    double y = 200;
    int width = 100;
    int height = 20;

    // Debugging prints
    std::cout << "Creating HealthBar..." << std::endl;
    std::cout << "HealthBar position: (" << x << ", " << y << ")" << std::endl;
    std::cout << "HealthBar size: (" << width << ", " << height << ")" << std::endl;

    HealthBar healthBar(x, y, width, height);

    // Verify that the health bar's attributes are correctly initialized
    REQUIRE(healthBar.get_x() == x);
    REQUIRE(healthBar.get_y() == y);
    REQUIRE(healthBar.get_w() == width);
    REQUIRE(healthBar.get_h() == height);

    // Clean up SDL
    delete Game::appWindow;
    TTF_Quit();
    SDL_Quit();
}

TEST_CASE("Menu creation and rendering", "[menu]") {
    // Initialize SDL and TTF
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("Failed to initialize SDL: " + std::string(SDL_GetError()));
    }
    if (TTF_Init() == -1) {
        throw std::runtime_error("Failed to initialize SDL_ttf: " + std::string(TTF_GetError()));
    }

    // Create a window and renderer
    Game::appWindow = new Window();
    Game::appWindow->createWindow("Test Window", 800, 600);

    // Create a menu
    Menu *mainMenu;

    mainMenu = new Menu();
    mainMenu->setBackground("assets/images/backgrounds_elements/menu/foggy.png");
	std::vector<std::string> buttonImagePaths = {"assets/images/backgrounds_elements/menu/buttons/button_normal.png", "assets/images/backgrounds_elements/menu/buttons/button_hover.png", "assets/images/backgrounds_elements/menu/buttons/button_pressed.png"};

	// Go to Combat Button
	Button *combatButton = new Button((800 - 220) / 2, (600 - 80) / 2 - 100, 220, 80, buttonImagePaths, "assets/ttf/liberation.ttf", "Combat", GAME);
	mainMenu->addButton(combatButton);

    //Render the menu
    mainMenu->displayMenu();

    // Check that the background texture was created successfully
    REQUIRE(mainMenu->getBackground() != NULL);
    // std::cout << "buttonStatus : " <<  (menu.buttonStatus(button)) << std::endl;
    REQUIRE(mainMenu->buttonStatus(combatButton) == false);
    // Check that the button was rendered correctly

    // Clean up SDL and TTF
    delete combatButton;
    delete Game::appWindow;
    TTF_Quit();
    SDL_Quit();
}