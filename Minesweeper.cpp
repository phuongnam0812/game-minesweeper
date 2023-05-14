#include "Texture.h"
#include "Variables.h"
#include "Buttons.h"
#include "MineSweeper.h"
#include "Timer.h"
#include <sstream>
#include <fstream>
using namespace std;

vector<vector<Button>> Buttons(3, vector<Button>(2));
Button iconBtn;
Button backBtn;
Button audioBtn;
Timer timer;

const std::string WINDOW_TITLE = "Game Minesweeper";

const int SCREEN_WIDTH = 889;
const int SCREEN_HEIGHT = 500;
const int TILE_SIZE = 28;

// initialization functions
bool init()
{
	bool loadingState = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		loadingState = false;
	}
	else
	{
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		// tạo window
		window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			loadingState = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				loadingState = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					loadingState = false;
				}

				// Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					loadingState = false;
				}
				// Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					loadingState = false;
				}
			}
		}
	}

	return loadingState;
}

bool loadMedia()
{
	bool loadingState = true;
	// mo tiles
	if (!Tiles_image.loadFromFile("assests/images/tiles.jpg"))
	{
		printf("Can't load this image from file!");
		loadingState = false;
	}
	else
	{
		for (int i = 0; i < 12; ++i)
		{
			Tilesprites[i].x = i * TILE_SIZE;
			Tilesprites[i].y = 0;
			Tilesprites[i].w = TILE_SIZE;
			Tilesprites[i].h = TILE_SIZE;
		}
	}
	if (!Digits.loadFromFile("assests/images/digits.png"))
	{
		printf("Fail");
		loadingState = false;
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			Digitsprites[i].x = i * 28;
			Digitsprites[i].y = 0;
			Digitsprites[i].w = 28;
			Digitsprites[i].h = 46;
		}
	}
	if (!easyTable.loadFromFile("assests/images/easy.png"))
	{
		printf("Fail");
		loadingState = false;
	}
	if (!mediumTable.loadFromFile("assests/images/medium.png"))
	{
		printf("Fail");
		loadingState = false;
	}
	if (!hardTable.loadFromFile("assests/images/hard.png"))
	{
		printf("Fail");
		loadingState = false;
	}
	if (!winIcon.loadFromFile("assests/images/winicon.png"))
	{
		printf("Fail");
		loadingState = false;
	}
	if (!loseIcon.loadFromFile("assests/images/loseicon.png"))
	{
		printf("Fail");
		loadingState = false;
	}
	if (!playingIcon.loadFromFile("assests/images/playingicon.png"))
	{
		printf("Fail");
		loadingState = false;
	}
	if (!back.loadFromFile("assests/images/backicon.png"))
	{
		loadingState = false;
	}
	if (!audio_on.loadFromFile("assests/images/unmute.png"))
	{
		loadingState = false;
	}
	if (!audio_off.loadFromFile("assests/images/mute.png"))
	{
		loadingState = false;
	}
	//  mo font chu
	gFont = TTF_OpenFont("assests/font.ttf", 37);
	if (gFont == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		loadingState = false;
	}
	// load text
	SDL_Color textcolor1 = {255, 255, 255, 255};
	if (!playBtn.loadFromRenderedText("PLAY", textcolor1))
	{
		printf("Fail");
	}
	if (!exitBtn.loadFromRenderedText("EXIT", textcolor1))
	{
		printf("fail!");
	}
	SDL_Color color = {255, 0, 0, 255};
	if (!playBtnColor.loadFromRenderedText("PLAY", color))
	{
		printf("Fail");
		loadingState = false;
	}
	if (!exitBtnColor.loadFromRenderedText("EXIT", color))
	{
		printf("Fail");
		loadingState = false;
	}
	// Load hieu ung am thanh
	loseMusic = Mix_LoadMUS("assests/audio/explosion.wav");
	if (loseMusic == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		loadingState = false;
	}

	winMusic = Mix_LoadMUS("assests/audio/win.wav");
	if (winMusic == NULL)
	{
		printf("Failed to load explosion sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		loadingState = false;
	}

	click = Mix_LoadWAV("assests/audio/click.wav");
	if (click == NULL)
	{
		printf("Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		loadingState = false;
	}
	// bool loadingState = true;
	// load background of menu
	if (!menuTheme.loadFromFile("assests/images/menu.jpg"))
	{
		printf("Fail!");
		loadingState = false;
	}
	// load level choice
	if (!levelTheme.loadFromFile("assests/images/level.jpg"))
	{
		printf("Fail");
		loadingState = false;
	}
	// load choice text
	SDL_Color textColor = {255, 255, 255, 255};
	if (!easyChoice.loadFromRenderedText("BEGINNER", textColor))
	{
		printf("Fail");
		loadingState = false;
	}
	if (!mediumChoice.loadFromRenderedText("INTERMEDIATE", textColor))
	{
		printf("Fail");
		loadingState = false;
	}
	if (!hardChoice.loadFromRenderedText("EXPERT", textColor))
	{
		printf("Fail");
		loadingState = false;
	}
	SDL_Color textcolor = {255, 0, 0, 255};
	if (!easyChoiceColor.loadFromRenderedText("BEGINNER", textcolor))
	{
		printf("Fail");
		loadingState = false;
	}
	if (!mediumChoiceColor.loadFromRenderedText("INTERMEDIATE", textcolor))
	{
		printf("Fail");
		loadingState = false;
	}
	if (!hardChoiceColor.loadFromRenderedText("EXPERT", textcolor))
	{
		printf("Fail");
		loadingState = false;
	}
	return loadingState;
}

// khoi tao game
void GameCreateBoard()
{
	srand(time(0));
	int mine = 0;
	// khoi tao bang
	for (int i = 0; i < board_size_x; i++)
	{
		for (int j = 0; j < board_size_y; j++)
		{
			stateCell[i][j] = 10;
			cell[i][j] = 0;
		}
	}
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	// dat bom ngau nhien
	while (mine < NumberOfMines)
	{
		int i = rand() % board_size_x;
		int j = rand() % board_size_y;
		if (cell[i][j] == 9)
			continue;
		cell[i][j] = 9;
		mine++;
	}
	// tinh so luong bom xung quanh moi o
	for (int i = 0; i < board_size_x; i++)
	{
		for (int j = 0; j < board_size_y; j++)
		{
			if (cell[i][j] == 9)
				continue;
			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					int xard = i + x;
					int yard = j + y;
					if (xard < 0 || xard > board_size_x - 1 || yard < 0 || yard > board_size_y - 1)
						continue;
					if (cell[xard][yard] == 9)
						cell[i][j]++;
				}
			}
		}
	}
}

