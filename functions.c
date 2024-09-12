#include "functions.h"

void malloc_error(){
    perror("Failed to allocate memory using malloc.");
    exit(EXIT_FAILURE);
}

void removeSpaces(char *str) {
    int len = strlen(str);
    
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[len - 1] = '\0';
        len--;
    }
}

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
        fprintf(output_file, "%s\n", current_team->team->name);
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
        currentPlayer->player->points += 1.0;
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