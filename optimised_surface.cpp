#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* argv[]) {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Failed to initialise sdl, %s", SDL_GetError());
		return 0;
	}
	SDL_Window* window = SDL_CreateWindow(
		"my window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);
	SDL_Surface* surface = SDL_GetWindowSurface(window);
	SDL_Surface* img_surf = SDL_LoadBMP("images/stretch.bmp");
	SDL_Surface* opt_surf = SDL_ConvertSurface(img_surf, surface->format, 0);
	SDL_FreeSurface(img_surf);
	SDL_Rect rect {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_BlitScaled(opt_surf, NULL, surface, &rect);
	SDL_UpdateWindowSurface(window);
	bool is_run = 1;
	SDL_Event e;
	while(is_run) {
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT) {
				is_run = 0;
			}
		}
		SDL_Delay(20);
	}
	SDL_FreeSurface(opt_surf);
	SDL_FreeSurface(surface);
	surface = NULL;
	opt_surf = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
	return 0;
}