void ArrangeButtons()
{
	iconBtn.setPosition(board_size_x * TILE_SIZE / 2, digit_y);
	backBtn.setPosition(0, 0);
	audioBtn.setPosition(timeDigit_x + 8, 0);
	for (int i = 0; i < board_size_x; ++i)
	{
		for (int j = 0; j < board_size_y; ++j)
		{
			Buttons[i][j].setPosition(i * TILE_SIZE + distance_x, j * TILE_SIZE + distance_y);
		}
	}
}

void createMenu()
{
	menuTheme.render(0, 0);
	playBtn.render(600, 400);
	exitBtn.render(750, 400);
	SDL_RenderPresent(renderer);
}

void createLevelMenu()
{
	levelTheme.render(0, 0);
	easyChoice.render(370, 200);
	mediumChoice.render(335, 250);
	hardChoice.render(385, 300);
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void renderMenu()
{
	bool startInside = false;
	bool exitInside = false;
	bool isMenuShowing = true;
	SDL_Event event;
	createMenu();
	int loopCounter = 0;
	while (isMenuShowing)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				mainLoop = false;
				isMenuShowing = false;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEMOTION)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				startInside = (x > 600 && x < 600 + playBtn.getWidth() && y > 400 && y < 400 + playBtn.getHeight());
				exitInside = (x > 750 && x < 750 + exitBtn.getWidth() && y > 400 && y < 400 + exitBtn.getHeight());
				if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						if (startInside)
						{
							start = true;
							isMenuShowing = false;
						}
						if (exitInside)
						{
							mainLoop = false;
							isMenuShowing = false;
						}
					}
				}
			}
			loopCounter++;
		}
		if (loopCounter > 0)
		{
			SDL_RenderPresent(renderer);
			loopCounter = 0;
		}
	}
}

