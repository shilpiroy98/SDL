#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
using namespace std;

int main() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
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
	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) & imgFlags)) {
		printf( "Flag not initialised SDL Error: %s\n", SDL_GetError());
		return 0;
	}
	SDL_Surface* win_surf = SDL_GetWindowSurface(window);
	SDL_Surface* loaded_surf = IMG_Load("images/loaded.png");
	SDL_Surface* opti_surf = SDL_ConvertSurface(loaded_surf, win_surf->format, 0);
	SDL_FreeSurface(loaded_surf);
	SDL_Rect rect;
	rect.x = rect.y = 0;
	rect.w = SCREEN_WIDTH;
	rect.h = SCREEN_HEIGHT;
	SDL_BlitScaled(opti_surf, NULL, win_surf, &rect);
	SDL_UpdateWindowSurface(window);
	bool is_run = 1;
	SDL_Event e;
	while(is_run) {
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT) {
				is_run = false;
			}
		}
		SDL_Delay(20);
	}
	SDL_FreeSurface(win_surf);
	win_surf = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}
