#include "../include/game.hpp"
#include "../include/player.hpp"
#include "../include/health_bar.hpp"
#include "../include/window.hpp"
#include "../include/menu.hpp"
#include "../include/button.hpp"
#include "../include/scenesheet.hpp"
#include "../include/scene.hpp"
#include "../include/soundEffect.hpp"
#include "../include/soundMusic.hpp"
#include <algorithm>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768

bool Game::RUNNING = true;
int Game::gameStatus = 0;
Scene *Game::scene = nullptr;
std::vector<Player *> Game::players;
std::vector<HealthBar *> Game::health_bars;
Window* Game::appWindow;
EffectMap SoundEffect::e_SoundMap;
MusicMap SoundMusic::m_SoundMap;


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
	players.push_back(new Player("assets/images/players/player1.png", 2.5));
	players.push_back(new Player("assets/images/players/player2.png", 2.5));

	health_bars.push_back(new HealthBar(75, 10, SCREEN_WIDTH / 4, SCREEN_WIDTH / 16));
	health_bars.push_back(new HealthBar(950, 10, SCREEN_WIDTH / 4, SCREEN_WIDTH / 16));
	scene = new Scene();
	RUNNING = true;
}

void Game::run()
{
	SDL_Event event;
	
	initMainMenu();
	initChooseSkinPlayer1();
	initChooseSkinPlayer2();
	scene->load_scene("assets/configs/arena.json");

	initEndMenu();
    players[1]->move(1366-300.5,0);

	Sprite skinPlayer1("assets/images/players/player1.png", 15);
	skinPlayer1.move(SCREEN_WIDTH / 2 - 110 - 48 * 15 / 2, SCREEN_HEIGHT / 2 - 300 - 48 * 15 / 2); // longueur ecran / 2 - (offset + valeur arbitraire) - 48 * ratio / 2

	Sprite skinPlayer2("assets/images/players/player2.png", 15);
	skinPlayer2.move(SCREEN_WIDTH / 2 - 110 - 48 * 15 / 2, SCREEN_HEIGHT / 2 - 300 - 48 * 15 / 2);

	std::vector<const char *> paths_to_sprites;
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
					players[0]->handle_events(event);
					players[1]->handle_events(event);
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
				case 8:
					endMenu->handleEvents(event);
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
			case 8:
				update();
				renderGame();
				SDL_RenderCopy(appWindow->renderer,fin_texture,NULL,NULL);
				endMenu->displayMenu(false);
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

    destroyGame();
}

void Game::update()
{
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
	drawHealthBars();
    // SDL_RenderPresent(appWindow->renderer);
}

void Game::drawHealthBars(){
	std::vector<HealthBar *> hb;
    for (auto &health_bar : health_bars){
        hb.push_back(health_bar);
    }

	health_bars[0]->actualDamages(players[0]->life);
	health_bars[1]->actualDamages(players[1]->life);

	if (!(players[0]->get_alive()&&players[1]->get_alive()))
	{
		players[0]->initSprite();
		players[1]->initSprite();
		players[0]->initPlayer();
		players[1]->initPlayer();
		gameStatus = 8;
	}

    for (auto &health_bar : hb)
        health_bar->render();
}

void Game::drawPlayers()
{
    std::vector<Player *> p;
    for (auto &player : players)
        p.push_back(player);
    std::sort(p.begin(), p.end(), [](Player* &a, Player* &b){ return a->y < b->y; });
    for (auto &player : p)
        player->draw();
    // p.clear();
}

void Game::destroyGame(){
    for (auto &player : players)
    {
        delete player;
    }
    for (auto &hb : health_bars){
        delete hb;
    }
    players.clear();
    health_bars.clear();
    delete mainMenu;
    mainMenu = NULL;
    delete mainChooseSkin1;
    mainChooseSkin1 = NULL;
    delete mainChooseSkin2;
    mainChooseSkin2 = NULL;
    delete scene;
    scene = NULL;
    delete appWindow;
    appWindow = NULL;
	SDL_DestroyTexture(fin_texture);
}

Game::~Game()
{
    destroyGame();
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
	Button *chooseSkinButton2 = new Button((SCREEN_WIDTH - 220) / 2, (SCREEN_HEIGHT - 80) / 2 + 100, 220, 80, buttonImagePaths, "assets/ttf/liberation.ttf", "Player 2 Skin", 3);
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



void Game::initEndMenu()
{
	endMenu = new Menu();

	// Init the arrow buttons to choose character
	std::vector<std::string> buttonImagePaths = {"assets/images/backgrounds_elements/menu/buttons/button_normal.png", "assets/images/backgrounds_elements/menu/buttons/button_hover.png", "assets/images/backgrounds_elements/menu/buttons/button_pressed.png"};

	Button *playButton_main_menu = new Button((SCREEN_WIDTH - 220) / 2, (SCREEN_HEIGHT - 80) / 2, 220, 80, buttonImagePaths, "assets/ttf/liberation.ttf", "Menu", 0);
	Button *playButton_retry = new Button((SCREEN_WIDTH - 220) / 2, (SCREEN_HEIGHT - 80) / 2 - 100, 220, 80, buttonImagePaths, "assets/ttf/liberation.ttf", "Retry", 1);

	endMenu->addButton(playButton_main_menu);
	endMenu->addButton(playButton_retry);

	createTransparentTexture(&fin_texture,180);
}


void Game::createTransparentTexture(SDL_Texture **texture_fin, Uint8 alpha) {
    // Create a surface with an alpha channel
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_PIXELFORMAT_RGBA32);
    
    // Set the blend mode of the surface
    SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);

    // Fill the surface with a transparent color
    SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 0, 0, 0, alpha));

    // Create a texture from the surface
    *texture_fin = SDL_CreateTextureFromSurface(appWindow->renderer, surface);

    // Free the surface
    SDL_FreeSurface(surface);
}

void Game::intiSound(){
	SoundMusic *music = new SoundMusic();
}