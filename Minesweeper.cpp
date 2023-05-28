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
const int CELL_SIZE = 28;

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
	Cells_image.loadFromFile("assests/images/tiles.jpg") ? (
															   for (int i = 0; i < 12; ++i) {
																   Cellsprites[i].x = i * CELL_SIZE;
																   Cellsprites[i].y = 0;
																   Cellsprites[i].w = CELL_SIZE;
																   Cellsprites[i].h = CELL_SIZE;
															   })
														 : (printf("Can't load this image from file!"), loadingState = false);

	Digits.loadFromFile("assests/images/digits.png") ? (
														   for (int i = 0; i < 10; i++) {
															   Digitsprites[i].x = i * 28;
															   Digitsprites[i].y = 0;
															   Digitsprites[i].w = 28;
															   Digitsprites[i].h = 46;
														   })
													 : (printf("Fail"), loadingState = false);

	easyTable.loadFromFile("assests/images/easy.png") ? void() : (printf("Fail"), loadingState = false);
	mediumTable.loadFromFile("assests/images/medium.png") ? void() : (printf("Fail"), loadingState = false);
	hardTable.loadFromFile("assests/images/hard.png") ? void() : (printf("Fail"), loadingState = false);
	winIcon.loadFromFile("assests/images/winicon.png") ? void() : (printf("Fail"), loadingState = false);
	loseIcon.loadFromFile("assests/images/loseicon.png") ? void() : (printf("Fail"), loadingState = false);
	playingIcon.loadFromFile("assests/images/playingicon.png") ? void() : (printf("Fail"), loadingState = false);
	back.loadFromFile("assests/images/backicon.png") ? void() : (loadingState = false);
	audio_on.loadFromFile("assests/images/unmute.png") ? void() : (loadingState = false);
	audio_off.loadFromFile("assests/images/mute.png") ? void() : (loadingState = false);

	// load font chu
	gFont = TTF_OpenFont("assests/font.ttf", 37);
	if (gFont == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		loadingState = false;
	}

	// load text
	SDL_Color textcolor1 = {255, 255, 255, 255};
	playBtn.loadFromRenderedText("PLAY", textcolor1) ? void() : (printf("Fail"), loadingState = false);
	exitBtn.loadFromRenderedText("EXIT", textcolor1) ? void() : (printf("fail!"), loadingState = false);

	SDL_Color color = {255, 0, 0, 255};
	playBtnColor.loadFromRenderedText("PLAY", color) ? void() : (printf("Fail"), loadingState = false);
	exitBtnColor.loadFromRenderedText("EXIT", color) ? void() : (printf("Fail"), loadingState = false);

	// Load hiệu ứng âm thanh
	loseMusic = Mix_LoadMUS("assests/audio/explosion.wav");
	loseMusic == NULL ? (printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError()), loadingState = false) : void();

	winMusic = Mix_LoadMUS("assests/audio/win.wav");
	winMusic == NULL ? (printf("Failed to load [explosion sound effect](poe://www.poe.com/_api/key_phrase?phrase=explosion%20sound%20effect&prompt=Tell%20me%20more%20about%20explosion%20sound%20effect.)! SDL_mixer Error: %s\n", Mix_GetError()), loadingState = false) : void();

	click = Mix_LoadWAV("assests/audio/click.wav");
	click == NULL ? (printf("Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError()), loadingState = false) : void();

	// Load hình nền của menu
	menuTheme.loadFromFile("assests/images/menu.jpg") ? void() : (printf("Fail!"), loadingState = false);

	// Load cấp độ chơi
	levelTheme.loadFromFile("assests/images/level.jpg") ? void() : (printf("Fail"), loadingState = false);

	// Load văn bản lựa chọn cấp độ
	SDL_Color textColor = {255, 255, 255, 255};
	easyLevel.loadFromRenderedText("BEGINNER", textColor) ? void() : (printf("Fail"), loadingState = false);
	mediumLevel.loadFromRenderedText("INTERMEDIATE", textColor) ? void() : (printf("Fail"), loadingState = false);
	hardLevel.loadFromRenderedText("EXPERT", textColor) ? void() : (printf("Fail"), loadingState = false);

	SDL_Color textcolor = {255, 0, 0, 255};
	easyLevelColor.loadFromRenderedText("BEGINNER", textcolor) ? void() : (printf("Fail"), loadingState = false);
	mediumLevelColor.loadFromRenderedText("INTERMEDIATE", textcolor) ? void() : (printf("Fail"), loadingState = false);
	hardLevelColor.loadFromRenderedText("EXPERT", textcolor) ? void() : (printf("Fail"), loadingState = false);
}

void gameCreateBoard()
{
	srand(time(0));
	int mine = 0;
	// khởi tạo bảng
	initBoard();

	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	// đặt mìn ngẫu nhiên
	while (mine < NumberOfMines)
	{
		int i = rand() % board_size_x;
		int j = rand() % board_size_y;
		if (getCell(i, j) != MINE)
		{
			setCell(i, j, MINE);
			mine++;
		}
	}

	// tính số lượng mìn xung quanh mỗi ô
	for (int i = 0; i < board_size_x; i++)
	{
		for (int j = 0; j < board_size_y; j++)
		{
			if (getCell(i, j) != MINE)
			{
				int numMines = countMines(i, j);
				setCell(i, j, numMines);
			}
		}
	}
}
// khởi tạo bảng với các giá trị ban đầu
void initBoard()
{
	for (int i = 0; i < board_size_x; i++)
	{
		for (int j = 0; j < board_size_y; j++)
		{
			stateCell[i][j] = 10;
			cell[i][j] = 0;
		}
	}
}

// lấy giá trị của ô tại vị trí (x, y)
int getCell(int x, int y)
{
	return cell[x][y];
}

// đặt giá trị của ô tại vị trí (x, y)
void setCell(int x, int y, int value)
{
	cell[x][y] = value;
}
int countMines(int x, int y)
{
	int count = 0;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			int xard = x + i;
			int yard = y + j;
			if (xard < 0 || xard > board_size_x - 1 || yard < 0 || yard > board_size_y - 1 || (i == 0 && j == 0))
				continue;
			if (getCell(xard, yard) == MINE)
				count++;
		}
	}
	return count;
}

