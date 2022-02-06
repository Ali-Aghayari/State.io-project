#include <SDL2/SDL2_gfxPrimitives.h>
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
	char string [50];
	sprintf(string, "res/DataBase/1S.txt", id);
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
	writeOnScreen(1, 1, 1);
	SDL_RenderPresent(sdlRenderer);
	int running = 1;
	int xMouse, yMouse;
	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			xMouse = event.motion.x;
			yMouse = event.motion.y;
			if (SCREEN_WIDTH / 2 - 250 < xMouse && xMouse < SCREEN_WIDTH / 2 + 250 && 100 < yMouse && yMouse < 220) {
				mainMenuscreen();
				writeOnScreen(2, 1, 1);
				SDL_RenderPresent(sdlRenderer);
				SDL_RenderClear(sdlRenderer);
				if (event.type == SDL_MOUSEBUTTONDOWN) {return 1;} // new game -> data map tarafo pak kon ?!!
			}
			else if (flag && SCREEN_WIDTH / 2 - 250 < xMouse && xMouse < SCREEN_WIDTH / 2 + 250 && 230 < yMouse && yMouse < 350) {
				mainMenuscreen();
				writeOnScreen(1, 2, 1);
				SDL_RenderPresent(sdlRenderer);
				SDL_RenderClear(sdlRenderer);
				if (event.type == SDL_MOUSEBUTTONDOWN) {
					// sound effect ke nmishe ?!?!
					// bayad flag ro avaz koni 
					return 2;
				} // data continue bekhoon age nadare begoo nadare
			}
			else if (SCREEN_WIDTH / 2 - 250 < xMouse && xMouse < SCREEN_WIDTH / 2 + 250 && 360 < yMouse && yMouse < 480) {
				mainMenuscreen();
				writeOnScreen(1, 1, 2);
				SDL_RenderPresent(sdlRenderer);
				SDL_RenderClear(sdlRenderer);
				if (event.type == SDL_MOUSEBUTTONDOWN) {return 3;} // safhe rank biar
			}
			else {
				mainMenuscreen();
				writeOnScreen(1, 1, 1);
				SDL_RenderPresent(sdlRenderer);
				SDL_RenderClear(sdlRenderer);
			}
			if  (event.type == SDL_QUIT) {
				running = 0;
				// cloooooooooooose
			}

		}

	}
}
int mainMenuSetup(int id) {
	mainMenuscreen();
	return mainMenuDetect(id);
}