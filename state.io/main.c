#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>

#include "globalVariable.h"
#include "Init.h"
#include "welcomePageRender.h"
#include "menuPageRender.h"
#include "gameRender.h"
#include "rankingPageRender.h"



int main (int argv, char *args[]) // check headers !!
{
	init();
	int id = welcomePageSetup(); //music ?? //exit should exit it !!
	mainMenuSetup(id);
	// while (1) {
	// 	int mode = mainMenuSetup(id); // do i need a sdl delay ? // ye khorooji mide ke mire too game?
	// 	switch (mode) {
	// 	case 1:
	// 		newGameSetup();
	// 		// new game
	// 		break;
	// 	case 2:
	// 		// continue
	// 		break;
	// 	case 3:
	// 		rankingPageSetup ();
	// 		break;
	// 	}
	// }
	// // mainMenuscreen();

	return 0;
}




/*

void readTroop(struct Troop *(troops[TroopsMax]), struct State *states, int id)
{
    //make enough space for troops
    int control = 0;
    int team, xEnd, yEnd, boostedMode, indexOfState;
    float Vx, xPos, Vy, yPos;
    char string[20];
    sprintf(string, "%d", id);
    strcat(string, ".txt");
    FILE *dataBase = fopen(string, "r");
    if (dataBase == NULL)
    {
        printf("Error openning Files\n");
        return;
    }
    char line[256];
    while (fgets(line, 256, dataBase) != NULL)
    {
        sscanf(line, " %d %f %f %f %f %d %d %d %d", &team, &xPos, &yPos, &Vx, &Vy, &xEnd, &yEnd, &boostedMode, &indexOfState);
        ///////////////////////////////////////////////////////////////////////
        troops[control]->team = team;
        troops[control]->xPos = xPos;
        troops[control]->yPos = yPos;
        troops[control]->Vx = Vx;
        troops[control]->Vy = Vy;
        troops[control]->yEnd = yEnd;
        troops[control]->xEnd = xEnd;
        troops[control]->boostedMode = boostedMode;
        troops[control]->attackTo = (states + indexOfState);
        /////////////////////////////////////////////////////////////////////////
        control++;
    }
    fclose(dataBase);
    for (int i = control; i < TroopsMax; i++)
    {
        troops[i] = NULL;
    }
}

void writetTroop(struct Troop *(troops[TroopsMax]), int id)
{
    int index;
    char string[20];
    sprintf(string, "%d", id);
    strcat(string, ".txt");
    FILE *dataBase = fopen(string, "w");
    if (dataBase == NULL)
    {
        printf("Error openning Files\n");
        return;
    }
    for (int i = 0; i < TroopsMax; ++i)
    {
        if (troops[i] == NULL)
        {
            continue;
        }
        for (int j = 0; j < totalStates; ++j)
        {
            if (troops[i]->attackTo == (states + j))
            {
                index = j;
                break;
            }
        }
        fprintf(dataBase, "%d %f %f %f %f %d %d %d %d\n",troops[i]->team,troops[i]->xPos,troops[i]->yPos,troops[i]->Vx,troops[i]->Vy,troops[i]->xEnd,troops[i]->yEnd,troops[i]->boostedMode,index);
    }
    fclose(dataBase);
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct State
{
	int team;
	int shape;
	int troops;
	int xArea;
	int yArea;
	int selected;
	int attackCount;
	struct State *attackTo;
	int boostedMode;
};

int totalStates;

void makeStates(struct State *states, int groups, int greyStatesCount)
{
	srand(time(NULL));
	int Xmap, Ymap, map[7][5];
	for (int i = 0; i < groups; i++)
	{
		states[i * 2].boostedMode = 0;
		states[i * 2].attackTo = NULL;
		states[i * 2].selected = 0;
		states[i * 2].team = i + 1;
		states[i * 2].shape = rand() % 10;
		states[i * 2].troops = 15;
		do
		{
			Xmap = rand() % 7;
			Ymap = rand() % 5;
		} while (map[Xmap][Ymap] == 1);
		map[Xmap][Ymap] = 1;
		states[i * 2].xArea = Xmap;
		states[i * 2].yArea = Ymap;

		states[i * 2 + 1].boostedMode = 0;
		states[i * 2 + 1].attackTo = NULL;
		states[i * 2 + 1].selected = 0;
		states[i * 2 + 1].team = i + 1;
		states[i * 2 + 1].shape = rand() % 10;
		states[i * 2 + 1].troops = 15;
		do
		{
			Xmap = rand() % 7;
			Ymap = rand() % 5;
		} while (map[Xmap][Ymap] == 1);
		map[Xmap][Ymap] = 1;
		states[i * 2 + 1].xArea = Xmap;
		states[i * 2 + 1].yArea = Ymap;
	}
	for (int i = 0; i < greyStatesCount; i++)
	{
		states[i + 2 * groups].boostedMode = 0;
		states[i + 2 * groups].attackTo = NULL;
		states[i + 2 * groups].selected = 0;
		states[i + 2 * groups].team = 6;
		states[i + 2 * groups].shape = rand() % 10;
		states[i + 2 * groups].troops = 10;
		do
		{
			Xmap = rand() % 7;
			Ymap = rand() % 5;
		} while (map[Xmap][Ymap] == 1);
		map[Xmap][Ymap] = 1;
		states[i + 2 * groups].xArea = Xmap;
		states[i + 2 * groups].yArea = Ymap;
	}
}

void readMap(struct State *states, int id)
{
	//make enough space for state
	int team, shape, troops, xArea, yArea, selected, attackCount, boostedMode, indexOfState, control = 0;
	char string[20];
	sprintf(string, "%d", id);
	strcat(string, ".txt");
	FILE *dataBase = fopen(string, "r");
	if (dataBase == NULL)
	{
		printf("Error openning Files\n");
		return;
	}
	char line[256];
	while (fgets(line, 256, dataBase) != NULL)
	{
		sscanf(line, " %d %d %d %d %d %d %d %d %d", &team, &shape, &troops, &xArea, &yArea, &selected, &attackCount, &boostedMode, &indexOfState);
		///////////////////////////////////////////////////////////////////////
		(states + control)->team = team;
		(states + control)->shape = shape;
		(states + control)->troops = troops;
		(states + control)->xArea = xArea;
		(states + control)->yArea = yArea;
		(states + control)->selected = selected;
		(states + control)->attackCount = attackCount;
		(states + control)->boostedMode = boostedMode;
		(states + control)->attackTo = (states + indexOfState);
		/////////////////////////////////////////////////////////////////////////
		control++;
	}
	fclose(dataBase);
}

void writetMap(struct State *states, int id)
{
	int index;
	char string[20];
	sprintf(string, "%d", id);
	strcat(string, ".txt");
	FILE *dataBase = fopen(string, "w");
	if (dataBase == NULL)
	{
		printf("Error openning Files\n");
		return;
	}
	for (int i = 0; i < totalStates; ++i)
	{
		index = -1;
		if ((states + i)->attackTo != NULL)
		{
			for (int j = 0; j < totalStates; ++j)
			{
				if ((states + i)->attackTo == (states + j))
				{
					index = j;
					break;
				}
			}
		}
		fprintf(dataBase, "%d %d %d %d %d %d %d %d %d\n", (states + i)->team, (states + i)->shape, (states + i)->troops, (states + i)->xArea, (states + i)->yArea, (states + i)->selected, (states + i)->attackCount, (states + i)->boostedMode, index);
	}
	fclose(dataBase);
}
int main()
{
	srand(time(NULL));
	int groups = 5; // get it
	int greyStatesCount = 10 + rand() % 10;
	totalStates = 2 * groups + greyStatesCount;
	struct State *states = (struct State *)malloc(sizeof(struct State) * totalStates);
	makeStates(states, groups, greyStatesCount);
	readMap(states, 123);
	for (int i = 0; i < totalStates; i++)
	{
		printf("%d %d %d %d %d %d %d %d \n", (states + i)->team, (states + i)->shape, (states + i)->troops, (states + i)->xArea, (states + i)->yArea, (states + i)->selected, (states + i)->attackCount, (states + i)->boostedMode);
	}
	writetMap(states, 123);
	return 0;
}
*/

