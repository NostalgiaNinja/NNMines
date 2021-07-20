#include "Game.h"
#include <iostream>
#include <string>

void Game::GenerateBoard()
{
	gameBoard.resize(gridSizeX);
	for (int i = 0; i < gridSizeX; i++)
	{
		gameBoard[i].resize(gridSizeY);
	}
}

void Game::GenerateMines()
{
	//check the amount of Total Mines to generate, and place them into the grid using random generation.
	int minesLeft = TotalMines;
	
	srand(time(NULL));

	while (minesLeft > 0)
	{

		int rX = 0;
		int rY = 0;

		rX = (rand() % gridSizeX);
		rY = (rand() % gridSizeY);

		for (int i = 0; i < gridSizeX; i++)
		{
			for (int j = 0; j < gridSizeY; j++)
			{
				if (gameBoard[i][j].CheckMine() != true)
				{
					if (rX == i && rY == j)
					{
						gameBoard[rX][rY].SetMine();
						minesLeft--;
					}
				}
			}
		}
	}

}

void Game::GenerateNumbers()
{
	for (int i = 0; i < gridSizeX; i++)
	{
		for (int j = 0; j < gridSizeY; j++)
		{
			if (gameBoard[i][j].CheckMine() != true)
			{
				//bottom number
				if (j != 0)
				{
					if (gameBoard[i][j - 1].CheckMine())
					{
						gameBoard[i][j].IncrementMineCount();
					}
				}
				//top number
				if (j != gridSizeY-1)
				{
					if (gameBoard[i][j + 1].CheckMine())
					{
						gameBoard[i][j].IncrementMineCount();
					}
				}
				//left number
				if (i != gridSizeX - 1)
				{
					if (gameBoard[i + 1][j].CheckMine())
					{
						gameBoard[i][j].IncrementMineCount();
					}
				}
				//right number
				if (i != 0)
				{
					if (gameBoard[i - 1][j].CheckMine())
					{
						gameBoard[i][j].IncrementMineCount();
					}
				}
				//top left
				if (i != gridSizeX - 1 && j != gridSizeY - 1)
				{
					if (gameBoard[i+1][j+1].CheckMine())
					{
						gameBoard[i][j].IncrementMineCount();
					}
				}
				//bottom right
				if (i != 0 && j != 0)
				{
					if (gameBoard[i - 1][j - 1].CheckMine())
					{
						gameBoard[i][j].IncrementMineCount();
					}
				}
				//bottom left
				if (i != gridSizeX - 1 && j != 0)
				{
					if (gameBoard[i + 1][j - 1].CheckMine())
					{
						gameBoard[i][j].IncrementMineCount();
					}
				}
				//top right
				if (i != 0 && j != gridSizeY - 1)
				{
					if (gameBoard[i-1][j+1].CheckMine())
					{
						gameBoard[i][j].IncrementMineCount();
					}
				}


			}
		}
	}

}

void Game::SelectRenderer(SDL_Renderer &renderer)
{
	gameRenderer = &renderer;
}

void Game::selectEventSystem(SDL_Event &eventSystem)
{
	gameEvent = &eventSystem;
}

void Game::LoadObjects()
{
	//Minesweeper skin - change if needed
	MineSkin.loadRenderer(*gameRenderer);
	MineSkin.LoadFromFile("textures/MineSkin.png");

	MouseHover.loadRenderer(*gameRenderer);
	MouseHover.LoadFromFile("textures/mouse_hover.png");

	NewGameButton.loadRenderer(*gameRenderer);
	NewGameButton.LoadFromFile("textures/NewGame_Button.png");

	ButtonHover.loadRenderer(*gameRenderer);
	ButtonHover.LoadFromFile("textures/Button_Hover.png");

	NewGameButtonPressed.loadRenderer(*gameRenderer);
	NewGameButtonPressed.LoadFromFile("textures/Button_Pressed.png");

	gameFont = TTF_OpenFont("fonts/PressStart2P.ttf", 8);
	fntMinesLeft.loadRenderer(*gameRenderer);
	fntTime.loadRenderer(*gameRenderer);

	UI.loadRenderer(*gameRenderer);
	UI.LoadFromFile("textures/MinesUI.png");
}

