#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include "globalVariable.h"
#include "welcomePageRender.h"


void mainMenuscreen() {
	SDL_Surface* sdlImage = SDL_LoadBMP("res/img/mainMenu.bmp");
	if (sdlImage == NULL) {printf("Unable to load bitmap: %s \n", SDL_GetError());}
	SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer, sdlImage);
	SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL);
	SDL_DestroyTexture(sdlTexture);
	SDL_FreeSurface(sdlImage);
}
void writeOnScreen(int mode1, int mode2, int mode3) {
	boxRGBA(sdlRenderer, SCREEN_WIDTH / 2 - 250, 100, SCREEN_WIDTH / 2 + 250, 220, 0, 0, 0, 100);
	boxRGBA(sdlRenderer, SCREEN_WIDTH / 2 - 250, 230, SCREEN_WIDTH / 2 + 250, 350, 0, 0, 0, 100);
	boxRGBA(sdlRenderer, SCREEN_WIDTH / 2 - 250, 360, SCREEN_WIDTH / 2 + 250, 480, 0, 0, 0, 100);
	int RGB[] = {100, 100, 100};
	outputScreen("New Game", SCREEN_WIDTH / 2 , 160, 130 - 30 * mode1 , RGB, mode1);
	outputScreen("Continue", SCREEN_WIDTH / 2 , 290, 130 - 30 * mode2 , RGB, mode2);
	outputScreen("Ranking", SCREEN_WIDTH / 2 , 420, 130 - 30 * mode3 , RGB, mode3);
}
int mainMenuDetect(int id) {
	int flag = 1;

	char temp[10] = {" "};
	char string [50] = "res/DataBase/";
	sprintf(temp, "%d", id);
	strcat(string, temp);
	strcat(string, "S.txt");
	FILE* test = fopen(string, "r");

	if (test == NULL) {flag = 0;}
	else {
		int lines = 0;
		char line[256];
		while (fgets(line, 256, test) != NULL)
		{
			lines++;
		}
		if (lines == 0) {flag = 0;}
	}
	int mode1=1;  int mode2=1; int mode3=1;

	writeOnScreen(1, 1, 1);
	SDL_RenderPresent(sdlRenderer);
	int running = 1;
	int xMouse, yMouse;
	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			mode1 = 1; mode2 = 1; mode3 = 1;
			xMouse = event.motion.x;
			yMouse = event.motion.y;
			if (SCREEN_WIDTH / 2 - 250 < xMouse && xMouse < SCREEN_WIDTH / 2 + 250 && 100 < yMouse && yMouse < 220) {
				mode1 = 2;
				if (event.type == SDL_MOUSEBUTTONDOWN) {return 1;}
			}
			else if (flag && SCREEN_WIDTH / 2 - 250 < xMouse && xMouse < SCREEN_WIDTH / 2 + 250 && 230 < yMouse && yMouse < 350) {
				mode2 = 2;
				if (event.type == SDL_MOUSEBUTTONDOWN) {return 2;}
			}
			else if (SCREEN_WIDTH / 2 - 250 < xMouse && xMouse < SCREEN_WIDTH / 2 + 250 && 360 < yMouse && yMouse < 480) {
				mode3 = 2;
				if (event.type == SDL_MOUSEBUTTONDOWN) {return 3;}
			}
			if  (event.type == SDL_QUIT) {
				SDL_DestroyRenderer(sdlRenderer);
				SDL_DestroyWindow(sdlWindow);
				TTF_Quit();
				SDL_Quit();
				exit(0);
			}
		}
		SDL_RenderClear(sdlRenderer);
		mainMenuscreen();
		writeOnScreen(mode1, mode2, mode3);
		SDL_RenderPresent(sdlRenderer);
	}
	return -1;
}
int mainMenuSetup(int id) {
	mainMenuscreen();
	return mainMenuDetect(id);
}