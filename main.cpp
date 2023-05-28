#include "Texture.h"
#include "Buttons.h"
#include "Variables.h"
#include "MineSweeper.h"
using namespace std;

int WinMain(int argc, char *argv[])
{
	// Start up SDL and create window
	if (!init())
	{
		cout << "Failed to initialize!" << endl;
	}
	else
	{
		if (loadMedia())
		{
			renderMenu();
			while (mainLoop)
			{
				if (isChoosing)
				{
					renderLevelSelected();
				}
				while (isRunning)
				{
					handleEvent();
					arrangeButtons();
					renderGame();
				}
			}
		}
	}
	close();
	return 0;
}