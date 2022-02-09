#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globalVariable.h"
#include "welcomePageRender.h"
#include "menuPageRender.h"
#include "gameRender.h"

void readTroop(struct Troop * (troops[TroopsMax]), struct State * states, int id)
{
	char temp[5];
	char string [50] = "res/DataBase/";
	sprintf(temp, "%d", id);
	strcat(string, temp);
	strcat(string, "T.txt");
	int control = 0;
	int team, xEnd, yEnd, boostedMode, indexOfState;
	float Vx, xPos, Vy, yPos;
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
		troops[control] = (struct Troop *)malloc(sizeof(struct Troop));
		troops[control]->team = team;
		troops[control]->xPos = xPos;
		troops[control]->yPos = yPos;
		troops[control]->Vx = Vx;
		troops[control]->Vy = Vy;
		troops[control]->yEnd = yEnd;
		troops[control]->xEnd = xEnd;
		troops[control]->boostedMode = boostedMode;
		troops[control]->attackTo = (states + indexOfState);
		control++;
	}
	fclose(dataBase);
}
void writeTroop(struct Troop * (troops[TroopsMax]), struct State * states, int id)
{
	char temp[5];
	char string [50] = "res/DataBase/";
	sprintf(temp, "%d", id);
	strcat(string, temp);
	strcat(string, "T.txt");
	int index;
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
		fprintf(dataBase, "%d %f %f %f %f %d %d %d %d\n", troops[i]->team, troops[i]->xPos, troops[i]->yPos, troops[i]->Vx, troops[i]->Vy, troops[i]->xEnd, troops[i]->yEnd, troops[i]->boostedMode, index);
	}
	fclose(dataBase);
}
void writeMap(struct State * states, int id)
{
	char temp[5];
	char string [50] = "res/DataBase/";
	sprintf(temp, "%d", id);
	strcat(string, temp);
	strcat(string, "S.txt");
	int index;
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
void readMap(struct State * states, int id)
{
	char temp[5];
	char string [50] = "res/DataBase/";
	sprintf(temp, "%d", id);
	strcat(string, temp);
	strcat(string, "S.txt");
	int team, shape, troops, xArea, yArea, selected, attackCount, boostedMode, indexOfState, control = 0;
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
		(states + control)->team = team;
		(states + control)->shape = shape;
		(states + control)->troops = troops;
		(states + control)->xArea = xArea;
		(states + control)->yArea = yArea;
		(states + control)->selected = selected;
		(states + control)->attackCount = attackCount;
		(states + control)->boostedMode = boostedMode;
		if (indexOfState == -1) {(states + control)->attackTo = NULL;}
		else {(states + control)->attackTo = (states + indexOfState);}
		control++;
	}
	fclose(dataBase);
}
void readBooster(struct Booster * (boosters[BoostersMax]), int id)
{
	char temp[5];
	char string [50] = "res/DataBase/";
	sprintf(temp, "%d", id);
	strcat(string, temp);
	strcat(string, "B.txt");
	int index, mode, timelimit, xPos, yPos, team[6];
	FILE *dataBase = fopen(string, "r");
	if (dataBase == NULL)
	{
		printf("Error openning Files\n");
		return;
	}
	char line[256];
	while (fgets(line, 256, dataBase) != NULL)
	{
		sscanf(line, " %d %d %d %d %d %d %d %d %d %d %d", &index, &mode, &timelimit, &xPos, &yPos, team + 0, team + 1, team + 2, team + 3, team + 4, team + 5);
		boosters[index] = (struct Booster *)malloc(sizeof(struct Booster));
		boosters[index]->mode = mode;
		boosters[index]->timeLimit = timelimit;
		boosters[index]->xPos = xPos;
		boosters[index]->yPos = yPos;
		for (int i = 0; i < 6; i++)
		{
			boosters[index]->teamOnIt[i] = team[i];
		}
	}
	fclose(dataBase);
}
void writeBooster(struct Booster * (boosters[BoostersMax]), int id)
{
	char temp[5];
	char string [50] = "res/DataBase/";
	sprintf(temp, "%d", id);
	strcat(string, temp);
	strcat(string, "B.txt");

	FILE *dataBase = fopen(string, "w");
	if (dataBase == NULL)
	{
		printf("Error openning Files\n");
		return;
	}
	for (int i = 0; i < BoostersMax; i++)
	{
		if (boosters[i] == NULL)
		{
			continue;
		}
		fprintf(dataBase, "%d %d %d %d %d %d %d %d %d %d %d\n", i, boosters[i]->mode, boosters[i]->timeLimit, boosters[i]->xPos, boosters[i]->yPos, boosters[i]->teamOnIt[0], boosters[i]->teamOnIt[1], boosters[i]->teamOnIt[2], boosters[i]->teamOnIt[3], boosters[i]->teamOnIt[4], boosters[i]->teamOnIt[5]);
	}
	fclose(dataBase);
}
void readOnlineBooster(struct OnlineBooster * (onlineBoosters[OnlineBoostersMax]), int id)
{
	char temp[5];
	char string [50] = "res/DataBase/";
	sprintf(temp, "%d", id);
	strcat(string, temp);
	strcat(string, "O.txt");
	int index, mode, timer;
	FILE *dataBase = fopen(string, "r");
	if (dataBase == NULL)
	{
		printf("Error openning Files\n");
		return;
	}
	char line[256];
	while (fgets(line, 256, dataBase) != NULL)
	{
		sscanf(line, " %d %d %d", &index, &mode, &timer);
		onlineBoosters[index] = (struct OnlineBooster *)malloc(sizeof(struct OnlineBooster));
		onlineBoosters[index]->mode = mode;
		onlineBoosters[index]->timer = timer;
	}
	fclose(dataBase);
}

