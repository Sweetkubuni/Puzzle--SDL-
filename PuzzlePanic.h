#pragma once
#ifndef PUZZLE_PANIC_H
#define PUZZLE_PANIC_H
#include <list>
#include "PanicPuzzleCommon.h"
#define MAX_REVEALED_BLOCKS 3

enum class BLOCK_ABILITY : std::uint16_t {
	burn_player    = 1,
	delay_player   = 2,
	life_recover   = 3
};

class puzzle_field
{
	struct BLOCK {
		BLOCK_ABILITY ability;
		std::uint16_t id;
		bool revealed;
	}field[21];

	std::unique_ptr<SDL_Texture, SDL_Deleter> texture_blocks;
	std::list<BLOCK *> selected_blocks;
	unsigned int numselected;
public:
	     puzzle_field(const std::string & filename, std::unique_ptr<SDL_Renderer, SDL_Deleter> & ren);
		 ~puzzle_field() { }
	void onHandle(SDL_Event & Event);
	void onUpdate();
	void onRender(std::unique_ptr<SDL_Renderer, SDL_Deleter> & ren);

/*
	bool has_won(); not necessary right now.
	bool has_lost();
*/
};
#endif

