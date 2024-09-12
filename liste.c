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