#pragma once
#include <vector>
#include "LoadTex.h"
#include "LoadTimer.h"

class Cell
{
public:
	Cell();
	~Cell();
	bool CheckMine();
	void SetMine();
	void IncrementMineCount();
	int ReadMineCount();
	bool checkOpened();
	void setOpened();
	void toggleFlagged();
	bool checkFlagged();
	void resetCell();

	SDL_Rect CellLocation;

private:
	bool isMine;
	bool isOpened;
	bool isFlagged;
	int MineCount;
};

class Game
{

public:

	Game();
	~Game();

	//game generation
	void GenerateMines();
	void GenerateNumbers();

	// renderer/event stuff
	void SelectRenderer(SDL_Renderer &renderer);
	void selectEventSystem(SDL_Event &eventSystem);

	//Loading
	void LoadObjects();
	void RunRenderer();
	void RunEvents();
	void Update();

	//game logic
	void OpenCells();
	void FlagCells();
	void ChordCells();
	void AutoFillCheck();
	void ResetGame();
	void FailureCheck();
	void Success();

private:
	//Minesweeper board
	int gridSizeX;
	int gridSizeY;
	int TotalMines;
	int FlaggedCount;
	
	//TODO: Static size of cell, but should change it to a dynamic array.
	Cell gameBoard[30][16];

	//game specific variables
	bool fail;
	bool win;
	bool firstClick;

	//Required stuff to get renderer and game functions going.
	//gameRenderer: Which renderer to render to? getRenderer will ask where to output this data on initialization.
	//gameEvent: What event system to use? gets the event system and uses it within scope
	SDL_Renderer *gameRenderer;
	SDL_Event* gameEvent;

	//Mouse
	int mouseX = 0;
	int mouseY = 0;

	//Objects called in scene
	Sprite MineSkin;
	Sprite MouseHover;

	//UI
	Sprite NewGameButton;
	Sprite NewGameButtonPressed;
	Sprite ButtonHover;
	Sprite UI;
	
	//Font - OFL-Licensed Press Start 2P
	TTF_Font* gameFont;
	Texture fntMinesLeft;
	Texture fntTime;
	
	//Timer - Clock time for Minesweeper
	LoadTimer gameTime;

	//TODO: in Sprite class, make a tex_location so that Cell Location and button location don't have to be manually done.
	SDL_Rect NewGameButtonLoc;
	SDL_Rect UILoc;
};
