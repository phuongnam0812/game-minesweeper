#pragma once

#ifndef VARIABLES_H
#define VARIABLES_H

#include "Texture.h"
#include "Buttons.h"

// initialization
extern SDL_Window *window;
extern SDL_Renderer *renderer;

// loop variable
extern bool isRunning;
extern bool showmenu;
extern bool isChoosing;
extern bool mainLoop;

// win or lose
extern bool isWinning;
extern bool lose;

// image use in game
extern Texture menuTheme;
extern Texture levelTheme;
extern Texture easyTable;
extern Texture mediumTable;
extern Texture hardTable;
extern Texture back;
extern Texture audio_on;
extern Texture audio_off;

// image face
extern Texture winIcon;
extern Texture playingIcon;
extern Texture loseIcon;

// text
extern Texture playBtn;
extern Texture exitBtn;
extern Texture playBtnColor;
extern Texture exitBtnColor;
extern Texture easyLevel;
extern Texture mediumLevel;
extern Texture hardLevel;
extern Texture easyLevelColor;
extern Texture mediumLevelColor;
extern Texture hardLevelColor;
extern Texture wInput;
extern Texture hInput;
extern Texture mInput;
extern TTF_Font *gFont;

// Create board data
extern std::vector<std::vector<int>> stateCell;
extern std::vector<std::vector<int>> cell;

// Cells in board
extern Texture Cells_image;
extern SDL_Rect Cellsprites[12];

// mines
extern int mineCountLeft;
extern int CountCellLeft;

// audio
extern bool mute;
extern Mix_Chunk *click;
extern Mix_MusicloseMusic;
extern Mix_Music winMusic;

// distance
extern int distance_x;
extern int distance_y;
extern int digit_x;
extern int digit_y;
extern int timeDigit_x;

// digits image
extern Texture Digits;
extern SDL_Rect Digitsprites[10];

// board size
extern int board_size_x;
extern int board_size_y;
extern int NumberOfMines;

// boolean
extern bool playAgain;
// extern bool saveScore;
extern bool start;
extern bool easy;
extern bool medium;
extern bool hard;

#endif