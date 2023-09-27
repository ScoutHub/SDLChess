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
#define PIECE_WIDTH 90
#define PIECE_HEIGHT 90

typedef struct {
	SDL_Surface* image;
	SDL_Texture* texture;
	int x, y, w, h;
	bool dead;
} ChessPiece;

typedef struct {
	ChessPiece* pawns;
	ChessPiece* bishop;
	ChessPiece* knight;
	ChessPiece* rook;
	ChessPiece queen;
	ChessPiece king;
} WhiteBoard;

typedef struct {
	ChessPiece* pawns;
	ChessPiece* bishop;
	ChessPiece* knight;
	ChessPiece* rook;
	ChessPiece queen;
	ChessPiece king;
} BlackBoard;

void destroy_game(SDL_Renderer* r, SDL_Window* w, WhiteBoard* white_board) {
	SDL_DestroyRenderer(r);
	SDL_DestroyWindow(w);
	for(int i = 0; i < 8; i++){
		SDL_DestroyTexture(white_board->pawns[i].texture);
	}
	IMG_Quit();
	SDL_Quit();
}

void draw_board(SDL_Renderer* r, WhiteBoard* white_board, BlackBoard* black_board) {
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
}

void draw_white_pieces(SDL_Renderer* renderer, WhiteBoard* white_board){
	for(int i = 0; i < 8; i++){
		SDL_Rect rect = { white_board->pawns[i].x, white_board->pawns[i].y, PIECE_WIDTH, PIECE_HEIGHT };
		SDL_RenderCopy(renderer, white_board->pawns[i].texture, NULL, &rect);
	}

	for (int i = 0; i < 2; i++) {
		SDL_Rect rect = { white_board->rook[i].x, white_board->rook[i].y, PIECE_WIDTH, PIECE_HEIGHT };
		SDL_RenderCopy(renderer, white_board->rook[i].texture, NULL, &rect);
	}

	for (int i = 0; i < 2; i++) {
		SDL_Rect rect = { white_board->bishop[i].x, white_board->bishop[i].y, PIECE_WIDTH, PIECE_HEIGHT };
		SDL_RenderCopy(renderer, white_board->bishop[i].texture, NULL, &rect);
	}

	for (int i = 0; i < 2; i++) {
		SDL_Rect rect = { white_board->knight[i].x, white_board->knight[i].y, PIECE_WIDTH, PIECE_HEIGHT };
		SDL_RenderCopy(renderer, white_board->knight[i].texture, NULL, &rect);
	}

	SDL_Rect rect = { white_board->queen.x, white_board->queen.y, PIECE_WIDTH, PIECE_HEIGHT };
	SDL_RenderCopy(renderer, white_board->queen.texture, NULL, &rect);
}

void draw_black_pieces(SDL_Renderer* renderer, BlackBoard* black_board) {
	for(int i = 0; i < 8; i++){
		SDL_Rect rect = { black_board->pawns[i].x, black_board->pawns[i].y, PIECE_WIDTH, PIECE_HEIGHT };
		SDL_RenderCopy(renderer, black_board->pawns[i].texture, NULL, &rect);
	}

	for (int i = 0; i < 2; i++) {
		SDL_Rect rect = { black_board->rook[i].x, black_board->rook[i].y, PIECE_WIDTH, PIECE_HEIGHT };
		SDL_RenderCopy(renderer, black_board->rook[i].texture, NULL, &rect);
	}

	for (int i = 0; i < 2; i++) {
		SDL_Rect rect = { black_board->bishop[i].x, black_board->bishop[i].y, PIECE_WIDTH, PIECE_HEIGHT };
		SDL_RenderCopy(renderer, black_board->bishop[i].texture, NULL, &rect);
	}

	for (int i = 0; i < 2; i++) {
		SDL_Rect rect = { black_board->knight[i].x, black_board->knight[i].y, PIECE_WIDTH, PIECE_HEIGHT };
		SDL_RenderCopy(renderer, black_board->knight[i].texture, NULL, &rect);
	}
	
	SDL_Rect rect2 = { black_board->queen.x, black_board->queen.y, PIECE_WIDTH, PIECE_HEIGHT };
	SDL_RenderCopy(renderer, black_board->queen.texture, NULL, &rect2);
}

