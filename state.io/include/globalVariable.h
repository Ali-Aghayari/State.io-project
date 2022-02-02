#pragma once

#define FPS 60
#define SCREEN_WIDTH 64*3*7
#define SCREEN_HEIGHT 64*3*5

SDL_Window *sdlWindow ;
SDL_Renderer *sdlRenderer;

struct Troop{
	int mode;
	float xPos; // int ?
	float yPos; // int ?
	float Vx;
	float Vy;
	int xEnd;
	int yEnd;
};

struct State{
	int team;
	int shape;
	int toops; // age man betoonam begam toops[i]= State.troop va kharab nashe khooobe vali fek nakonam 
	int xArea;
	int Yarea;

};

struct Player{
	// ????????????????????
	// voroodi tedad miad 
	// tedad state 
	// rank ya score ya chizi ? 
};