void arrangeButtons()
{
	iconBtn.setPosition(board_size_x * CELL_SIZE / 2, digit_y);
	backBtn.setPosition(0, 0);
	audioBtn.setPosition(timeDigit_x + 8, 0);
	for (int i = 0; i < board_size_x; ++i)
	{
		for (int j = 0; j < board_size_y; ++j)
		{
			Buttons[i][j].setPosition(i * CELL_SIZE + distance_x, j * CELL_SIZE + distance_y);
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
	easyLevel.render(370, 200);
	mediumLevel.render(335, 250);
	hardLevel.render(385, 300);
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void setGameLevel(int x, int y, int n, int dx, int dy, int d1x, int d1y, int dtx, int &board_size_x, int &board_size_y, int &TotalOfMines, int &CountMineLeft, int &CountCellLeft, int &dist_x, int &dist_y, int &digit_x, int &digit_y, int &timeDigit_x)
{
	// Lưu trữ các giá trị hiện tại của board_size_x, board_size_y, TotalOfMines, CountMineLeft, và CountTileLeft để tránh mất dữ liệu.
	int prev_board_size_x = board_size_x;
	int prev_board_size_y = board_size_y;
	int prev_TotalOfMines = TotalOfMines;
	int prev_CountMineLeft = CountMineLeft;
	int prev_CountCellLeft = CountCellLeft;
	// Cập nhật các giá trị của board_size_x, board_size_y, TotalOfMines, CountMineLeft, và CountTileLeft với các giá trị mới được truyền vào hàm.
	board_size_x = x;
	board_size_y = y;
	TotalOfMines = n;
	CountMineLeft = n;
	CountCellLeft = x * y;
	// Thay đổi kích thước của các vector Buttons, stateCell và cell theo kích thước mới của bảng.
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

	// Sao chép các giá trị của các vector Buttons, stateCell và cell từ kích thước trước đến kích thước mới của bảng.
	for (int i = 0; i < prev_board_size_x; i++)
	{
		for (int j = 0; j < prev_board_size_y; j++)
		{
			if (i < board_size_x && j < board_size_y)
			{
				Buttons[i][j] = Buttons[i][j];
				stateCell[i][j] = stateCell[i][j];
				cell[i][j] = cell[i][j];
			}
		}
	}
}

void openCells(int i, int j)
{
	switch (stateCell[i][j])
	{
	case 11:
		return;
	case 10:
	{
		stateCell[i][j] = cell[i][j];
		if (stateCell[i][j] != 9)
		{
			CountCellLeft--;
		}

		if (stateCell[i][j] == 0)
		{
			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					int xard = i + x;
					int yard = j + y;

					if (xard < 0 || xard > board_size_x - 1 || yard < 0 || yard > board_size_y - 1)
					{
						continue;
					}

					openCells(xard, yard);
				}
			}
		}
		break;
	}
	default:
		break;
	}
}

void isWin()
{
	if (CountCellLeft == NumberOfMines)
		isWinning = true;
}

std::string getTime()
{
	std::stringstream Time{};
	int n = timer.getTicks() / 1000;
	int h, m, s;
	h = n / 3600;
	m = (n - h * 3600) / 60;
	s = (n - h * 3600 - m * 60);
	Time << h << ":" << m << ":" << s;
	return (isWinning == true) ? Time.str() : Time.str();
}

void PlayAgain()
{
	timer.start();
	gameCreateBoard();
	Mix_HaltMusic();
	mineCountLeft = NumberOfMines;
	CountCellLeft = board_size_x * board_size_y;
	isWinning = false;
	lose = false;
	playAgain = false;
}

void handleEvent()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			isRunning = false;
			mainLoop = false;
			break;
		default:
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
			break;
		}
	}
}

