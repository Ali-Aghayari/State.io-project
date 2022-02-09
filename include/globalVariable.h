#pragma once


#define FPS 60
#define SCREEN_WIDTH 64*3*7
#define SCREEN_HEIGHT 64*3*5

#define MAP1T 20


#define MapSize 64*3
#define HalfSize 32*3
#define BoosterSize 50
#define BoosterTime 900
#define BoosterDeff 150
#define AllertTime 100
#define Sorat 1.8
#define Speed 25
#define MaxGroup 5
#define GreyTeam 6
#define MyTeam 1
#define StartingT 15
#define StartingG 10

#define GrowRate 100
#define BoostersMax 3
#define OnlineBoostersMax 6

#define TroopsMax 2000
#define StatesMax 35
#define MaxInState 50

#define ABS(a) a>0 ? a : -a
#define MAX(a,b) a > b ? a : b
#define MIN(a, b) a < b ? a : b

SDL_Window *sdlWindow ;
SDL_Renderer *sdlRenderer;

struct Booster {
	int mode;
	int xPos;
	int yPos;
	int teamOnIt[6];
	int timeLimit;
};
struct OnlineBooster {
	int mode;
	int timer;
};
struct Troop {
	int team;
	struct State *attackTo;
	float xPos;
	float yPos;
	float Vx;
	float Vy;
	int xEnd;
	int yEnd;
	int boostedMode;
};

struct State {
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



// int TroopsMax;
// int TroopsCount;
int totalStates;
struct Troop ** temper1;
struct Troop ** temper2;