// save state !
// need to save troops !
// need to save states !
// need to save potions !
/*
format ?
in a username folder ?!?!?
- states
- troops
- posions

in states save every thing as it is
in troops save every thing as it is
.........................
*/






/*
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void readMap(truct State *states, int id)
{
	// state ro baayad dorost koniii
	char *string;
	sprintf(string, " %d", id);
	FILE *dataBase = fopen(string, "r");
	if (dataBase == NULL)
	{
		printf("Error openning Files\n");
		return;
	}

	char line[256];
	while (fgets(line, 256, dataBase) != NULL)
	{
		sscanf(line, " %d %d %d",team,shape,troops,xarea,yarea,selected,attackcount,index??,boost mode );
	}
	fclose(dataBase);
}

int main()
{
	//readMap();
	return 0;
}

*/









// int readFileFunc() {
// 	FILE *dataBase;
// 	dataBase = fopen("userDataBase.txt", "r");
// 	if ( dataBase == NULL )
// 	{
// 		printf("Press any key to exit...\n");
// 		return 1;
// 	}
// 	char line[256] ;
// 	while (fgets(line, sizeof(line), dataBase)) {
// 		if (line[strlen(line) - 1] == '\n') {line[strlen(line) - 1] = '\0';}
// 		char* token = strtok(line, ":");
// 		while (token != NULL) {
// 			printf("%s\n", token);
// 			token = strtok(NULL, ":");
// 		}
// 	}
// 	fclose(dataBase);
// 	return 0;
// }
// int append(){
// 	// read if its in there ???
// 	// if not :
// 	// i can use a+ !!

