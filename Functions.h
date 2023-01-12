#pragma once
#include "SDL_rect.h"
#include <cmath>

namespace Functions
{
// R-функциональное пересечение
float RAnd(float f1, float f2)
{
	return f1 + f2 - std::sqrt(powf(f1, 2) + powf(f2, 2));
}

// R-функциональное объежигегте
float ROr(float f1, float f2)
{
	return f1 + f2 + std::sqrt(powf(f1, 2) + powf(f2, 2));
}

float Circle(SDL_FPoint position, float radius, SDL_FPoint args)
{
	return powf(radius, 2) - powf(args.x - position.x, 2) - powf(args.y - position.y, 2);
}
float Circle(SDL_Point position, float radius, SDL_Point args)
{
	return powf(radius, 2) - powf(args.x - position.x, 2) - powf(args.y - position.y, 2);
}

float Ellips(SDL_Point position, float radiusA,float radiusB, SDL_Point args)
{
	//return powf(radiusA, 2) - powf(args.x - position.x, 2) - powf(args.y - position.y, 2);
	return 1 - powf((args.x - position.x), 2) / powf(radiusA,2) - powf((args.y - position.y), 2) / powf(radiusB,2);
	
}
}
