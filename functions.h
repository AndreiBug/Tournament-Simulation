#pragma once

#include "liste.h"
#include "stiva.h"
#include "coada.h"
#include <math.h>
#include <ctype.h>
#define table_line 69
#define sizeLineWinners 38

void ReleaseMemory(Team_list* teamList);

void CloseFiles(FILE* tasks, FILE* input_file, FILE* output_file);

int PowerOf2(int number);

void ShowTeams(Team_list* teamList, FILE* output_file);

float calculateTeamPoints(Team* team);

void addPointsToPlayers(Team* team);

void addAtEnd(Team_list** head, Team* v);

Team_list* CopyTeamList(Team_list* TeamList, Player_list* players, int nr_of_players);