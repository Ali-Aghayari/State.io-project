#pragma once

void readTroop(struct Troop * (troops[TroopsMax]), struct State * states, int id);
void writeTroop(struct Troop * (troops[TroopsMax]), struct State * states, int id);
void writeMap(struct State * states, int id);
void readMap(struct State * states, int id);
void readBooster(struct Booster * (boosters[BoostersMax]), int id);
void writeBooster(struct Booster * (boosters[BoostersMax]), int id);
void readOnlineBooster(struct OnlineBooster * (onlineBoosters[OnlineBoostersMax]), int id);
void writeOnlineBooster(struct OnlineBooster * (onlineBoosters[OnlineBoostersMax]), int id);
int CountStates(int id);
void addScore(int score , int id);
int howManyUsers();
void sortDataBase();
void deleteContinueMaps(int id);
void saveRandomMap(struct State * states, int name);
int CountRandomSave(int name);
void readRandomMap(struct State * states, int name);
int ReadyMapCount(int map);
void ReadyMapOpen(struct State * states, int map);

