#pragma once

#ifndef BUTTONS_H
#define BUTTONS_H

#include <SDL.h>

class Button
{
public:
	// Initializes internal variables
	Button();

	// Sets top left position
	void setPosition(int x, int y);

	// Handles mouse event
	void handleEvent(SDL_Event *e);

	// Shows button sprite
	void render(int i, int j);

	// Shows button sprite when we lose
	void loseRender(int i, int j);

	// set button in game
	void handleEventAgain(SDL_Event *e);
	void handleEventBack(SDL_Event *e);
	void handleEventMute(SDL_Event *e);

private:
	// Top left position
	SDL_Point mPosition;
};
#endif