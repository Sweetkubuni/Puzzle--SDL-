#include "PuzzlePanic.h"
#include "SDL_tools.h"
#include <cmath>
#include <random>

puzzle_field::puzzle_field(const std::string & filename, std::unique_ptr<SDL_Renderer, SDL_Deleter> & ren) : texture_blocks(loadTexture(filename, ren), SDL_Deleter())
{
	unsigned int i = 0;
	numselected = 0;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 6);
	unsigned int ban_nums[] = { 0,0,0,0,0,0,0 };

	/* fill field with random hidden tiles*/
	while (i < 21) {
		unsigned int val = dis(gen);
		if (ban_nums[val] != 3)
		{
			switch (val) {
			case 0:
			case 1:
			case 2:
				field[i].id = val;
				field[i].ability = BLOCK_ABILITY::burn_player;
				break;
			case 3:
			case 4:
			case 5:
				field[i].id = val;
				field[i].ability = BLOCK_ABILITY::delay_player;
				break;
			case 6:
				field[i].id = val;
				field[i].ability = BLOCK_ABILITY::delay_player;
				break;
			}
			field[i].revealed = false;
			++ban_nums[val];
			++i;
		}
	}
}

void puzzle_field::onHandle(SDL_Event & Event)
{
	if (Event.type == SDL_MOUSEBUTTONDOWN)
	{
		if ((Event.motion.x < 192) && (Event.motion.x > 0))
		{
			if ((Event.motion.y < 448) && (Event.motion.y > 0))
			{
				int RAW_X_INPUT = Event.motion.x / 64;
				int RAW_Y_INPUT = Event.motion.y / 64;
				field[((RAW_Y_INPUT * 3) + RAW_X_INPUT)].revealed = true;
				selected_blocks.push_front(&field[(int)((RAW_Y_INPUT * 3) + RAW_X_INPUT)]);
				++numselected;
			}
		}
	}
}

void puzzle_field::onRender(std::unique_ptr<SDL_Renderer, SDL_Deleter> & ren)
{
	for (int y = 0; y < 7; y++ )
	for (int x = 0; x < 3; x++)
	{
		if (field[(3 * y) + x].revealed)
		{
			SDL_Rect block = { 0, 0, 64, 64 };
			block.x += 64 * field[(3 * y) + x].id;
			renderTexture(texture_blocks, ren, x * 64, y * 64, &block);
		}
		else // use clip mystery block
		{
			SDL_Rect block = { 448, 0, 64, 64 };
			renderTexture(texture_blocks, ren, x * 64, y *64, &block);
		}
	}

}

void puzzle_field::onUpdate()
{
	if (numselected == 3)
	{
		BLOCK * tmp[3];
		unsigned int i = 0;

		while (!selected_blocks.empty()) 
		{
			tmp[i++] = selected_blocks.front();
			selected_blocks.pop_front();
		}

		if ((tmp[0]->id == tmp[1]->id) && (tmp[1]->id == tmp[2]->id))
		{
			//stay revealed
		}
		else
		{
			tmp[0]->revealed = tmp[1]->revealed = tmp[2]->revealed = false;
		}

		numselected = 0;
	}
}