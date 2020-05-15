#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
using namespace std;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum KeyPressSurfaces {
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

SDL_Window* window = NULL;
SDL_Surface* window_surface = NULL, *cur_surface = NULL;
SDL_Surface* key_press_surfaces[KEY_PRESS_SURFACE_TOTAL];

SDL_Surface* load_surface(string path) {
	SDL_Surface* loaded_surface = SDL_LoadBMP(path.c_str());
	if(loaded_surface == NULL) {
		printf("unable to load surface, %s", SDL_GetError());
	}
	return loaded_surface;
}

void init() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("unable to init sdl, %s", SDL_GetError());
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
	window_surface = SDL_GetWindowSurface(window);
}

void load_media() {
	key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT] = load_surface("images/press.bmp");
	key_press_surfaces[KEY_PRESS_SURFACE_UP] = load_surface("images/up.bmp");
	key_press_surfaces[KEY_PRESS_SURFACE_DOWN] = load_surface("images/down.bmp");
	key_press_surfaces[KEY_PRESS_SURFACE_LEFT] = load_surface("images/left.bmp");
	key_press_surfaces[KEY_PRESS_SURFACE_RIGHT] = load_surface("images/right.bmp");
}

void close() {
	for(int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i ) {
		SDL_FreeSurface(key_press_surfaces[i]);
		key_press_surfaces[i] = NULL;
	}
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	init();
	load_media();
	bool quit = 0;
	SDL_Event e;
	cur_surface = key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT];
	while(!quit) {
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT) {
				quit = 1;
			}
			else if(e.type == SDL_KEYDOWN) {
				switch(e.key.keysym.sym) {
					case SDLK_UP:
					cur_surface = key_press_surfaces[KEY_PRESS_SURFACE_UP];
					break;
					case SDLK_DOWN:
					cur_surface = key_press_surfaces[KEY_PRESS_SURFACE_DOWN];
					break;
					case SDLK_LEFT:
					cur_surface = key_press_surfaces[KEY_PRESS_SURFACE_LEFT];
					break;
					case SDLK_RIGHT:
					cur_surface = key_press_surfaces[KEY_PRESS_SURFACE_RIGHT];
					break;
					default:
					cur_surface = key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT];
					break;
				}
			}
		}
		SDL_BlitSurface(cur_surface, NULL, window_surface, NULL);
		SDL_UpdateWindowSurface(window);
	}
	close();

}