// 	// dont use tese in main !
// 	FILE *dataBase;
// 	dataBase = fopen("salam.txt", "a+");
// 	if ( dataBase == NULL )
// 	{
// 		printf("Press any key to exit...\n");
// 		return 1;
// 	}
// 	char user[] = "baba man ridam to in vaz";
// 	int id = 1021;
// 	int rank = 8;
// 	int playTime = 312;
// 	fprintf(dataBase, "%s", user);
// 	fprintf(dataBase, ":");
// 	fprintf(dataBase, "%d", id);
// 	fprintf(dataBase, ":");
// 	fprintf(dataBase, "%d", rank);
// 	fprintf(dataBase, ":");
// 	fprintf(dataBase, "%d", playTime);
//     fprintf(dataBase, "\n");
// 	fclose(dataBase);
// }

// todays plans :::
/*
 **************************************************************************
2 sarbaz ha ??
3 gif for loading page ?
5 bara dokme esc daste khar bezar
khod seda
8 dokme ghat seda (p)
9 dokme simple graph namooosan ?!?!?

*/

// **********************************************************

//-------------music
// Mix_Music* music;
// Mix_Chunk* sound;

// music = Mix_LoadMUS("res/music.mp3");
// sound = Mix_LoadWAV("res/music.mp3");
// if ( !music || !sound ) {
// 	printf("Failed to load music or sound: %s", Mix_GetError());
// }
// int result = Mix_PlayMusic( music, -1 );

// if ( result != 0 ) {
// 	printf("Failed to play music: %s", Mix_GetError());
// }
// int channel = Mix_PlayChannel( -1, sound, 0 );
// // Mix_Music *music = NULL;
// // music = Mix_LoadMUS(
// //             "music.mp3");
// // Mix_PlayMusic(music, -1);

// // Mix_Pause( channel );

// // SDL_Delay( 1000 );

// // Mix_Resume( channel );

//-------------music


// rgbs :
/*
0xffffc75f
0xffaaaa00
0xff5fc7ff
0xffff00ff
0xffccb5fc
0xffff6f91
0xffff9671
0xff916fff
0xff9b9b9e


Hex #C3447A done 9
Hex #BC243C done
Hex #45B8AC done 10
Hex #9B2335
Hex #E15D44 done 8
Hex #EFC050 done 7
Hex #5B5EA6
Hex #D65076 with 9 ??
Hex #B565A7

HEX: #FF6F61
*/

/////////////////////////////////////////////////////////////////////////

// Mix_FreeChunk( sound );
// Mix_FreeMusic( music );
// Mix_Quit();
// TTF_CloseFont( font );
// TTF_Quit();
// SDL_DestroyTexture( text_texture );
// SDL_FreeSurface( text );
// SDL_UpdateWindowSurface(sdlWindow);
// SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL);
// SDL_DestroyTexture(sdlTexture);
// SDL_FreeSurface(sdlImage);
// SDL_Quit();
// null ptr those thingies