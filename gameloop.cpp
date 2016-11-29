#include "gameloop.h"
#include "PuzzlePanic.h"
#include "SDL_timer.h"
#include "SDL_filesystem.h"
#define MS_PER_UPDATE 1500
void Run_GameLoop(std::unique_ptr<SDL_Renderer, SDL_Deleter> & ren)
{

	SDL_Event Event;
	std::string path = SDL_GetBasePath();
	std::string imagepath = path + "blocks.png";
	puzzle_field game(imagepath, ren);
	double previous = SDL_GetTicks();
	double lag = 0.0;
	while (true)
	{
		double current = SDL_GetTicks();
		double elapsed = current - previous;
		previous = current;
		lag += elapsed;

		while (SDL_PollEvent(&Event))
		{
			game.onHandle(Event);
		}

		while (lag >= MS_PER_UPDATE)
		{
			game.onUpdate();
			lag -= MS_PER_UPDATE;
		}

		game.onRender(ren);
		SDL_RenderPresent(ren.get());
	}
}