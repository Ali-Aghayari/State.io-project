#pragma once

void gamePage();
void printTroopCount(struct State *input);
void printAllert(int team , int booster , int mode);
void loadMap(struct State *input);
void loadBooster(struct Booster *input);
void makeStates(struct State *states, int groups, int greyStatesCount);
void makeBooster(struct Booster * (boosters[BoostersMax]), struct State *states, int indexBoosters);
int makeTroops(struct Troop * (troops[TroopsMax]), struct State *states, int indexTroops, int reverseBoostFlag);
void boosterTimer(struct Booster * (boosters[BoostersMax]));
void troopsMoveAndPrint(struct Troop * (troops[TroopsMax]));
void myAI(struct State * states);
void freeEveryThing(struct State * states, struct Troop * (troops[TroopsMax]), struct Booster * (boosters[BoostersMax]), struct OnlineBooster * (onlineBoosters[OnlineBoostersMax]));
void endGame(int id, int mode, int socreChange);
void gameSetup(int newOrOld , int id, int map , int G , int S , int RandSave);