#include "liste.h"

void delete_team_with_min_points(Team_list** head) {
    if (*head == NULL) return;

    Team_list *min_team = *head, *prev_min_team = NULL;
    Team_list *current = *head, *prev = NULL;

    int min_points = 0;
    int current_points = 0;

    Player_list* player = current->team->players;
    while (player != NULL) {
        min_points += player->player->points;
        player = player->next;
    }

    while (current != NULL) {
        current_points = 0;
        player = current->team->players;
        while (player != NULL) {
            current_points += player->player->points;
            player = player->next;
        }

        if (current_points < min_points) {
            min_points = current_points;
            min_team = current;
            prev_min_team = prev;
        }

        prev = current;
        current = current->next;
    }

    if (min_team == *head) {
        *head = min_team->next;
    } else {
        prev_min_team->next = min_team->next;
    }
    
    Player_list* current_player = min_team->team->players;
    while (current_player != NULL) {
        Player_list* temp_player = current_player;
        current_player = current_player->next;

        free(temp_player->player->firstName);
        free(temp_player->player->secondName);
        free(temp_player->player);
        free(temp_player);
    }

    free(min_team->team->name);
    free(min_team->team);
    free(min_team);
}

void addAtBeginning(Team_list **head, Team* v) {
    Team_list* newNode = (Team_list*)malloc(sizeof(Team_list));
    newNode->team = v;
    newNode->next = *head;
    *head = newNode;
}

void addAtEnd(Team_list** head, Team* v) {
    Team_list *newNode = (Team_list*)malloc(sizeof(Team_list));
    newNode->team = v;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        Team_list *aux = *head;
        while (aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = newNode;
    }
}

Team_list* CopyTeamList(Team_list* TeamList, int nr_of_players) {
    Team_list* copy = NULL;
    Team_list* current = NULL;

    while (TeamList != NULL) {
        Team_list* new_team_node = (Team_list*)malloc(sizeof(Team_list));
        new_team_node->team = (Team*)malloc(sizeof(Team));
        new_team_node->team->name = (char*)malloc(50 * sizeof(char));

        strcpy(new_team_node->team->name, TeamList->team->name);
        new_team_node->team->players = NULL;

        Player_list* current_player = TeamList->team->players;
        int player_count = 0;
        while (current_player != NULL && player_count < nr_of_players) {
            Player_list* new_player_node = (Player_list*)malloc(sizeof(Player_list));
            new_player_node->player = (Player*)malloc(sizeof(Player));
            new_player_node->player->firstName = (char*)malloc(25 * sizeof(char));
            new_player_node->player->secondName = (char*)malloc(25 * sizeof(char));

            strcpy(new_player_node->player->firstName, current_player->player->firstName);
            strcpy(new_player_node->player->secondName, current_player->player->secondName);
            new_player_node->player->points = current_player->player->points;

            new_player_node->next = NULL;
            if (new_team_node->team->players == NULL) {
                new_team_node->team->players = new_player_node;
            } else {
                Player_list* temp = new_team_node->team->players;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = new_player_node;
            }

            current_player = current_player->next;
            player_count++;
        }

        new_team_node->next = NULL;
        if (copy == NULL) {
            copy = new_team_node;
            current = copy;
        } else {
            current->next = new_team_node;
            current = current->next;
        }
        TeamList = TeamList->next;
    }

    return copy;
}