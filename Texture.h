#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <vector>

class Texture
{
public:
	// Initializes variables
	Texture(SDL_Texture *_mTexture, int _mWidth, int _mHeight);

	// Deallocates memory
	~Texture();

	// Loads image at specified path
	bool loadFromFile(std::string path);

	// Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

	// Deallocates texture
	void free();

	// Renders texture at given point
	void render(int x, int y, SDL_Rect *clip = NULL);

	// Gets image dimensions
	int getWidth();
	int getHeight();

private:
	// The actual hardware texture
	SDL_Texture *mTexture;

	// Image dimensions
	int mWidth;
	int mHeight;
};
#endif