void handleGameEvents()
{
	(playAgain == true) ? PlayAgain() : void(); // void() để đảm bảo hàm trả về void
	if (lose == true)
	{
		timer.pause();
		loseIcon.render(board_size_x * CELL_SIZE / 2, digit_y);
		for (int i = 0; i < board_size_x; i++)
		{
			for (int j = 0; j < board_size_y; j++)
			{
				Buttons[i][j].loseRender(i, j);
			}
		}
	}

	(isWinning == true) ? (timer.pause(), winIcon.render(board_size_x * CELL_SIZE / 2, digit_y)) : void();
}

void renderMenu()
{
	bool startInside = false;
	bool exitInside = false;
	bool isMenuShowing = true;
	createMenu();
	int loopCounter = 0;
	while (isMenuShowing)
	{
		handleEvent();
		int x, y;
		SDL_GetMouseState(&x, &y);
		startInside = (x > 600 && x < 600 + playBtn.getWidth() && y > 400 && y < 400 + playBtn.getHeight());
		exitInside = (x > 750 && x < 750 + exitBtn.getWidth() && y > 400 && y < 400 + exitBtn.getHeight());
		if (startInside && isMouseButtonDown(SDL_BUTTON_LEFT))
		{
			start = true;
			isMenuShowing = false;
		}
		if (exitInside && isMouseButtonDown(SDL_BUTTON_LEFT))
		{
			mainLoop = false;
			isMenuShowing = false;
		}
		loopCounter++;
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
				bool insideEasy = (x > 370 && x < 370 + easyLevel.getWidth() && y > 200 && y < 200 + easyLevel.getHeight());
				bool insideMedium = (x > 335 && x < 335 + mediumLevel.getWidth() && y > 250 && y < 250 + mediumLevel.getHeight());
				bool insideHard = (x > 385 && x < 385 + hardLevel.getWidth() && y > 300 && y < 300 + hardLevel.getHeight());
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
							setGameLevel(9, 9, 10, 21, 163, 25, 80, 235, board_size_x, board_size_y, NumberOfMines, mineCountLeft, CountCellLeft, distance_x, distance_y, digit_x, digit_y, timeDigit_x);
							gameCreateBoard();
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
							setGameLevel(16, 16, 40, 21, 163, 25, 80, 430, board_size_x, board_size_y, NumberOfMines, mineCountLeft, CountCellLeft, distance_x, distance_y, digit_x, digit_y, timeDigit_x);
							gameCreateBoard();
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
							setGameLevel(30, 16, 90, 21, 163, 25, 80, 820, board_size_x, board_size_y, NumberOfMines, mineCountLeft, CountCellLeft, distance_x, distance_y, digit_x, digit_y, timeDigit_x);
							gameCreateBoard();
						}
					}
				}
			}
		}
		SDL_RenderPresent(renderer); // vẽ màn hình sau khi đã xử lý sự kiện
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

void renderTime()
{
	int n = timer.getTicks() / 1000;
	int digitIndex = 0;

	if (n < 10)
	{
		Digits.render(timeDigit_x, digit_y, &Digitsprites[n]);
		digitIndex = 28;
	}
	else
	{
		while (n > 0)
		{
			int digit = n % 10;
			Digits.render(timeDigit_x - digitIndex, digit_y, &Digitsprites[digit]);
			n /= 10;
			digitIndex += 28;
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
	playingIcon.render(board_size_x * CELL_SIZE / 2, digit_y);
	renderButton();
	back.render(0, 0);
	renderMineCount();
	isWin();
	renderTime();
	handleGameEvents();
	SDL_RenderPresent(renderer);
}

void close()
{
	// Free loaded images
	Cells_image.free();
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