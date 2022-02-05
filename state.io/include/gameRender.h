#pragma once

void attackTest(struct State *attacker, struct State *defender);
void gamePage();
void loadMap( struct State * input);
void printTroopCount(struct State * input);
void gameSetup();
void loadBooster(int mode , float x , float y);
void wereToPutBoost();
void makeStates(struct State *states, int totalStates, int groups, int greyStatesCount);