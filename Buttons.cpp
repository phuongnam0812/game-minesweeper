#include "Variables.h"
#include "Buttons.h"
#include "MineSweeper.h"

const int SCREEN_WIDTH = 889;
const int SCREEN_HEIGHT = 500;
const int CELL_SIZE = 28;

Button::Button()
{
	mPosition.x = 0;
	mPosition.y = 0;
}

void Button::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

void Button::handleEventAgain(SDL_Event *e)
{
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool inside = true;
		// Mouse is left of the button
		if (x < mPosition.x)
		{
			inside = false;
		}
		// Mouse is right of the button
		else if (x > mPosition.x + 42)
		{
			inside = false;
		}
		// Mouse above the button
		else if (y < mPosition.y)
		{
			inside = false;
		}
		// Mouse below the button
		else if (y > mPosition.y + 42)
		{
			inside = false;
		}
		if (inside)
		{
			if (e->button.button == SDL_BUTTON_LEFT)
			{
				PlayAgain();
			}
		}
	}
}

void Button::handleEventBack(SDL_Event *e)
{
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool inside = true;
		// Mouse is left of the button
		if (x < mPosition.x)
		{
			inside = false;
		}
		// Mouse is right of the button
		else if (x > mPosition.x + 50)
		{
			inside = false;
		}
		// Mouse above the button
		else if (y < mPosition.y)
		{
			inside = false;
		}
		// Mouse below the button
		else if (y > mPosition.y + 50)
		{
			inside = false;
		}
		if (inside)
		{
			if (e->button.button == SDL_BUTTON_LEFT)
			{
				SDL_SetWindowSize(window, SCREEN_WIDTH, SCREEN_HEIGHT);
				isRunning = false;
				isChoosing = true;
				isWinning = false;
				lose = false;
				easy = false;
				medium = false;
				hard = false;
			}
		}
	}
}

void Button::handleEventMute(SDL_Event *e)
{
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool inside = true;
		// Mouse is left of the button
		if (x < mPosition.x)
		{
			inside = false;
		}
		// Mouse is right of the button
		else if (x > mPosition.x + 50)
		{
			inside = false;
		}
		// Mouse above the button
		else if (y < mPosition.y)
		{
			inside = false;
		}
		// Mouse below the button
		else if (y > mPosition.y + 50)
		{
			inside = false;
		}
		if (inside)
		{
			if (e->button.button == SDL_BUTTON_LEFT)
			{
				if (mute == true)
					mute = false;
				else
					mute = true;
			}
		}
	}
}

void Button::handleEvent(SDL_Event *e)
{
	// neu xu kien xay ra
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		// lay vi tri cua chuot
		int x, y;
		SDL_GetMouseState(&x, &y);

		int i = (x - distance_x) / CELL_SIZE;
		int j = (y - distance_y) / CELL_SIZE;

		// kiem tra chuot co dang o vi tri cua btn khong
		bool inside = true;

		// chuot ben trai
		if (x < mPosition.x)
		{
			inside = false;
		}
		// chuot ben phai
		else if (x > mPosition.x + CELL_SIZE)
		{
			inside = false;
		}
		// chuot ben tren
		else if (y < mPosition.y)
		{
			inside = false;
		}
		// chuot ben duoi
		else if (y > mPosition.y + CELL_SIZE)
		{
			inside = false;
		}

		// chuot o trong btn
		if (inside)
		{
			if (e->type == SDL_MOUSEBUTTONDOWN)
			{

				// khi nhap chuot
				switch (e->button.button)
				{
				case SDL_BUTTON_LEFT:
				{
					openCells(i, j);
					if (CountCellLeft == TotalOfMines)
					{
						Mix_PlayMusic(winMusic, 1);
					}
					if (stateCell[i][j] == 9)
					{
						lose = true;
						Mix_PlayMusic(loseMusic, 1);
					}
					else
					{
						Mix_PlayChannel(-1, click, 0);
					}
					break;
				}
				case SDL_BUTTON_RIGHT:
				{
					Mix_PlayChannel(-1, click, 0);
					if (stateCell[i][j] >= 10)
					{
						if (stateCell[i][j] == 11)
						{
							stateCell[i][j] = 10;
							mineCountLeft++;
						}
						else
						{
							stateCell[i][j] = 11;
							mineCountLeft--;
						}
					}
					else
						break;
					break;
				}
				}
			}
		}
	}
}

void Button::render(int i, int j)
{
	// Show current button sprite
	Cells_image.render(mPosition.x, mPosition.y, &Cellsprites[stateCell[i][j]]);
}
void Button::loseRender(int i, int j)
{
	// Show all button sprite
	Cells_image.render(mPosition.x, mPosition.y, &Cellsprites[cell[i][j]]);
}