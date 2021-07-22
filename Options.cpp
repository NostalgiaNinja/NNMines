#include "Options.h"

void Options::SelectRenderer(SDL_Renderer& renderer)
{
	optsRenderer = &renderer;
}

void Options::selectEventSystem(SDL_Event& eventSystem)
{
	optsEvent = &eventSystem;
}

void Options::LoadObjects()
{
	SettingsMenuSprite.loadRenderer(*optsRenderer);
	RadioHover.loadRenderer(*optsRenderer);
	RadioSelected.loadRenderer(*optsRenderer);

	SettingsMenuSprite.LoadFromFile("textures/Settings_Menu.png");
	RadioHover.LoadFromFile("textures/Radio_Hover.png");
	RadioSelected.LoadFromFile("textures/Radio_Selected.png");
}

void Options::RunEvents()
{
	if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT) && optsEvent->button.state == SDL_PRESSED)
	{
		if (mouseX > EasyRadioLoc.x && mouseX < EasyRadioLoc.w + EasyRadioLoc.x)
			if (mouseY > EasyRadioLoc.y && mouseY < EasyRadioLoc.y + EasyRadioLoc.h)
			{
				diff = 1;
			}

		if (mouseX > NormalRadioLoc.x && mouseX < NormalRadioLoc.w + NormalRadioLoc.x)
			if (mouseY > NormalRadioLoc.y && mouseY < NormalRadioLoc.y + NormalRadioLoc.h)
			{
				diff = 2;
			}

		if (mouseX > HardRadioLoc.x && mouseX < HardRadioLoc.w + HardRadioLoc.x)
			if (mouseY > HardRadioLoc.y && mouseY < HardRadioLoc.y + HardRadioLoc.h)
			{
				diff = 3;
			}

		if (mouseX > SettingsMenuLoc.x + 2 && mouseX < SettingsMenuLoc.w + SettingsMenuLoc.x + 2)
			if (mouseY > SettingsMenuLoc.y + 51 && mouseY < SettingsMenuLoc.h + SettingsMenuLoc.y + 51)
		{
				done = true;
		}
		//56,51
		if (mouseX > SettingsMenuLoc.x + 56 && mouseX < SettingsMenuLoc.w + SettingsMenuLoc.x + 56)
			if (mouseY > SettingsMenuLoc.y + 51 && mouseY < SettingsMenuLoc.h + SettingsMenuLoc.y + 51)
			{
				cancelled = true;
			}
	}
}

void Options::RunRenderer()
{
	SettingsMenuSprite.render(SettingsMenuLoc.x, SettingsMenuLoc.y, NULL);
	
	SDL_GetMouseState(&mouseX, &mouseY);

		if (mouseX > EasyRadioLoc.x && mouseX < EasyRadioLoc.w + EasyRadioLoc.x)
			if (mouseY > EasyRadioLoc.y && mouseY < EasyRadioLoc.y + EasyRadioLoc.h)
				RadioHover.render(EasyRadioLoc.x, EasyRadioLoc.y, NULL);

		if (mouseX > NormalRadioLoc.x && mouseX < NormalRadioLoc.w + NormalRadioLoc.x)
			if (mouseY > NormalRadioLoc.y && mouseY < NormalRadioLoc.y + NormalRadioLoc.h)
				RadioHover.render(NormalRadioLoc.x, NormalRadioLoc .y, NULL);

		if (mouseX > HardRadioLoc.x && mouseX < HardRadioLoc.w + HardRadioLoc.x)
			if (mouseY > HardRadioLoc.y && mouseY < HardRadioLoc.y + HardRadioLoc.h)
				RadioHover.render(HardRadioLoc.x, HardRadioLoc.y, NULL);

	switch (diff)
	{
	case 1:
		RadioSelected.render(SettingsMenuLoc.x + 3, SettingsMenuLoc.y + 5, NULL);
		break;

	case 2:
		RadioSelected.render(SettingsMenuLoc.x + 3, SettingsMenuLoc.y + 20, NULL);
		break;

	case 3:
		RadioSelected.render(SettingsMenuLoc.x + 3, SettingsMenuLoc.y + 35, NULL);
		break;

	default:
		break;
	}

}

Options::Options()
{
	optsRenderer = nullptr;
	optsEvent = nullptr;

	diff = 1;

	SettingsMenuLoc = { 240, 52, 90, 64 };
	EasyRadioLoc = { 244, 58, 12, 12 };
	NormalRadioLoc = { 244, 72, 12, 12 };
	HardRadioLoc = { 244, 88, 12, 12 };

	done = false;
	cancelled = false;
}

Options::~Options()
{
	optsRenderer = nullptr;
	optsEvent = nullptr;
}