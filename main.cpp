#include "gameloop.h"
#include "SDL.h"
using namespace std;

#define SCREEN_H 512
#define SCREEN_W 200

int main(int argc, char ** argv) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return EXIT_FAILURE;
	}

	std::unique_ptr<SDL_Window, SDL_Deleter> ptr_window(SDL_CreateWindow("Panic Puzzle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN), SDL_Deleter());
	std::unique_ptr<SDL_Renderer, SDL_Deleter> ptr_rend(SDL_CreateRenderer(ptr_window.get(), -1, SDL_RENDERER_ACCELERATED), SDL_Deleter());

	Run_GameLoop(ptr_rend);

	SDL_Quit();

	return EXIT_SUCCESS;
}