void Game::RunRenderer()
{
	
	// X and Y offset for the grid
	int xoffset = 50;
	int yoffset = 85;
	
	//mine visual state
	SDL_Rect CellValues[13];
	for (int i = 0; i < SDL_arraysize(CellValues); i++)
	{
		CellValues[i] = { i * 32, 0, 32, 32 };
	}

	//UI
	UI.render(UILoc.x,UILoc.y,NULL);

	std::string TimeElapsed = std::to_string(int(gameTime.getTicks() / 1000));
	fntTime.loadFont(TimeElapsed, SDL_Color{ 0xff,0xff,0xff,0 }, gameFont);
	fntTime.render(UILoc.x + 35, UILoc.y + 12, NULL);

	std::string MinesLeft = std::to_string(int(TotalMines - FlaggedCount));
	fntMinesLeft.loadFont(MinesLeft, SDL_Color{ 0xff, 0xff, 0xff, 0 }, gameFont);
	fntMinesLeft.render(UILoc.x + 35,UILoc.y + 32,NULL);

	//UI - Buttons
	NewGameButton.render(NewGameButtonLoc.x, NewGameButtonLoc.y, NULL);

	if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT) && gameEvent->button.state == SDL_PRESSED)
	{
		if (mouseX > NewGameButtonLoc.x && mouseX < NewGameButtonLoc.w + NewGameButtonLoc.x)
			if (mouseY > NewGameButtonLoc.y && mouseY < NewGameButton.getHeight() + NewGameButtonLoc.y)
				NewGameButtonPressed.render(NewGameButtonLoc.x, NewGameButtonLoc.y, NULL);
	}

	if (mouseX > NewGameButtonLoc.x && mouseX < NewGameButtonLoc.w + NewGameButtonLoc.x)
	{
		if (mouseY > NewGameButtonLoc.y && mouseY < NewGameButton.getHeight() + NewGameButtonLoc.y)
		{
			ButtonHover.render(NewGameButtonLoc.x, NewGameButtonLoc.y, NULL);
		}
	}

	//Minesweeper grid
	for (int i = 0; i < gridSizeX; i++)
	{
		for (int j = 0; j < gridSizeY; j++)
		{

			//assign a cell location in the render pipeline
			gameBoard[i][j].CellLocation = {(xoffset + (i *32)),(yoffset + (j*32)),32,32};

			if (gameBoard[i][j].checkOpened() != true)
			{
				//initial render should look like this.
				MineSkin.render(gameBoard[i][j].CellLocation.x, gameBoard[i][j].CellLocation.y, &CellValues[0]);
			}
			
			if (fail)
			{
				if (gameBoard[i][j].CheckMine())
				{
					MineSkin.render(gameBoard[i][j].CellLocation.x, gameBoard[i][j].CellLocation.y, &CellValues[11]);
				}
				if (gameBoard[i][j].checkFlagged() && gameBoard[i][j].CheckMine() == false)
				{
					MineSkin.render(gameBoard[i][j].CellLocation.x, gameBoard[i][j].CellLocation.y, &CellValues[10]);
				}
				if (gameBoard[i][j].checkFlagged() && gameBoard[i][j].CheckMine())
				{
					MineSkin.render(gameBoard[i][j].CellLocation.x, gameBoard[i][j].CellLocation.y, &CellValues[12]);
				}
			}

			if (gameBoard[i][j].checkOpened())
			{
				if (gameBoard[i][j].CheckMine())
				{
					MineSkin.render(gameBoard[i][j].CellLocation.x, gameBoard[i][j].CellLocation.y, &CellValues[11]);
				}
				else
				{
					MineSkin.render(gameBoard[i][j].CellLocation.x, gameBoard[i][j].CellLocation.y, &CellValues[1]);
				}

				switch (gameBoard[i][j].ReadMineCount())
				{
				case 1:
					MineSkin.render(gameBoard[i][j].CellLocation.x, gameBoard[i][j].CellLocation.y, &CellValues[2]);
					break;

				case 2:
					MineSkin.render(gameBoard[i][j].CellLocation.x, gameBoard[i][j].CellLocation.y, &CellValues[3]);
					break;

				case 3:
					MineSkin.render(gameBoard[i][j].CellLocation.x, gameBoard[i][j].CellLocation.y, &CellValues[4]);
					break;

				case 4:
					MineSkin.render(gameBoard[i][j].CellLocation.x, gameBoard[i][j].CellLocation.y, &CellValues[5]);
					break;

				case 5:
					MineSkin.render(gameBoard[i][j].CellLocation.x, gameBoard[i][j].CellLocation.y, &CellValues[6]);
					break;

				case 6:
					MineSkin.render(gameBoard[i][j].CellLocation.x, gameBoard[i][j].CellLocation.y, &CellValues[7]);
					break;

				case 7:
					MineSkin.render(gameBoard[i][j].CellLocation.x, gameBoard[i][j].CellLocation.y, &CellValues[8]);
					break;

				case 8:
					MineSkin.render(gameBoard[i][j].CellLocation.x, gameBoard[i][j].CellLocation.y, &CellValues[9]);
					break;

				default:
					break;
				}
			}

			if (!fail)
			{
				if (gameBoard[i][j].checkFlagged())
				{
					MineSkin.render(gameBoard[i][j].CellLocation.x, gameBoard[i][j].CellLocation.y, &CellValues[12]);
				}
			}

			//render grid square (debug)

			if (mouseX > gameBoard[i][j].CellLocation.x && mouseX < gameBoard[i][j].CellLocation.x + gameBoard[i][j].CellLocation.w)
			{
				if (mouseY > gameBoard[i][j].CellLocation.y && mouseY < gameBoard[i][j].CellLocation.y + gameBoard[i][j].CellLocation.h)
				{
					MouseHover.render(gameBoard[i][j].CellLocation.x, gameBoard[i][j].CellLocation.y, NULL);
				}
			}
		}
	}
}

