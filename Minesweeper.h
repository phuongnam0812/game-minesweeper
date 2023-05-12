#pragma once

#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "Timer.h"
#include <SDL.h>
// initialization func
bool init();
bool loadmedia();
bool loadMenuMedia();

// close SDL
void close();

// initialization games
void GameCreateBoard();
void createMenu();
void createModeMenu();
void showMenu();
void showModeChoice();
void ArrangeButtons();

// ingame func
void IsWin();
void MineManager();
void PlayAgain();
void HandleGameEvents();
std::string getTime();
std::string getFileScoreName();
void getScore();
void TimeManager();
void setGameMode(int x, int y, int n, int dx, int dy, int d1x, int d1y, int dtx, int &BOARD_SIZE_X, int &BOARD_SIZE_Y, int &NumberOfMines, int &mineCountLeft, int &CountTileLeft, int &distance_x, int &distance_y, int &digit_x, int &digit_y, int &timeDigit_x);
void renderButton();
void handleEvent();
void revealCells(int i, int j);
void renderGame();

#endif