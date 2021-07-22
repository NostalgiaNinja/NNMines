#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "LoadTex.h"
#include "LoadTimer.h"
#include "StateMachines.h"
#include "Options.h"
#include "Game.h"
#include <string>

SDL_Window* mainWindow = nullptr;
SDL_Renderer* mainRenderer = nullptr;

void init(int scrWidth, int scrHeight)
{
	//init SDL Subsystem
	SDL_Init(SDL_INIT_VIDEO);

	//init Window system
	mainWindow = SDL_CreateWindow("NN's Minesweeper Clone", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, scrWidth, scrHeight, SDL_WINDOW_SHOWN | SDL_RENDERER_PRESENTVSYNC);

	//init Renderer
	mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(mainRenderer, 0x00, 0x00, 0x00, 0xff);

	//init SDL_IMG
	int imgFlags = IMG_INIT_PNG;
	IMG_Init(imgFlags);

	//init SDL_TTF
	TTF_Init();
}

void destroyBeforeClose(SDL_Window* window, SDL_Renderer*& renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

int main(int args, char* argv[])
{
	//pre-initialization (game-specific)
	APPSTATE state(APPSTATE::INIT);

	//figure out where resolution should be delt with
	int screenWidth = 1050;
	int screenHeight = 630;
	
	//initialize game and event system
	Game game;
	SDL_Event ev;

	//initialize window
	init(screenWidth, screenHeight);
	
	//Modify state machine to handle application state.
	state = APPSTATE::GAME;

	//select the renderer for the scene
	game.SelectRenderer(*mainRenderer);
	game.selectEventSystem(ev);

	//load objects for renderer
	game.LoadObjects();
	game.SetDifficulty();

	Options options;

	options.SelectRenderer(*mainRenderer);
	options.selectEventSystem(ev);

	options.LoadObjects();

	SDL_Rect frameDebugger = { 20, screenHeight - 50, 32, 32 };

	while (state != APPSTATE::EXIT)
	{

		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT)
			{
				state = APPSTATE::EXIT;
			}
			else
			{
				if (state == APPSTATE::GAME)
					game.RunEvents();

				if (state == APPSTATE::OPTIONS)
					options.RunEvents();
			}
		}
		

		SDL_SetRenderDrawColor(mainRenderer, 0x00, 0x00, 0x00, 0xff);
		SDL_RenderClear(mainRenderer);

		if (game.optionsSelected == true)
		{
			state = APPSTATE::OPTIONS;
		}

		if (state == APPSTATE::GAME)
		{
			game.Update(); 
			game.RunRenderer();
		}

		if (state == APPSTATE::OPTIONS)
		{
			game.RunRenderer();
			options.RunRenderer();
		}

		if (options.done == true)
		{
			state = APPSTATE::GAME;
			game.optionsSelected = false;

			if (options.diff == 1)
			{
				game.gameDifficulty = Difficulty::EASY;
			}
			if (options.diff == 2)
			{
				game.gameDifficulty = Difficulty::NORMAL;
			}
			if (options.diff == 3)
			{
				game.gameDifficulty = Difficulty::HARD;
			}
			game.ResetGame();
			options.done = false;
		}

		if (options.cancelled == true)
		{
			state = APPSTATE::GAME;
			game.optionsSelected = false;
			options.cancelled = false;
		}

		SDL_RenderPresent(mainRenderer);
	}
	
	destroyBeforeClose(mainWindow, mainRenderer);

	return 0;
}

