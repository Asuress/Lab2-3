#pragma once

#include "SDL.h"
#include <vector>

class Texture
{
public:
	Texture(SDL_Renderer* renderer, SDL_Point size);
	~Texture();
	
	SDL_Point GetSize() const { return _size; }

	SDL_Color GetColor(SDL_Point pixel);

	void Render();
	
	void SetPixel(SDL_Point pixel, SDL_Color color);
	void UpdateTexture();

private:
	SDL_Color RgbaFromUint32(Uint32 pixel);

    SDL_Renderer* _renderer;
	SDL_Texture* _sdlTexture;
	SDL_Point _size;
	std::vector<Uint32> _pixels;
};
