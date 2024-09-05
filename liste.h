#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Team_list {
    struct Team* team;
    struct Team_list* next;
} Team_list;

typedef struct Team {
    char* name;
    struct Player_list* players;
} Team;

typedef struct Player_list {
    struct Player* player;
    struct Player_list* next;
} Player_list;

typedef struct Player {
    char* firstName;
    char* secondName;
    float points;
} Player;

typedef struct Match{
    Team *firstTeam, *secondTeam;
} Match;

void delete_team_with_min_points(Team_list** head);