void Game::RunEvents()
{
	//keyboard event - F2 - New Game
	const Uint8* KeyState = SDL_GetKeyboardState(NULL);

	if (KeyState[SDL_SCANCODE_F2])
	{
		ResetGame();
	}


	if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT) && gameEvent->button.state == SDL_PRESSED)
	{
		OpenCells();

		if (mouseX > NewGameButtonLoc.x && mouseX < NewGameButtonLoc.w + NewGameButtonLoc.x)
		{
			if (mouseY > NewGameButtonLoc.y && mouseY < NewGameButtonLoc.h + NewGameButtonLoc.y)
			{
				ResetGame();
			}
		}
	}

	if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_RIGHT) && gameEvent->button.state == SDL_PRESSED)
	{
		//flag if not opened.
		FlagCells();

		//else Chord if opened
		ChordCells();

	}

}

void Game::Update()
{
	if (!firstClick)
	{
		//0 autofill check
		AutoFillCheck();

		//failure check
		FailureCheck();

		//Success check
		Success();
	}
}


void Game::OpenCells()
{
	for (int i = 0; i < gridSizeX; i++)
	{
		for (int j = 0; j < gridSizeY; j++)
		{
			if (!fail)
			{
				//left click
				{
					if (mouseX > gameBoard[i][j].CellLocation.x && mouseX < gameBoard[i][j].CellLocation.x + gameBoard[i][j].CellLocation.w)
					{
						if (mouseY > gameBoard[i][j].CellLocation.y && mouseY < gameBoard[i][j].CellLocation.y + gameBoard[i][j].CellLocation.h)
						{
							//first click check
							while (firstClick)
							{
								GenerateMines();
								GenerateNumbers();

								//check if it's a mine, and if not continue, else reset the board and generate a new set of mines.

								while (gameBoard[i][j].CheckMine())
								{
									ResetGame();
									GenerateMines();
									GenerateNumbers();
								}

								gameTime.start();
								firstClick = false;
							}

							//do checks for cell, and open if applicable.
							if (!gameBoard[i][j].checkFlagged())
							{
								gameBoard[i][j].setOpened();
							}
						}
					}
				}
			}
		}
	}
}