void writeOnlineBooster(struct OnlineBooster * (onlineBoosters[OnlineBoostersMax]), int id)
{
	char temp[5];
	char string [50] = "res/DataBase/";
	sprintf(temp, "%d", id);
	strcat(string, temp);
	strcat(string, "O.txt");
	FILE *dataBase = fopen(string, "w");
	if (dataBase == NULL)
	{
		printf("Error openning Files\n");
		return;
	}
	for (int i = 0; i < OnlineBoostersMax; i++)
	{
		if (onlineBoosters[i] == NULL)
		{
			continue;
		}
		fprintf(dataBase, "%d %d %d\n", i, onlineBoosters[i]->mode, onlineBoosters[i]->timer);
	}
	fclose(dataBase);
}
int CountStates(int id) {
	char temp[5];
	char string [50] = "res/DataBase/";
	sprintf(temp, "%d", id);
	strcat(string, temp);
	strcat(string, "S.txt");
	int stateCount = 0;
	FILE *dataBase = fopen(string, "r");
	if (dataBase == NULL)
	{
		printf("Error openning Files\n");
	}
	char line[256];
	while (fgets(line, 256, dataBase) != NULL)
	{
		stateCount++;
	}
	fclose(dataBase);
	return stateCount;
}
void addScore(int score , int id) {
	FILE *dataBase, *temp;
	char userName[20];
	int idCheck, rank, scoreCheck;
	dataBase = fopen("res/DataBase/userNames.txt", "r");
	temp = fopen("res/DataBase/userNamesTemp.txt", "w");
	char line[256];
	while (fgets(line, 256, dataBase) != NULL)
	{
		sscanf(line, " %d %d %d %[^\n]s", &idCheck, &rank, &scoreCheck, userName);
		if (idCheck == id) {scoreCheck += score;}
		fprintf(temp, "%d %d %d %s\n", idCheck, rank, scoreCheck , userName);
	}
	fclose(dataBase);
	fclose(temp);
}
int howManyUsers() {
	FILE  *temp; int count = 0;
	temp = fopen("res/DataBase/userNamesTemp.txt", "r");
	char line[256];
	while (fgets(line, 256, temp) != NULL)
	{
		count++;
	}
	fclose(temp);
	return count;
}
void sortDataBase() {
	FILE *temp, *dataBase;
	int count = howManyUsers();
	int idCheck, rank, scoreCheck, tempId, tempScore;
	char userName[15], line[256];
	int save[100][2] = {{0}};

	temp = fopen("res/DataBase/userNamesTemp.txt", "r");
	for (int i = 0 ; fgets(line, 256, temp) != NULL && i < count ; i++)
	{
		sscanf(line, " %d %d %d %[^\n]s", &idCheck, &rank, &scoreCheck, userName);
		save[i][0] = scoreCheck;
		save[i][1] = idCheck;
	}
	fseek(temp, 0, SEEK_SET);

	for (int i = 0; i < count; ++i)
	{
		for (int j = i + 1; j < count; ++j)
		{
			if (save[j][0] > save[i][0]) {
				tempId = save[j][1];
				tempScore = save[j][0];
				save[j][0] = save[i][0];
				save[j][1] = save[i][1];
				save[i][0] = tempScore;
				save[i][1] = tempId;
			}
		}
	}
	dataBase = fopen("res/DataBase/userNames.txt", "w");
	for (int i = 0; i < count; ++i)
	{
		fseek(temp, 0, SEEK_SET);
		while (fgets(line, 256, temp) != NULL)
		{
			sscanf(line, " %d %d %d %s", &idCheck, &rank, &scoreCheck, userName);
			if (save[i][1] == idCheck) {
				fprintf(dataBase, "%d %d %d %s\n", idCheck, i + 1 , save[i][0], userName);
				break;
			}
		}
	}
	fclose(temp);
	fclose(dataBase);
}
void deleteContinueMaps(int id) {
	char temp[5];
	sprintf(temp, "%d", id);

	char string [50] = "res/DataBase/";
	strcat(string, temp);
	strcat(string, "B.txt");
	FILE *dataBase;
	dataBase = fopen(string, "w");
	fclose(dataBase);

	string[0] = '\0';
	strcat(string, "res/DataBase/");
	strcat(string, temp);
	strcat(string, "O.txt");
	dataBase = fopen(string, "w");
	fclose(dataBase);

	string[0] = '\0';
	strcat(string, "res/DataBase/");
	strcat(string, temp);
	strcat(string, "S.txt");
	dataBase = fopen(string, "w");
	fclose(dataBase);

	string[0] = '\0';
	strcat(string, "res/DataBase/");
	strcat(string, temp);
	strcat(string, "T.txt");
	dataBase = fopen(string, "w");
	fclose(dataBase);
}
void saveRandomMap(struct State * states, int name) {
	char temp[5];
	char string [50] = "res/DataBase/SavedMaps/";
	sprintf(temp, "%d", name);
	strcat(string, temp);
	strcat(string, "S.txt");
	int index;
	FILE *dataBase = fopen(string, "w");
	if (dataBase == NULL)
	{
		printf("Error openning Files\n");
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
int CountRandomSave(int name) {
	char temp[5];
	char string [50] = "res/DataBase/SavedMaps/";
	sprintf(temp, "%d", name);
	strcat(string, temp);
	strcat(string, "S.txt");
	int stateCount = 0;
	FILE *dataBase = fopen(string, "r");
	if (dataBase == NULL)
	{
		printf("Error openning Files\n");
	}
	char line[256];
	while (fgets(line, 256, dataBase) != NULL)
	{
		stateCount++;
	}
	fclose(dataBase);
	return stateCount;
}
void readRandomMap(struct State * states, int name) {
	char temp[5];
	char string [50] = "res/DataBase/SavedMaps/";
	sprintf(temp, "%d", name);
	strcat(string, temp);
	strcat(string, "S.txt");
	int team, shape, troops, xArea, yArea, selected, attackCount, boostedMode, indexOfState, control = 0;
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
		(states + control)->team = team;
		(states + control)->shape = shape;
		(states + control)->troops = troops;
		(states + control)->xArea = xArea;
		(states + control)->yArea = yArea;
		(states + control)->selected = selected;
		(states + control)->attackCount = attackCount;
		(states + control)->boostedMode = boostedMode;
		if (indexOfState == -1) {(states + control)->attackTo = NULL;}
		else {(states + control)->attackTo = (states + indexOfState);}
		control++;
	}
	fclose(dataBase);
}
int ReadyMapCount(int map) {
	char temp[5];
	char string [50] = "res/DataBase/ReadyMaps/map";
	sprintf(temp, "%d", map);
	strcat(string, temp);
	strcat(string, ".txt");
	int stateCount = 0;
	FILE *dataBase = fopen(string, "r");
	if (dataBase == NULL)
	{
		printf("Error openning Files\n");
	}
	char line[256];
	while (fgets(line, 256, dataBase) != NULL)
	{
		stateCount++;
	}
	fclose(dataBase);
	return stateCount;
}
void ReadyMapOpen(struct State * states, int map) {
	char temp[5];
	char string [50] = "res/DataBase/ReadyMaps/map";
	sprintf(temp, "%d", map);
	strcat(string, temp);
	strcat(string, ".txt");
	int team, shape, troops, xArea, yArea, selected, attackCount, boostedMode, indexOfState, control = 0;
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
		(states + control)->team = team;
		(states + control)->shape = shape;
		(states + control)->troops = troops;
		(states + control)->xArea = xArea;
		(states + control)->yArea = yArea;
		(states + control)->selected = selected;
		(states + control)->attackCount = attackCount;
		(states + control)->boostedMode = boostedMode;
		if (indexOfState == -1) {(states + control)->attackTo = NULL;}
		else {(states + control)->attackTo = (states + indexOfState);}
		control++;
	}
	fclose(dataBase);
}
