#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("unable to initialise sdl, %s", SDL_GetError());
		return 0;
	}
	SDL_Window* window = SDL_CreateWindow(
		"my game",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	bool is_running = 1;
	SDL_Event e;
	while(is_running) {
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT) {
				is_running = 0;
			}
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(renderer);
			SDL_Rect rect { SCREEN_WIDTH/8, SCREEN_HEIGHT/8, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 };
			SDL_SetRenderDrawColor(renderer, 0xF3, 0xF3, 0x32, 0xFF);
			SDL_RenderFillRect(renderer, &rect);
			SDL_Rect out_rect { SCREEN_WIDTH/5, SCREEN_HEIGHT/5, SCREEN_WIDTH/3, SCREEN_HEIGHT/3 };
			SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x03, 0xFF);
			SDL_RenderDrawRect(renderer, &out_rect);
			SDL_SetRenderDrawColor(renderer, 0x00, 0x0F, 0xF3, 0xFF);
			SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT/6, SCREEN_WIDTH, SCREEN_HEIGHT/2);
			SDL_RenderPresent(renderer);

		}
		SDL_Delay(20);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
	SDL_Quit();
	return 0;

}
