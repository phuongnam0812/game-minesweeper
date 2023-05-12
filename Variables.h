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
extern Texture music_on;
extern Texture music_off;

// image face
extern Texture winFace;
extern Texture playingFace;
extern Texture loseFace;

// Tiles in board
extern Texture Tiles_image;
extern SDL_Rect Tilesprites[12];

// text
extern Texture startBtn;
extern Texture exitBtn;
extern Texture menuColor;
extern Texture menu1Color;
extern Texture easyChoice;
extern Texture mediumChoice;
extern Texture hardChoice;
extern Texture easyChoiceColor;
extern Texture mediumChoiceColor;
extern Texture hardChoiceColor;
extern Texture wInput;
extern Texture hInput;
extern Texture mInput;
extern TTF_Font *gFont;

// Create board data
extern std::vector<std::vector<int>> sBoard;
extern std::vector<std::vector<int>> board;

// mines
extern int mineCountLeft;
extern int CountTileLeft;

// audio
extern bool mute;
extern Mix_Chunk *click;
extern Mix_Music *loseMusic;
extern Mix_Music *winMusic;

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
extern bool saveScore;
extern bool start;
extern bool easy;
extern bool medium;
extern bool hard;

#endif