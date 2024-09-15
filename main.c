#include "coada.c"
#include "functions.c"
#include "liste.c"
#include "stiva.c"
#include "arbori.c"
#include "tasks.c"

int main(int argc, char* argv[]) {
    
    FILE* tasks = fopen(argv[1], "r");
    FILE* input_file = fopen(argv[2], "r");
    FILE* output_file = fopen(argv[3], "w");

    if (tasks == NULL || input_file == NULL || output_file == NULL) malloc_error();
    int task[5];
    for(int i = 0; i < 5; i++) {
        fscanf(tasks, "%d", &task[i]);
    }
    
    //task 1 2
    if(task[0] == 1 || task[1] == 1){
    int nr_of_teams, nr_of_players;
    Team_list* teamList = NULL;
    task12(output_file, input_file, &teamList, &nr_of_teams, &nr_of_players);
    
    // task 3
    if(task[2] == 1){
    Team_list* savedTeams = NULL;
    task3(output_file, &teamList, &nr_of_teams, nr_of_players, &savedTeams);

    // task 4
    if(task[3] == 1){
    task4(output_file, &savedTeams);

    // task 5
    if(task[4] == 1){
    task5(output_file, savedTeams);
    }}}
    ReleaseMemory(teamList);
    }
    CloseFiles(tasks, input_file, output_file);
}
