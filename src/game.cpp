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
Window* Game::appWindow;

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
	players.push_back(new Player("assets/images/players/player1.png", 2.5));
	players.push_back(new Player("assets/images/players/player2.png", 2.5));

	

	// players[i]->controller->registerWithEventHandlers(eventHandler);

	RUNNING = true;
}

void Game::run()
{
	SDL_Event event;
	
	initMainMenu();
	initChooseSkinPlayer1();
	initChooseSkinPlayer2();
	initArena();
	Sprite skin("assets/images/players/player1.png", 2.5);

	Sprite skinPlayer1("assets/images/players/player1.png");
	Sprite skinPlayer2("assets/images/players/player2.png");

	std::vector<char *> paths_to_sprites;
	paths_to_sprites.push_back("assets/images/players/player1.png");
	paths_to_sprites.push_back("assets/images/players/player2.png");

	int x_p1 = 0;
	int x_p2 = 1;

	while (RUNNING)
	{
		while (SDL_PollEvent(&event))
		{
			appWindow->handleEvents(event);

			switch (gameStatus)
			{
				// Initial Menu
				case 0:
					mainMenu->handleEvents(event);
					break;

				// Game Menu
				case 1:
					players[1]->handle_events(event);
					players[0]->handle_events(event);
					break;

				// Choose Skin Menu
				case 2:
					mainChooseSkin1->handleEvents(event);
					break;

				case 3:
					mainChooseSkin2->handleEvents(event);
					break;
				
				case 4:
					x_p1 += 1;
					if (x_p1 > 1){x_p1 = 0;}
					skinPlayer1.change_skin(paths_to_sprites[x_p1]);
					players[0]->change_skin(paths_to_sprites[x_p1]);
					gameStatus = 2;
					break;

				case 5:
					x_p1 -= 1;
					if (x_p1 < 0){x_p1 = 1;} 
					skinPlayer1.change_skin(paths_to_sprites[x_p1]);
					players[0]->change_skin(paths_to_sprites[x_p1]);
					gameStatus = 2;
					break;

				case 6:
					x_p2 += 1;
					if (x_p2 > 1){x_p2 = 0;} 
					skinPlayer2.change_skin(paths_to_sprites[x_p2]);
					players[1]->change_skin(paths_to_sprites[x_p2]);
					gameStatus = 3;
					break;

				case 7:
					x_p2 -= 1;
					if (x_p2 < 0){x_p2 = 1;} 
					skinPlayer2.change_skin(paths_to_sprites[x_p2]);
					players[1]->change_skin(paths_to_sprites[x_p2]);
					gameStatus = 3;
					break;

			}
		}

		SDL_RenderClear(appWindow->renderer);

		switch (gameStatus)
		{
			case 0:
				mainMenu->displayMenu();
				break;

			case 1:
				update();
				renderGame();
				break;

			case 2:
				skinPlayer1.update();
				mainChooseSkin1->displayMenu();
				skinPlayer1.draw();
				break;
			
			case 3:
				skinPlayer2.update();
				mainChooseSkin2->displayMenu();
				skinPlayer2.draw();
				break;
		}

		SDL_RenderPresent(appWindow->renderer);
        SDL_Delay(10);

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
    for(auto& player : players)
        player->update();
}

void Game::renderGame()
{
    // SDL_RenderClear(appWindow->renderer);
    // SDL_SetRenderDrawColor(appWindow->renderer, 255, 255, 255, 255);
    // SDL_RenderFillRect(appWindow->renderer, nullptr);
    scene->drawScene();
    drawPlayers();
    // SDL_RenderPresent(appWindow->renderer);
}

void Game::drawPlayers()
{
    std::vector<Player *> p;
    for (auto &player : players)
        p.push_back(player);
    std::sort(p.begin(), p.end(), [](Player* &a, Player* &b){ return a->y < b->y; });
    for (auto &player : p)
        player->draw();
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
	delete mainChooseSkin1;
	delete mainChooseSkin2;
    appWindow->destroyWindow();
}

void Game::initMainMenu()
{
	mainMenu = new Menu();
    mainMenu->setBackground("assets/images/backgrounds_elements/menu/foggy.png");
	std::vector<std::string> buttonImagePaths = {"assets/images/backgrounds_elements/menu/buttons/button_normal.png", "assets/images/backgrounds_elements/menu/buttons/button_hover.png", "assets/images/backgrounds_elements/menu/buttons/button_pressed.png"};

	// Go to Combat Button
	Button *combatButton = new Button((SCREEN_WIDTH - 220) / 2, (SCREEN_HEIGHT - 80) / 2 - 100, 220, 80, buttonImagePaths, "assets/ttf/liberation.ttf", "Combat", 1);
	mainMenu->addButton(combatButton);

	// Go to Choose Skin Menu Button
	Button *chooseSkinButton1 = new Button((SCREEN_WIDTH - 220) / 2, (SCREEN_HEIGHT - 80) / 2, 220, 80, buttonImagePaths, "assets/ttf/liberation.ttf", "Player 1 Skin", 2);
	mainMenu->addButton(chooseSkinButton1);

	// Go to Choose Skin Menu Button
	Button *chooseSkinButton2 = new Button((SCREEN_WIDTH - 220) / 2, (SCREEN_HEIGHT - 80) / 2 + 100, 220, 80, buttonImagePaths, "assets/ttf/liberation.ttf", "Player 2 Skin", 2);
	mainMenu->addButton(chooseSkinButton2);
}

void Game::initChooseSkinPlayer1()
{
	mainChooseSkin1 = new Menu();
    mainChooseSkin1->setBackground("assets/images/backgrounds_elements/menu/foggy.png");

	// Init the arrow buttons to choose character
	std::vector<std::string> buttonImagePaths_right = {"assets/images/backgrounds_elements/menu/buttons/left.png", "assets/images/backgrounds_elements/menu/buttons/left.png", "assets/images/backgrounds_elements/menu/buttons/left.png"};
	std::vector<std::string> buttonImagePaths_left = {"assets/images/backgrounds_elements/menu/buttons/right.png", "assets/images/backgrounds_elements/menu/buttons/right.png", "assets/images/backgrounds_elements/menu/buttons/right.png"};

	Button *playButton_right = new Button((SCREEN_WIDTH - 160) / 2 + 250, (SCREEN_HEIGHT) * 3 / 4, 160, 80, buttonImagePaths_right, "assets/ttf/liberation.ttf", "", 4);
	Button *playButton_left = new Button((SCREEN_WIDTH - 160) / 2 - 250, (SCREEN_HEIGHT) * 3 / 4, 160, 80, buttonImagePaths_left, "assets/ttf/liberation.ttf", "", 5);

	mainChooseSkin1->addButton(playButton_right);
	mainChooseSkin1->addButton(playButton_left);

	// Init the button to go back to the menu
	std::vector<std::string> buttonImagePaths = {"assets/images/backgrounds_elements/menu/buttons/button_normal.png", "assets/images/backgrounds_elements/menu/buttons/button_hover.png", "assets/images/backgrounds_elements/menu/buttons/button_pressed.png"};
	Button *goBackButton = new Button((SCREEN_WIDTH - 220) / 2, (SCREEN_HEIGHT) * 3 / 4, 220, 80, buttonImagePaths, "assets/ttf/liberation.ttf", "Select", 0);
	mainChooseSkin->addButton(goBackButton);

	// Init a sprite
	Sprite skin("assets/images/players/player1.png", 2.5);
	
	mainChooseSkin1->addButton(goBackButton);
}

void Game::initChooseSkinPlayer2()
{
	mainChooseSkin2 = new Menu();
    mainChooseSkin2->setBackground("assets/images/backgrounds_elements/menu/foggy.png");

	// Init the arrow buttons to choose character
	std::vector<std::string> buttonImagePaths_right = {"assets/images/backgrounds_elements/menu/buttons/left.png", "assets/images/backgrounds_elements/menu/buttons/left.png", "assets/images/backgrounds_elements/menu/buttons/left.png"};
	std::vector<std::string> buttonImagePaths_left = {"assets/images/backgrounds_elements/menu/buttons/right.png", "assets/images/backgrounds_elements/menu/buttons/right.png", "assets/images/backgrounds_elements/menu/buttons/right.png"};

	Button *playButton_right = new Button((SCREEN_WIDTH - 160) / 2 + 250, (SCREEN_HEIGHT) * 3 / 4, 160, 80, buttonImagePaths_right, "assets/ttf/liberation.ttf", "", 6);
	Button *playButton_left = new Button((SCREEN_WIDTH - 160) / 2 - 250, (SCREEN_HEIGHT) * 3 / 4, 160, 80, buttonImagePaths_left, "assets/ttf/liberation.ttf", "", 7);

	mainChooseSkin2->addButton(playButton_right);
	mainChooseSkin2->addButton(playButton_left);

	// Init the button to go back to the menu
	std::vector<std::string> buttonImagePaths = {"assets/images/backgrounds_elements/menu/buttons/button_normal.png", "assets/images/backgrounds_elements/menu/buttons/button_hover.png", "assets/images/backgrounds_elements/menu/buttons/button_pressed.png"};
	Button *goBackButton = new Button((SCREEN_WIDTH - 220) / 2, (SCREEN_HEIGHT) * 3 / 4, 220, 80, buttonImagePaths, "assets/ttf/liberation.ttf", "Select", 0);
	mainChooseSkin2->addButton(goBackButton);	
}

void Game::initArena()
{
	scene = new Arena();
}