void Game::FlagCells()
{
	for (int i = 0; i < gridSizeX; i++)
	{
		for (int j = 0; j < gridSizeY; j++)
		{
			if (!fail && !win)
			{
				if (mouseX > gameBoard[i][j].CellLocation.x && mouseX < gameBoard[i][j].CellLocation.x + gameBoard[i][j].CellLocation.w)
				{
					if (mouseY > gameBoard[i][j].CellLocation.y && mouseY < gameBoard[i][j].CellLocation.y + gameBoard[i][j].CellLocation.h)
					{
						if (!gameBoard[i][j].checkOpened())
						{
							gameBoard[i][j].toggleFlagged();
							if (gameBoard[i][j].checkFlagged() == false)
							{
								FlaggedCount--;
							}
							else
							{
								FlaggedCount++;
							}
						}
					}
				}
			}
		}
	}
}


void Game::ChordCells()
{
	//Flagged Cells check
	int flaggedCells = 0;

	for (int i = 0; i < gridSizeX; i++)
	{
		for (int j = 0; j < gridSizeY; j++)
		{
			if (!fail)
			{
				if (mouseX > gameBoard[i][j].CellLocation.x && mouseX < gameBoard[i][j].CellLocation.x + gameBoard[i][j].CellLocation.w)
				{
					if (mouseY > gameBoard[i][j].CellLocation.y && mouseY < gameBoard[i][j].CellLocation.y + gameBoard[i][j].CellLocation.h)
					{
						if (gameBoard[i][j].checkOpened())
						{
							if (i != 0 && j != 0)
								if (gameBoard[i - 1][j - 1].checkFlagged())
									flaggedCells++;

							if (i != 0)
								if (gameBoard[i - 1][j].checkFlagged())
									flaggedCells++;

							if (i!= 0 && j != gridSizeY - 1)
								if (gameBoard[i - 1][j + 1].checkFlagged())
									flaggedCells++;

							if (j != 0)
								if (gameBoard[i][j - 1].checkFlagged())
									flaggedCells++;
							
							if (j != gridSizeY - 1)
								if (gameBoard[i][j + 1].checkFlagged())
									flaggedCells++;

							if (i != gridSizeX - 1 && j != 0)
								if (gameBoard[i + 1][j - 1].checkFlagged())
									flaggedCells++;

							if (i != gridSizeX - 1)
								if (gameBoard[i + 1][j].checkFlagged())
									flaggedCells++;

							if (i != gridSizeX - 1 && j != gridSizeY - 1)
								if (gameBoard[i + 1][j + 1].checkFlagged())
									flaggedCells++;

							if (gameBoard[i][j].ReadMineCount() == flaggedCells)
							{
								if (i != 0 && j != 0)
									if (!gameBoard[i - 1][j - 1].checkFlagged() && !gameBoard[i - 1][j - 1].checkOpened())
										gameBoard[i - 1][j - 1].setOpened();
								if (i != 0)
								{
									if (!gameBoard[i - 1][j].checkFlagged() && !gameBoard[i - 1][j].checkOpened())
										gameBoard[i - 1][j].setOpened();

									if (j != gridSizeY - 1)
									{
										if (!gameBoard[i - 1][j + 1].checkFlagged() && !gameBoard[i - 1][j + 1].checkOpened())
											gameBoard[i - 1][j + 1].setOpened();
									}
								}
								if (j != 0)
								{
									if (!gameBoard[i][j - 1].checkFlagged() && !gameBoard[i][j - 1].checkOpened())
										gameBoard[i][j - 1].setOpened();
									if (!gameBoard[i + 1][j - 1].checkFlagged() && !gameBoard[i + 1][j - 1].checkOpened())
										gameBoard[i + 1][j - 1].setOpened();
								}
								if (j != gridSizeY - 1)
								{
									if (!gameBoard[i][j + 1].checkFlagged() && !gameBoard[i][j + 1].checkOpened())
										gameBoard[i][j + 1].setOpened();
									if (!gameBoard[i + 1][j + 1].checkFlagged() && !gameBoard[i + 1][j + 1].checkOpened())
										gameBoard[i + 1][j + 1].setOpened();
								}
								if (!gameBoard[i + 1][j].checkFlagged() && !gameBoard[i + 1][j].checkOpened())
									gameBoard[i + 1][j].setOpened();
							}
						}
					}
				}
			}
		}
	}
}

