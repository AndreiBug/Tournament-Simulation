#include "functions.h"

void ReleaseMemory(Team_list* teamList){
    Team_list* current_team = teamList;
    while (current_team != NULL) {
        Team_list* temp_team = current_team;
        current_team = current_team->next;

        Player_list* current_player = temp_team->team->players;
        while (current_player != NULL) {
            Player_list* temp_player = current_player;
            current_player = current_player->next;

            free(temp_player->player->firstName);
            free(temp_player->player->secondName);
            free(temp_player->player);
            free(temp_player);
        }
        free(temp_team->team->name);
        free(temp_team->team);
        free(temp_team);
    }
}

void CloseFiles(FILE* tasks, FILE* input_file, FILE* output_file){
    fclose(tasks);
    fclose(input_file);
    fclose(output_file);
}

int PowerOf2(int number){
    int power = 1;
    while(power * 2 <= number) {
        power *= 2;
    }
    return power;
}

void ShowTeams(Team_list* teamList, FILE* output_file){
    Team_list* current_team = teamList;
    while (current_team != NULL) {
        fprintf(output_file, "%s", current_team->team->name);
        current_team = current_team->next;
    }
}

float calculateTeamPoints(Team* team) {
    float nr_of_players = 0.0;
    int totalPoints = 0;
    Player_list* current = team->players;
    while (current != NULL) {
        totalPoints += current->player->points;
        current = current->next;
        nr_of_players++;
    }
    return totalPoints / nr_of_players;
}

void addPointsToPlayers(Team* team) {
    Player_list* currentPlayer = team->players;

    while (currentPlayer != NULL) {
        currentPlayer->player->points += 1.0;  // Increment each player's points by 1
        currentPlayer = currentPlayer->next;
    }
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
        // If the list is empty, make the new node the head
        *head = newNode;
    } else {
        // Traverse to the end of the list and add the new node
        Team_list *aux = *head;
        while (aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = newNode;
    }
}

Team_list* CopyTeamList(Team_list* TeamList, Player_list* players, int nr_of_players) {
    Team_list* copy = NULL;
    Team_list* current = NULL; // Pointer to keep track of the last copied team in the new list

    // Traverse the original TeamList
    while (TeamList != NULL) {
        // Allocate memory for the new team node
        Team_list* new_team_node = (Team_list*)malloc(sizeof(Team_list));
        new_team_node->team = (Team*)malloc(sizeof(Team));
        new_team_node->team->name = (char*)malloc(50 * sizeof(char));

        // Copy the name of the team
        strcpy(new_team_node->team->name, TeamList->team->name);
        new_team_node->team->players = NULL; // Initialize players list for the new team

        // Traverse through the players of the current team in TeamList
        Player_list* current_player = TeamList->team->players;
        int player_count = 0;
        while (current_player != NULL && player_count < nr_of_players) {
            // Allocate memory for the new player node
            Player_list* new_player_node = (Player_list*)malloc(sizeof(Player_list));
            new_player_node->player = (Player*)malloc(sizeof(Player));
            new_player_node->player->firstName = (char*)malloc(25 * sizeof(char));
            new_player_node->player->secondName = (char*)malloc(25 * sizeof(char));

            // Copy player data from 'current_player' to the new player node
            strcpy(new_player_node->player->firstName, current_player->player->firstName);
            strcpy(new_player_node->player->secondName, current_player->player->secondName);
            new_player_node->player->points = current_player->player->points;  // Copy the points correctly

            // Insert the new player node at the end of the players list of the new team
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

            // Move to the next player in TeamList
            current_player = current_player->next;
            player_count++;
        }

        // Link the new_team_node to the copied list
        new_team_node->next = NULL;
        if (copy == NULL) {
            copy = new_team_node;
            current = copy;
        } else {
            current->next = new_team_node;
            current = current->next;
        }

        // Move to the next team in TeamList
        TeamList = TeamList->next;
    }

    return copy;
}