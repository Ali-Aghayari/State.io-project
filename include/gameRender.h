#pragma once

void attackTest(struct State *attacker, struct State *defender);
void gamePage();
void loadMap( struct State * input);
void printTroopCount(struct State * input);
void gameSetup(int newOrOld , int id);
void loadBooster(int mode , float x , float y);
void wereToPutBoost();
int makeTroops(struct Troop * (troops[TroopsMax]), struct State *states, int indexBoosters) ;
void boosterTimer(struct Booster * (boosters[BoostersMax]));
void makeStates(struct State *states, int groups, int greyStatesCount);
void troopsMoveAndPrint(struct Troop * (troops[TroopsMax]));
void makeBooster(struct Booster * (boosters[BoostersMax]), struct State *states, int *indexBoosters);
void myAI(struct State *states);