void init_pieces_image(SDL_Renderer* renderer, WhiteBoard* white_board, BlackBoard* black_board) {
	int w_x = 5, w_y = 605, b_x = 5, b_y = 105;
	for(int i = 0; i < 8; i++){
		white_board->pawns[i].x = w_x;
		white_board->pawns[i].y = w_y;
		white_board->pawns[i].image = IMG_Load("assets/white_pieces/pawn.png");
		white_board->pawns[i].texture = SDL_CreateTextureFromSurface(renderer, white_board->pawns[i].image);
			
		black_board->pawns[i].x = b_x;
		black_board->pawns[i].y = b_y;
		black_board->pawns[i].image = IMG_Load("assets/black_pieces/pawn.png");
		black_board->pawns[i].texture = SDL_CreateTextureFromSurface(renderer, black_board->pawns[i].image);

		w_x += 100;
		b_x += 100;
	}

	w_x = 5;
	w_y = 705;
	b_x = 5;
	b_y = 5;
	for(int i = 0; i < 2; i++){
		white_board->rook[i].x = w_x;
		white_board->rook[i].y = w_y;
		white_board->rook[i].image = IMG_Load("assets/white_pieces/rook.png");
		white_board->rook[i].texture = SDL_CreateTextureFromSurface(renderer, white_board->rook[i].image);

		black_board->rook[i].x = b_x;
		black_board->rook[i].y = b_y;
		black_board->rook[i].image = IMG_Load("assets/black_pieces/rook.png");
		black_board->rook[i].texture = SDL_CreateTextureFromSurface(renderer, black_board->rook[i].image);

		w_x += 700;
		b_x += 700;
	}

	w_x = 205;
	w_y = 705;
	b_x = 205;
	b_y = 5;
	for(int i = 0; i < 2; i++){
		white_board->bishop[i].x = w_x;
		white_board->bishop[i].y = w_y;
		white_board->bishop[i].image = IMG_Load("assets/white_pieces/bishop.png");
		white_board->bishop[i].texture = SDL_CreateTextureFromSurface(renderer, white_board->bishop[i].image);

		black_board->bishop[i].x = b_x;
		black_board->bishop[i].y = b_y;
		black_board->bishop[i].image = IMG_Load("assets/black_pieces/bishop.png");
		black_board->bishop[i].texture = SDL_CreateTextureFromSurface(renderer, black_board->bishop[i].image);

		w_x += 300;
		b_x += 300;
	}

	w_x = 105;
	w_y = 705;
	b_x = 105;
	b_y = 5;
	for(int i = 0; i < 2; i++){
		white_board->knight[i].x = w_x;
		white_board->knight[i].y = w_y;
		white_board->knight[i].image = IMG_Load("assets/white_pieces/knight.png");
		white_board->knight[i].texture = SDL_CreateTextureFromSurface(renderer, white_board->knight[i].image);

		black_board->knight[i].x = b_x;
		black_board->knight[i].y = b_y;
		black_board->knight[i].image = IMG_Load("assets/black_pieces/knight.png");
		black_board->knight[i].texture = SDL_CreateTextureFromSurface(renderer, black_board->knight[i].image);

		w_x += 500;
		b_x += 500;
	}

	w_x = 405;
	w_y = 705;
	b_x = 405;
	b_y = 5;
	white_board->queen.x = w_x;
	white_board->queen.y = w_y;
	white_board->queen.image = IMG_Load("assets/white_pieces/queen.png");
	white_board->queen.texture = SDL_CreateTextureFromSurface(renderer, white_board->queen.image);;

	black_board->queen.x = b_x;
	black_board->queen.y = b_y;
	black_board->queen.image = IMG_Load("assets/black_pieces/queen.png");
	black_board->queen.texture = SDL_CreateTextureFromSurface(renderer, black_board->queen.image);;
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
	WhiteBoard white_board;
	BlackBoard black_board;

	white_board.pawns = (ChessPiece*) malloc(sizeof(ChessPiece) * 8);
	black_board.pawns = (ChessPiece*) malloc(sizeof(ChessPiece) * 8);

	white_board.rook = (ChessPiece*) malloc(sizeof(ChessPiece) * 2);
	black_board.rook = (ChessPiece*) malloc(sizeof(ChessPiece) * 2);

	white_board.bishop = (ChessPiece*) malloc(sizeof(ChessPiece) * 2);
	black_board.bishop = (ChessPiece*) malloc(sizeof(ChessPiece) * 2);

	white_board.knight = (ChessPiece*) malloc(sizeof(ChessPiece) * 2);
	black_board.knight = (ChessPiece*) malloc(sizeof(ChessPiece) * 2);

	init_pieces_image(renderer, &white_board, &black_board);
	if(white_board.pawns == NULL || black_board.pawns == NULL) {
		printf("ERROR: Cannot alloc. pawns\n");
		return -1;
	}
	bool quit = false;
	SDL_Event event;
	while(!quit) {
		draw_board(renderer, &white_board, &black_board);
		draw_white_pieces(renderer, &white_board);
		draw_black_pieces(renderer, &black_board);
		SDL_RenderPresent(renderer);
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

	destroy_game(renderer, window, &white_board);
	free(white_board.pawns);
	free(black_board.pawns);
	free(white_board.bishop);
	free(black_board.bishop);
	free(white_board.knight);
	free(black_board.knight);
	free(white_board.rook);
	free(black_board.rook);
	return 0;
}
