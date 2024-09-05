#include "coada.c"
#include "functions.c"
#include "liste.c"
#include "stiva.c"
#include "arbori.c"

int main(int argc, char* argv[]) {
    FILE* tasks = fopen(argv[1], "r");
    FILE* input_file = fopen(argv[2], "r");
    FILE* output_file = fopen(argv[3], "w");

    if (tasks == NULL || input_file == NULL || output_file == NULL) {
        perror("Error opening files");
        return EXIT_FAILURE;
    }

    int nr_of_teams, nr_of_players;
    fscanf(input_file, "%d", &nr_of_teams);

    Team_list* teamList = NULL;

    for (int i = 0; i < nr_of_teams; i++) {
        Team_list* new_team = (Team_list*)malloc(sizeof(Team_list));
        if (new_team == NULL) {
            perror("Failed to allocate memory for new_team");
            return EXIT_FAILURE;
        }
        new_team->team = (Team*)malloc(sizeof(Team));
        if (new_team->team == NULL) {
            perror("Failed to allocate memory for new_team->team");
            return EXIT_FAILURE;
        }
        new_team->team->name = (char*)malloc(50 * sizeof(char));
        if (new_team->team->name == NULL) {
            perror("Failed to allocate memory for new_team->team->name");
            return EXIT_FAILURE;
        }
        new_team->team->players = NULL;
        new_team->next = teamList;  // adăugarea la începutul listei
        teamList = new_team;

        fscanf(input_file, "%d", &nr_of_players);
        fgetc(input_file);  // pentru a consuma newline-ul rămas

        if (fgets(new_team->team->name, 50, input_file) == NULL) {
            perror("Error reading team name");
            return EXIT_FAILURE;
        }

        for (int j = 0; j < nr_of_players; j++) {
            Player_list* new_player = (Player_list*)malloc(sizeof(Player_list));
            if (new_player == NULL) {
                perror("Failed to allocate memory for new_player");
                return EXIT_FAILURE;
            }
            new_player->player = (Player*)malloc(sizeof(Player));
            if (new_player->player == NULL) {
                perror("Failed to allocate memory for new_player->player");
                return EXIT_FAILURE;
            }

            new_player->player->firstName = (char*)malloc(25 * sizeof(char));
            new_player->player->secondName = (char*)malloc(25 * sizeof(char));
            if (new_player->player->firstName == NULL ||
                new_player->player->secondName == NULL) {
                perror("Failed to allocate memory for player names");
                return EXIT_FAILURE;
            }

            if (fscanf(input_file, "%s", new_player->player->firstName) !=
                    1 ||
                fscanf(input_file, "%s", new_player->player->secondName) !=
                    1 ||
                fscanf(input_file, "%f", &new_player->player->points) != 1) {
                fprintf(stderr, "Error reading player data\n");
                return EXIT_FAILURE;
            }

            new_player->next = new_team->team->players;
            new_team->team->players = new_player;
        }  
    }

    while (nr_of_teams != PowerOf2(nr_of_teams)) {
        delete_team_with_min_points(&teamList);
        nr_of_teams--;
    }

    ShowTeams(teamList, output_file);

    // task 3
    int roundNr = 1, top_teams = 8;
    float firstTeamPoints, secondTeamPoints;
    Team_list* savedTeams = NULL;

    while (nr_of_teams > 1) {
        fprintf(output_file, "\n--- ROUND NO:%d\n", roundNr);

        Queue* queue = createQueue();
        Team_list* teamList_copy = teamList;

        while (teamList_copy != NULL) {
            Match* match = (Match*)malloc(sizeof(Match));
            if (match == NULL) {
                perror("Failed to allocate memory for match");
                return EXIT_FAILURE;
            }
            char* match_line = (char*)malloc(table_line * sizeof(char));
            if (match_line == NULL) {
                perror("Failed to allocate memory for match_line");
                return EXIT_FAILURE;
            }
            memset(match_line, ' ', table_line - 1);
            match_line[table_line - 1] = '\0';

            match->firstTeam = teamList_copy->team;
            teamList_copy = teamList_copy->next;

            int i = 0;
            while (match->firstTeam->name[i] != '\n') {
                match_line[i] = match->firstTeam->name[i];
                i++;
            }
            match_line[33] = '-';

            match->secondTeam = teamList_copy->team;
            teamList_copy = teamList_copy->next;

            int pos_in_table = table_line - strlen(match->secondTeam->name) - 1;
            for (int j = 0; j < strlen(match->secondTeam->name); j++) {
                match_line[pos_in_table + j] = match->secondTeam->name[j];
            }

            fprintf(output_file, "%s", match_line);
            free(match_line);

            enQueue(queue, match);
        }

        StackNode* losers = NULL;
        StackNode* winners = NULL;

        while (queue->front != NULL) {
            Match* match = deQueue(queue);

            firstTeamPoints = calculateTeamPoints(match->firstTeam);
            secondTeamPoints = calculateTeamPoints(match->secondTeam);

            if (firstTeamPoints > secondTeamPoints) {
                addPointsToPlayers(match->firstTeam);
                push(&winners, match->firstTeam);
                push(&losers, match->secondTeam);
            } else {
                addPointsToPlayers(match->secondTeam);
                push(&losers, match->firstTeam);
                push(&winners, match->secondTeam);
            }
            free(match);
        }

        deleteStack(&losers);

        char* winners_line = (char*)malloc(sizeLineWinners * sizeof(char));
        if (winners_line == NULL) {
            perror("Failed to allocate memory for winners_line");
            return EXIT_FAILURE;
        }

        fprintf(output_file, "\nWINNERS OF ROUND NO:%d\n", roundNr);
        Team_list* newTeamList = NULL;
        int contor_teams = 0;
        while (winners != NULL) {
            Team* winner = pop(&winners);

            memset(winners_line, ' ', sizeLineWinners - 1);
            winners_line[34] = '-';
            winners_line[sizeLineWinners - 1] = '\0';
            strncpy(winners_line, winner->name, strlen(winner->name) - 1);

            float points = calculateTeamPoints(winner);
            char char_points[6];
            snprintf(char_points, 6, "%.2f", points);

            fprintf(output_file, "%s%s\n", winners_line, char_points);
            
            addAtEnd(&newTeamList, winner);
            contor_teams++;
        }

        if(contor_teams == top_teams){
            savedTeams = CopyTeamList(newTeamList, newTeamList->team->players, nr_of_players);
        }

        free(winners_line);
        teamList = newTeamList;

        deleteQueue(queue);
        roundNr++;
        nr_of_teams /= 2;
    }

    // task 4

    BSTNode* root = NULL;
    createBSTTree(&root, savedTeams);
    fprintf(output_file, "\n");
    fprintf(output_file, "TOP 8 TEAMS:\n");
    inorder(root, output_file);

    deleteBSTTree(root);

    // task 5
    AVLNode* AVLroot = NULL;
    fprintf(output_file, "\nTHE LEVEL 2 TEAMS ARE: \n");
    
    insertBSTIntoAVL(root, &AVLroot);
    int level = 0;
    printLevel2(AVLroot, output_file, level);

    deleteAVLTree(AVLroot);

    ReleaseMemory(teamList);
    CloseFiles(tasks, input_file, output_file);
}
