#pragma once

#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "Timer.h"
#include <SDL.h>
// initialization func
bool init();
bool loadMedia();
bool loadMenuMedia();

// close SDL
void close();

// initialization games
void gameCreateBoard();
void createMenu();
void createLevelMenu();
void renderMenu();
void renderLevelSelected();
void arrangeButtons();

// ingame func
void isWin();
void renderMineCount();
void PlayAgain();
void handleGameEvents();
std::string getTime();
void renderTime();
void setGameLevel(int x, int y, int n, int dx, int dy, int d1x, int d1y, int dtx, int &BOARD_SIZE_X, int &BOARD_SIZE_Y, int &NumberOfMines, int &mineCountLeft, int &CountCellLeft, int &distance_x, int &distance_y, int &digit_x, int &digit_y, int &timeDigit_x);
void renderButton();
void handleEvent();
void openCells(int i, int j);
void renderGame();

#endif