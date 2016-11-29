#pragma once
#ifndef PANIC_PUZZLE_COMMON_H
#define PANIC_PUZZLE_COMMON_H
#include <cstdlib>
#include <string>
#include <memory>
#include "SDL_events.h"
#include "SDL_rect.h"
#include "SDL_render.h"

struct SDL_Deleter
{
	void operator() (SDL_Window * p) const { SDL_DestroyWindow(p); }
	void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
	void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
};

#endif // !PANIC_PUZZLE_COMMON_H