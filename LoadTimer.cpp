#include <SDL2/SDL.h>
#include "LoadTimer.h"

LoadTimer::LoadTimer()
{
	startTicks = 0;
	pausedTicks = 0;

	paused = false;
	started = false;
}

void LoadTimer::start()
{
	started = true;
	paused = false;

	startTicks = SDL_GetTicks();
	pausedTicks = 0;
}

void LoadTimer::stop()
{
	started = false;
	paused = false;

	startTicks = 0;
	pausedTicks = 0;
}

void LoadTimer::pause()
{
	if (started && !paused)
	{
		paused = true;

		pausedTicks = SDL_GetTicks() - startTicks;
		startTicks = 0;
	}
}

void LoadTimer::unpause()
{
	if (started && paused)
	{
		paused = false;

		startTicks = SDL_GetTicks() - pausedTicks;

		pausedTicks = 0;
	}
}

Uint32 LoadTimer::getTicks()
{
	Uint32 time = 0;

	if (started)
	{
		if (paused)
		{
			time = pausedTicks;
		}
		else
		{
			time = SDL_GetTicks() - startTicks;
		}
	}
	return time;
}

bool LoadTimer::isStarted()
{
	return started;
}

bool LoadTimer::isPaused()
{
	return paused;
}
