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
extern int CountCellLeft = board_size_x * board_size_y;

// images use in game
extern Texture menuTheme(NULL, 0, 0);
extern Texture levelTheme(NULL, 0, 0);
extern Texture easyTable(NULL, 0, 0);
extern Texture mediumTable(NULL, 0, 0);
extern Texture hardTable(NULL, 0, 0);
extern Texture back(NULL, 0, 0);
extern Texture audio_on(NULL, 0, 0);
extern Texture audio_off(NULL, 0, 0);

// image face
extern Texture winIcon(NULL, 0, 0);
extern Texture playingIcon(NULL, 0, 0);
extern Texture loseIcon(NULL, 0, 0);

// text
extern Texture playBtn(NULL, 0, 0);
extern Texture exitBtn(NULL, 0, 0);
extern Texture playBtnColor(NULL, 0, 0);
extern Texture exitBtnColor(NULL, 0, 0);
extern Texture easyLevel(NULL, 0, 0);
extern Texture mediumLevel(NULL, 0, 0);
extern Texture hardLevel(NULL, 0, 0);
extern Texture easyLevelColor(NULL, 0, 0);
extern Texture mediumLevelColor(NULL, 0, 0);
extern Texture hardLevelColor(NULL, 0, 0);
extern Texture wInput(NULL, 0, 0);
extern Texture hInput(NULL, 0, 0);
extern Texture mInput(NULL, 0, 0);

// create board data
extern std::vector<std::vector<int>> stateCell(3, std::vector<int>(2, 0));
extern std::vector<std::vector<int>> cell(3, std::vector<int>(2, 0));

// Cells in board
extern Texture Cells_image(NULL, 0, 0);
extern SDL_Rect Cellsprites[12] = {};

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
// extern bool saveScore = false;
extern bool start = false;
extern bool easy = false;
extern bool medium = false;
extern bool hard = false;