void renderLevelSelected()
{
	int gameMode = 0; // lưu trạng thái lựa chọn cấp độ chơi
	SDL_Event event;
	createLevelMenu();
	while (isChoosing)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				mainLoop = false;
				isChoosing = false;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEMOTION)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				bool insideEasy = (x > 370 && x < 370 + easyChoice.getWidth() && y > 200 && y < 200 + easyChoice.getHeight());
				bool insideMedium = (x > 335 && x < 335 + mediumChoice.getWidth() && y > 250 && y < 250 + mediumChoice.getHeight());
				bool insideHard = (x > 385 && x < 385 + hardChoice.getWidth() && y > 300 && y < 300 + hardChoice.getHeight());
				if (insideEasy)
					gameMode = 1; // cấp độ chơi dễ
				else if (insideMedium)
					gameMode = 2; // cấp độ chơi trung bình
				else if (insideHard)
					gameMode = 3; // cấp độ chơi khó
				if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						if (gameMode == 1)
						{
							isRunning = true;
							isChoosing = false;
							timer.start();
							easy = true;
							medium = false;
							hard = false;
							SDL_SetWindowSize(window, 294, 436);
							setGameLevel(9, 9, 10, 21, 163, 25, 80, 235, board_size_x, board_size_y, NumberOfMines, mineCountLeft, CountTileLeft, distance_x, distance_y, digit_x, digit_y, timeDigit_x);
							GameCreateBoard();
						}
						else if (gameMode == 2)
						{
							isRunning = true;
							isChoosing = false;
							timer.start();
							easy = false;
							medium = true;
							hard = false;
							SDL_SetWindowSize(window, 488, 630);
							setGameLevel(16, 16, 40, 21, 163, 25, 80, 430, board_size_x, board_size_y, NumberOfMines, mineCountLeft, CountTileLeft, distance_x, distance_y, digit_x, digit_y, timeDigit_x);
							GameCreateBoard();
						}
						else if (gameMode == 3)
						{
							isRunning = true;
							isChoosing = false;
							timer.start();
							easy = false;
							medium = false;
							hard = true;
							SDL_SetWindowSize(window, 880, 632);
							setGameLevel(30, 16, 90, 21, 163, 25, 80, 820, board_size_x, board_size_y, NumberOfMines, mineCountLeft, CountTileLeft, distance_x, distance_y, digit_x, digit_y, timeDigit_x);
							GameCreateBoard();
						}
					}
				}
			}
		}
		SDL_RenderPresent(renderer); // vẽ màn hình sau khi đã xử lý sự kiện
	}
}
// mở ô
void revealCells(int i, int j)
{
	if (stateCell[i][j] == 10 || stateCell[i][j] == 11)
	{
		if (stateCell[i][j] == 11)
		{
			return;
		}
		stateCell[i][j] = cell[i][j];
		if (stateCell[i][j] != 9)
			CountTileLeft--;
		if (stateCell[i][j] == 0)
		{
			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					int xard = i + x;
					int yard = j + y;
					if (xard < 0 || xard > board_size_x - 1 || yard < 0 || yard > board_size_y - 1)
						continue;
					revealCells(xard, yard);
				}
			}
		}
	}
}
void renderMineCount()
{
	int n = mineCountLeft;
	if (mineCountLeft < 10)
	{
		Digits.render(digit_x, digit_y, &Digitsprites[0]);
		for (int i = 0; i <= 9; i++)
		{
			if (i == mineCountLeft)
				Digits.render(digit_x + 28, digit_y, &Digitsprites[i]);
		}
	}

	else
	{
		int i = 0;
		while (n > 0)
		{
			int x = n % 10;
			n /= 10;
			Digits.render(digit_x + (1 - i) * 28, digit_y, &Digitsprites[x]);
			i++;
		}
	}
}
// ham trong game
void handleEvent()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			isRunning = false;
			mainLoop = false;
		}
		iconBtn.handleEventAgain(&e);
		backBtn.handleEventBack(&e);
		audioBtn.handleEventMute(&e);
		for (int i = 0; i < board_size_x; i++)
		{
			for (int j = 0; j < board_size_y; j++)
			{
				Buttons[i][j].handleEvent(&e);
			}
		}
	}
}

void HandleGameEvents()
{
	if (playAgain == true)
		PlayAgain();
	// if we lose
	if (lose == true)
	{
		timer.pause();
		loseIcon.render(board_size_x * TILE_SIZE / 2, digit_y);
		for (int i = 0; i < board_size_x; i++)
		{
			for (int j = 0; j < board_size_y; j++)
			{
				Buttons[i][j].loseRender(i, j);
			}
		}
	}
	// if we win
	if (isWinning == true)
	{
		timer.pause();
		winIcon.render(board_size_x * TILE_SIZE / 2, digit_y);
		// if (isRunning == false && isWinning)
		// getScore();
	}
}

