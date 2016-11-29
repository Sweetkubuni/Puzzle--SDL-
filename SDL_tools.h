#pragma once
#ifndef SDL_TOOLS_H
#define SDL_TOOLS_H
#include "PanicPuzzleCommon.h"
#include "SDL_image.h"

SDL_Texture * loadTexture(const std::string & file, std::unique_ptr<SDL_Renderer, SDL_Deleter> & ren)
{
	SDL_Texture * texture = IMG_LoadTexture(ren.get(), file.c_str());
	return texture;
}

void renderTexture(std::unique_ptr<SDL_Texture, SDL_Deleter> & tex, std::unique_ptr<SDL_Renderer, SDL_Deleter> & ren, int x, int y,
	SDL_Rect *clip = nullptr)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	if (clip != nullptr) {
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else {
		SDL_QueryTexture(tex.get(), NULL, NULL, &dst.w, &dst.h);
	}
	SDL_RenderCopy(ren.get(), tex.get(), clip, &dst);
}
#endif