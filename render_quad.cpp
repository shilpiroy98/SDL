#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *argv[]) {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Failed to initialise SDL %s\n", SDL_GetError());
		return 0;
	}
	SDL_Window* window = SDL_CreateWindow(
		"my game window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);
	if(window == NULL) {
		printf("Failed to initialise SDL Window %s\n", SDL_GetError());
		return 0;
	}
	bool is_running = true;
	SDL_Event event;
	while(is_running) {
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				is_running = false;
			}
		}
		SDL_Delay(20);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
