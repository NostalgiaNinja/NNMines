#pragma once
#include <iostream>

enum class APPSTATE
{
	INIT,
	SPLASHES,
	MAINMENU,
	GAME,
	OPTIONS,
	PAUSE,
	GAMEOVER,
	EXIT
};

APPSTATE& operator++(APPSTATE& appstate)
{
	using IntType = typename std::underlying_type<APPSTATE>::type;
	appstate = static_cast<APPSTATE>(static_cast<IntType>(appstate) + 1);
	return appstate;
}

APPSTATE& operator++(APPSTATE& appstate, int)
{
	APPSTATE result = appstate;
	++appstate;
	return result;
}