CC = gcc
CFLAGS = -Wall
SDL_LIB = -I/Library/Frameworks/SDL2.framework/Headers
SDL_IMAGE_LIB = -I/Library/Frameworks/SDL2_image.framework/Headers 
FRAMEWORK = -F /Library/Frameworks -framework SDL2 -framework SDL2_image
LFLAGS = `sdl2-config --cflags --libs`

build_mac:
	$(CC) $(CFLAGS) main.c -o main $(SDL_LIB) $(SDL_IMAGE_LIB) $(FRAMEWORK) 

build_linux:
	$(CC) main.c -o main $(LFLAGS) 

clean:
	rm -f main
