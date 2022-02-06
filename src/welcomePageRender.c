#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globalVariable.h"


void welcomePage() {
	SDL_Surface* sdlImage = SDL_LoadBMP("res/img/mainPage.bmp");
	if (sdlImage == NULL) {printf("Unable to load bitmap: %s \n", SDL_GetError());}
	SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer, sdlImage);
	SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL);
	SDL_DestroyTexture(sdlTexture);
	SDL_FreeSurface(sdlImage);
}
void outputScreen(char *input , int Xcenter , int Ycenter , int size, int RGB[3], int mode) {
	TTF_Font* font;
	if (mode == 1) {font = TTF_OpenFont("res/pricedown bl.otf", size);}
	if (mode == 2) {font = TTF_OpenFont("res/Play With Fire.ttf", size);}
	if (mode == 3) {font = TTF_OpenFont("res/Need for Font.ttf", size);}

	if ( !font ) {
		printf("Failed to load font: %s", TTF_GetError());
	}
	SDL_Surface* sdlText;
	SDL_Color color = { RGB[0], RGB[1],  RGB[2] };

	sdlText = TTF_RenderText_Solid( font, input , color );
	if ( !sdlText ) {
		printf("Failed to render text: %s", TTF_GetError());
	}
	SDL_Texture* textTexture;
	textTexture = SDL_CreateTextureFromSurface(sdlRenderer, sdlText);
	int width, height;
	TTF_SizeText(font, input, &width, &height);
	SDL_Rect src = { 0, 0, sdlText->w, sdlText->h };
	SDL_Rect dest = { Xcenter - (sdlText->w) / 2 , Ycenter - (sdlText->h) / 2  , sdlText->w, sdlText->h };
	SDL_RenderCopy( sdlRenderer, textTexture, &src, &dest );
	TTF_CloseFont( font );
	SDL_FreeSurface( sdlText );
	SDL_DestroyTexture( textTexture );
}
void welcomePagePreSetup() {
	int RGB[] = {158, 16, 48};
	welcomePage();
	outputScreen("state.io", SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 13, 100 , RGB, 1);
	outputScreen("enter user name : ", SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 13 * 3   , 70 , RGB, 1);
	outputScreen("created by : Ali Aghayari", SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 17 * 16 , 30 , RGB, 1);
}

int inputScreenAndRefresh()
{
	SDL_StartTextInput();
	char input[20] =	{' '};
	int running = 1, nextIndex = 0;
	int RGB[] = {158, 16, 48};
	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_TEXTINPUT)
			{
				if (strlen(input) < 15) {
					strcat(input, event.text.text);
					nextIndex = strlen(input);
				}
			} else if ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && strlen(input) > 1) {
				input[nextIndex - 1] = '\0';
				nextIndex--;
			}
			else if (event.type == SDL_KEYDOWN  && event.key.keysym.sym == SDLK_RETURN) {
				FILE *dataBase;
				char userName[20];
				int flag = 1, controlRank = 1, controlId = 1;
				int idCheck, rank, score;
				dataBase = fopen("res/DataBase/userNames.txt", "a+");
				if (dataBase == NULL)
				{
					printf("Error openning Files\n");
				}
				char line[256];
				while (fgets(line, 256, dataBase) != NULL)
				{
					sscanf(line, " %d %d %d %[^\n]s", &idCheck, &rank, &score, userName);
					if (score >= 0) {controlRank++;}
					controlId++;
					if (strcasecmp(userName, input + 1) == 0)
					{
						flag = 0;
						break;
					}
				}
				if (flag)
				{
					fprintf(dataBase, "%d %d %d%s\n", controlId, controlRank, 0, input);
					fclose(dataBase);
					SDL_StopTextInput();
					return controlId;
				}
				else {
					fclose(dataBase);
					SDL_StopTextInput();
					return idCheck;
				}
				running = 0;
			}
			else if  (event.type == SDL_QUIT ) {
				Mix_Quit();
				TTF_Quit();
				SDL_Quit();
			}
			SDL_Delay(1000 / FPS);
			SDL_RenderClear(sdlRenderer);
			welcomePagePreSetup();
			outputScreen(input, SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 13 * 5   , 50 , RGB, 1);
			SDL_RenderPresent(sdlRenderer);
		}
	}
	SDL_StopTextInput();
	return -1;
}
int welcomePageSetup() {
	welcomePagePreSetup();
	SDL_RenderPresent(sdlRenderer);
	return inputScreenAndRefresh();
}
