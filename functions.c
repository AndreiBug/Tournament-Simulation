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
