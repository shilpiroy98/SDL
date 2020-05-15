#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Surface* surface = NULL, *img_surface = NULL;

void initialise() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("unable to initialise SDL, %s", SDL_GetError());
		exit(0);
	}
	window = SDL_CreateWindow(
		"my window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);
	surface = SDL_GetWindowSurface(window);

}

void load_image() {
	img_surface = SDL_LoadBMP("images/hello_world.bmp");
	if(img_surface == NULL) {
		printf("Unable to load image, %s", SDL_GetError());
		exit(0);
	}
}

void copy_image_to_screen() {
	SDL_BlitSurface(img_surface, NULL, surface, NULL);
	SDL_UpdateWindowSurface(window);
}

void quit_sdl() {
	SDL_FreeSurface(surface);
	surface = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	initialise();
	load_image();
	copy_image_to_screen();
	SDL_Event event;
	bool is_running = true;
	while(is_running) {
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				is_running = false;
			}
		}
		SDL_Delay(20);
	}
	quit_sdl();
}
