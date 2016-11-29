#ifndef GAME_LOOP_H
#define GAME_LOOP_H
#include "PanicPuzzleCommon.h"
void Run_GameLoop(std::unique_ptr<SDL_Renderer, SDL_Deleter> & ren);
#endif // !GAME_LOOP_H