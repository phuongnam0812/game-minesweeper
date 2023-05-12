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
		if (loadmedia())
		{
			if (loadMenuMedia())
			{
				showMenu();
				while (mainLoop)
				{
					if (isChoosing)
					{
						showModeSelected();
					}
					while (isRunning)
					{
						handleEvent();
						ArrangeButtons();
						renderGame();
					}
				}
			}
		}
	}
	// Free resources and close SDL
	close();
	return 0;
}