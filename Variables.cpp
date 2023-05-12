#include "Variables.h"
#include <iostream>
// loop variable
extern bool isRunning = false;
extern bool showmenu = false;
extern bool isChoosing = true;
extern bool mainLoop = true;

// win or lose
extern bool isWinning = false;
extern bool lose = false;

// mines
extern int mineCountLeft = NumberOfMines;
extern int CountTileLeft = board_size_x * board_size_y;

// images use in game
extern Texture menuTheme(NULL, 0, 0);
extern Texture levelTheme(NULL, 0, 0);
extern Texture easyTable(NULL, 0, 0);
extern Texture mediumTable(NULL, 0, 0);
extern Texture hardTable(NULL, 0, 0);
extern Texture back(NULL, 0, 0);
extern Texture music_on(NULL, 0, 0);
extern Texture music_off(NULL, 0, 0);

// image face
extern Texture winFace(NULL, 0, 0);
extern Texture playingFace(NULL, 0, 0);
extern Texture loseFace(NULL, 0, 0);

// text
extern Texture startBtn(NULL, 0, 0);
extern Texture exitBtn(NULL, 0, 0);
extern Texture menuColor(NULL, 0, 0);
extern Texture menu1Color(NULL, 0, 0);
extern Texture easyChoice(NULL, 0, 0);
extern Texture mediumChoice(NULL, 0, 0);
extern Texture hardChoice(NULL, 0, 0);
extern Texture easyChoiceColor(NULL, 0, 0);
extern Texture mediumChoiceColor(NULL, 0, 0);
extern Texture hardChoiceColor(NULL, 0, 0);
extern Texture wInput(NULL, 0, 0);
extern Texture hInput(NULL, 0, 0);
extern Texture mInput(NULL, 0, 0);

// create board data
extern std::vector<std::vector<int>> sBoard(3, std::vector<int>(2, 0));
extern std::vector<std::vector<int>> board(3, std::vector<int>(2, 0));

// Tiles in board
extern Texture Tiles_image(NULL, 0, 0);
extern SDL_Rect Tilesprites[12] = {};

// audio
extern bool mute = false;
extern Mix_Chunk *click = NULL;
extern Mix_Music *loseMusic = NULL;
extern Mix_Music *winMusic = NULL;

// distance
extern int distance_x = 0;
extern int distance_y = 0;
extern int digit_x = 0;
extern int digit_y = 0;
extern int timeDigit_x = 0;

// digits image
extern Texture Digits(NULL, 0, 0);
extern SDL_Rect Digitsprites[10] = {};

// Board size
extern int board_size_x = 0;
extern int board_size_y = 0;
extern int NumberOfMines = 0;

// boolean
extern bool playAgain = false;
extern bool saveScore = false;
extern bool start = false;
extern bool easy = false;
extern bool medium = false;
extern bool hard = false;