void IsWin()
{
	if (CountTileLeft == NumberOfMines)
		isWinning = true;
}

std::string getTime()
{
	stringstream Time{};
	if (isWinning == true)
	{
		int n = timer.getTicks() / 1000;
		int h, m, s;
		h = n / 3600;
		m = (n - h * 3600) / 60;
		s = (n - h * 3600 - m * 60);
		Time.str("");
		Time << h << ":" << m << ":" << s;
		return Time.str();
	}
	else
	{
		int n = timer.getTicks() / 1000;
		int h, m, s;
		h = n / 3600;
		m = (n - h * 3600) / 60;
		s = (n - h * 3600 - m * 60);
		Time.str("");
		Time << h << ":" << m << ":" << s;
		return Time.str();
	}
}

void PlayAgain()
{
	// timer.stop();
	if (isWinning)
		// getScore();
		timer.start();
	GameCreateBoard();
	Mix_HaltMusic();
	mineCountLeft = NumberOfMines;
	CountTileLeft = board_size_x * board_size_y;
	isWinning = false;
	lose = false;
	playAgain = false;
}
void setGameLevel(int x, int y, int n, int dx, int dy, int d1x, int d1y, int dtx, int &board_size_x, int &board_size_y, int &NumberOfMines, int &mineCountLeft, int &CountTileLeft, int &distance_x, int &distance_y, int &digit_x, int &digit_y, int &timeDigit_x)
{
	board_size_x = x;
	board_size_y = y;
	NumberOfMines = n;
	mineCountLeft = n;
	CountTileLeft = x * y;
	distance_x = dx;
	distance_y = dy;
	digit_x = d1x;
	digit_y = d1y;
	timeDigit_x = dtx;

	Buttons.resize(board_size_x);
	for (int i = 0; i < board_size_x; i++)
	{
		Buttons[i].resize(board_size_y);
	}
	stateCell.resize(board_size_x);
	for (int i = 0; i < board_size_x; i++)
	{
		stateCell[i].resize(board_size_y);
	}
	cell.resize(board_size_x);
	for (int i = 0; i < board_size_x; i++)
	{
		cell[i].resize(board_size_y);
	}
}

void TimeManager()
{
	int n = timer.getTicks() / 1000;
	if (n < 10)
	{
		for (int i = 0; i <= 9; i++)
		{
			if (i == n)
				Digits.render(timeDigit_x, digit_y, &Digitsprites[n]);
		}
	}
	else
	{
		int i = 0;
		while (n > 0)
		{
			int x = n % 10;
			n /= 10;
			Digits.render(timeDigit_x - i * 28, digit_y, &Digitsprites[x]);
			i++;
		}
	}
}

void renderButton()
{
	for (int i = 0; i < board_size_x; i++)
	{
		for (int j = 0; j < board_size_y; j++)
		{
			Buttons[i][j].render(i, j);
		}
	}
}

void renderGame()
{
	if (mute == false)
	{
		SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255);
		SDL_RenderClear(renderer);
		audio_on.render(timeDigit_x + 8, 0);
		loseMusic = Mix_LoadMUS("assests/audio/explosion.wav");
		winMusic = Mix_LoadMUS("assests/audio/win.wav");
		click = Mix_LoadWAV("assests/audio/click.wav");
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		audio_off.render(timeDigit_x + 8, 0);
		click = NULL;
		winMusic = NULL;
		loseMusic = NULL;
	}
	if (easy == true || medium == true || hard == true)
	{
		if (easy == true)
		{
			easyTable.render(0, 50);
		}
		if (medium == true)
		{
			mediumTable.render(0, 50);
		}
		if (hard == true)
		{
			hardTable.render(0, 50);
		}
	}
	playingIcon.render(board_size_x * TILE_SIZE / 2, digit_y);
	renderButton();
	back.render(0, 0);
	renderMineCount();
	IsWin();
	TimeManager();
	HandleGameEvents();
	SDL_RenderPresent(renderer);
}

// close SDL
void close()
{
	// Free loaded images
	Tiles_image.free();
	// Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;
	// Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	// Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}