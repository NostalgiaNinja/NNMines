#pragma once
#include "LoadTex.h"

class Options
{
public:
	Options();
	~Options();
	//required rendering stuff
	void SelectRenderer(SDL_Renderer& renderer);
	void selectEventSystem(SDL_Event& eventSystem);

	void LoadObjects();
	void RunRenderer();
	void RunEvents();

	bool done;
	bool cancelled;
	int diff;

private:

	//Mouse
	int mouseX = 0;
	int mouseY = 0;

	SDL_Renderer* optsRenderer;
	SDL_Event* optsEvent;

	Sprite SettingsMenuSprite;
	Sprite RadioHover;
	Sprite RadioSelected;

	SDL_Rect SettingsMenuLoc;
	SDL_Rect EasyRadioLoc;
	SDL_Rect NormalRadioLoc;
	SDL_Rect HardRadioLoc;
};