void Game::FailureCheck()
{
	for (int i = 0; i < gridSizeX; i++)
	{
		for (int j = 0; j < gridSizeY; j++)
		{
			if (gameBoard[i][j].checkOpened() && gameBoard[i][j].CheckMine())
			{
				fail = true;
				gameTime.stop();
			}
		}
	}
}

void Game::Success()
{
	
	int CountedCorrect = 0;
	for (int i = 0; i < gridSizeX; i++)
	{
		for (int j = 0; j < gridSizeY; j++)
		{
			if (gameBoard[i][j].checkFlagged() && gameBoard[i][j].CheckMine())
			{
				CountedCorrect++;
			}
		}
	}
	if (CountedCorrect == TotalMines && win == false)
	{
		gameTime.stop();
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "CONGRATULATIONS!", "YOU WON!", NULL);

		win = true;
	}
}

void Game::AutoFillCheck()
{
	for (int i = 0; i < gridSizeX; i++)
	{
		for (int j = 0; j < gridSizeY; j++)
		{
			if (gameBoard[i][j].checkOpened() && gameBoard[i][j].ReadMineCount() == 0 && !gameBoard[i][j].CheckMine())
			{
				if (j != 0)
					gameBoard[i][j - 1].setOpened();
				if (j != gridSizeY - 1)
					gameBoard[i][j + 1].setOpened();
				if (i != gridSizeX - 1)
					gameBoard[i + 1][j].setOpened();
				if (i != 0)
					gameBoard[i - 1][j].setOpened();
				if (i != gridSizeX - 1 && j != gridSizeY - 1)
					gameBoard[i + 1][j + 1].setOpened();
				if (i != 0 && j != 0)
					gameBoard[i - 1][j - 1].setOpened();
				if (i != gridSizeX - 1 && j != 0)
					gameBoard[i + 1][j - 1].setOpened();
				if (i != 0 && j != gridSizeY - 1)
					gameBoard[i - 1][j + 1].setOpened();
			}
		}
	}
}

void Game::ResetGame()
{
	//reset every cell
	for (int i = 0; i < gridSizeX; i++)
	{
		for (int j = 0; j < gridSizeY; j++)
		{
			gameBoard[i][j].resetCell();
		}
	}

	fail = false;
	win = false;
	firstClick = true;
	FlaggedCount = 0;
}

Game::Game()
{
	//note these are initial Expert grid sizes - Make dynamic later.
	gridSizeX = 30;
	gridSizeY = 16;
	TotalMines = 99;
	FlaggedCount = 0;

	GenerateBoard();

	//game specific variables
	fail = false;
	win = false;
	firstClick = true;

	//which renderer to point to
	gameRenderer = nullptr;
	gameEvent = nullptr;

	//UI
	NewGameButtonLoc = { 185, 20, 128, 32 };
	UILoc = { 50, 10, 128, 64 };

	gameFont = nullptr;
}

Game::~Game()
{
	gridSizeX = 0;
	gridSizeY = 0;
	TotalMines = 0;
	FlaggedCount = 0;

	//UI
	NewGameButtonLoc = { 0,0,0,0};
	gameFont = nullptr;
}

Cell::Cell()
{
	isMine = false;
	isOpened = false;
	isFlagged = false;
	MineCount = 0;
	CellLocation = { 0,0,0,0 };
}

Cell::~Cell()
{
	isMine = false;
	isOpened = false;
	isFlagged = false;
	MineCount = 0;
	CellLocation = { 0,0,0,0 };
}

void Cell::SetMine()
{
	isMine = true;
}

bool Cell::CheckMine()
{
	return isMine;
}

void Cell::IncrementMineCount()
{
	MineCount++;
}

int Cell::ReadMineCount()
{
	return MineCount;
}

bool Cell::checkOpened()
{
	return isOpened;
}

void Cell::setOpened()
{
	isOpened = true;
}

void Cell::toggleFlagged()
{
	if (isFlagged == false)
	{
		isFlagged = true;

	}
	else
	{
		isFlagged = false;

	}
}

bool Cell::checkFlagged()
{
	return isFlagged;
}

void Cell::resetCell()
{
	isMine = false;
	isOpened = false;
	isFlagged = false;
	MineCount = 0;
}