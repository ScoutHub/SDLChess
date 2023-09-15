#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#define GAME_SPEED 100
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define ROWS 8
#define COLS 8
#define SIDE 0 // 0: White side, 1: Black side 

void destroy_game(SDL_Renderer* r, SDL_Window* w) {
	SDL_DestroyRenderer(r);
	SDL_DestroyWindow(w);
	SDL_Quit();
}

void draw_board(SDL_Renderer* r) {
	SDL_SetRenderDrawColor(r, 0, 0, 0, 255 );
    SDL_RenderClear(r);
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			SDL_Rect rect;
			rect.x = j * 100;
			rect.y = i * 100;
			rect.w = 100;
			rect.h = 100;
			SDL_RenderDrawRect(r, &rect);
			if(((j == 0 || j % 2 == 0) && (i == 0 || i % 2 == 0)) || ( i % 2 != 0 && j % 2 != 0)){
				if(SIDE == 0) SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
				else SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
			} else {
				if(SIDE == 0) SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
				else SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
			}
			SDL_RenderFillRect(r, &rect);
		}
	}
	SDL_RenderPresent(r);
}

int main(void) {
	if(SDL_Init(SDL_INIT_VIDEO) == -1) {
		printf("ERROR: SDL wasn't able to initialize.");
		return -1;
	}
	SDL_Window *window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	if(!window) {
		printf("ERROR: Window couldnt' created.");
		return -1;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(!renderer) {
		printf("ERROR: Renderer wasn't able to render");
		return -1;
	}
	int initted = IMG_Init(IMG_INIT_PNG);
	if(initted != IMG_INIT_PNG) {
		printf("Couldn't init image\n");
		return -1;
	}
	bool quit = false;
	SDL_Event event;
	while(!quit) {
		draw_board(renderer);
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE:
							quit = true;
							break;
						default:
							break;
					}
					break;
				default:
					break;
			}
		}
		SDL_Delay(GAME_SPEED);
	}

	destroy_game(renderer, window);
	return 0;
}
