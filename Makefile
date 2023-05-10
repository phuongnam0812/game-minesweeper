CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
# LDFLAGS = -lSDL2 -lmingw32 -lSDL2main
SDL2_INCLUDE_PATHS = -IC:\phuongnam\Game\ASDL\SDL2-2.26.5\x86_64-w64-mingw32\include\SDL2 -IC:\phuongnam\Game\ASDL\SDL2_image-2.6.3\x86_64-w64-mingw32\include\SDL2 -IC:\phuongnam\Game\ASDL\SDL2_mixer-2.6.3\x86_64-w64-mingw32\include\SDL2 -IC:\phuongnam\Game\ASDL\SDL2_ttf-2.20.2\x86_64-w64-mingw32\include\SDL2
SDL2_LIBRARY_PATH = -LC:\phuongnam\Game\ASDL\SDL2-2.26.5\x86_64-w64-mingw32\lib
SDL2_LINK_FLAGS = -lSDL2 -lmingw32 -lSDL2main

SDL2_IMAGE_LIBRARY_PATH = -LC:\phuongnam\Game\ASDL\SDL2_image-2.6.3\x86_64-w64-mingw32\lib
SDL2_IMAGE_LINK_FLAGS = -lSDL2_image

SDL2_MIXER_LIBRARY_PATH = -LC:\phuongnam\Game\ASDL\SDL2_mixer-2.6.3\x86_64-w64-mingw32\lib
SDL2_MIXER_LINK_FLAGS = -lSDL2_mixer

SDL2_TTF_LIBRARY_PATH = -LC:\phuongnam\Game\ASDL\SDL2_ttf-2.20.2\x86_64-w64-mingw32\lib
SDL2_TTF_LINK_FLAGS = -lSDL2_ttf

SDL2_COMPILER_FLAGS = $(SDL2_INCLUDE_PATHS) $(SDL2_LIBRARY_PATH) $(SDL2_LINK_FLAGS) $(SDL2_IMAGE_LIBRARY_PATH) $(SDL2_IMAGE_LINK_FLAGS) $(SDL2_TTF_LIBRARY_PATH) $(SDL2_TTF_LINK_FLAGS) $(SDL2_MIXER_LIBRARY_PATH) $(SDL2_MIXER_LINK_FLAGS)
COMPILER_FLAGS = -w -Wl,-subsystem,windows

SRCS = main.cpp Texture.cpp Buttons.cpp MineSweeper.cpp Timer.cpp Variables.cpp
OBJS = $(SRCS:.cpp=.o)

minesweeper: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(SDL2_COMPILER_FLAGS) $(COMPILER_FLAGS) -o minesweeper

main.o: main.cpp Texture.h Buttons.h Variables.h constant.h MineSweeper.h Timer.h
	$(CXX) $(CXXFLAGS) $(SDL2_COMPILER_FLAGS) -c main.cpp

Texture.o: Texture.cpp Texture.h
	$(CXX) $(CXXFLAGS) $(SDL2_COMPILER_FLAGS) -c Texture.cpp

Buttons.o: Buttons.cpp Buttons.h
	$(CXX) $(CXXFLAGS) $(SDL2_COMPILER_FLAGS) -c Buttons.cpp

# constant.o: constant.cpp constant.h
# 	$(CXX) $(CXXFLAGS) $(OBJS) $(SDL2_COMPILER_FLAGS) $(COMPILER_FLAGS) -c constant.cpp

MineSweeper.o: MineSweeper.cpp MineSweeper.h Variables.h constant.h Buttons.h Texture.h Timer.h
	$(CXX) $(CXXFLAGS) $(SDL2_COMPILER_FLAGS) -c MineSweeper.cpp

Timer.o: Timer.cpp Timer.h
	$(CXX) $(CXXFLAGS) $(SDL2_COMPILER_FLAGS) -c Timer.cpp

Variables.o: Variables.cpp Variables.h Texture.h Buttons.h constant.h
	$(CXX) $(CXXFLAGS) $(SDL2_COMPILER_FLAGS) -c Variables.cpp

clean:
	rm $(OBJS) minesweeper
run: 
	./minesweeper.exe