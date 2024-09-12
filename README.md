# lanParty
Tema PA

-TASK I-
1. I opened the files from which the information needs to be processed and I declared all the variables that i will use throughout the code;
2. I read the number of teams and created a for loop in which I read all the teams with their names. In this loop i created another for loop to read the players with their names and individual points;
3. I created a function to erase all the possible spaces or endlines from the end of the team name;
4. I added every new team to the beginning of the list;
5. I remember the beginning of the team and the beginning of every team players for future processing;

-TASK II-
1. For task 2 I created a while loop and I deleted the teams with the lowest score with delete_team_with_min_points function until the number of teams was equal to a power of 2;
2. I updated the number of teams every iteration;
3. In the end, I made a function ShowTeams that writes all the team names in the output file.

-TASK III-
1. I declared the variables that will help me completing this task;
2. I made a while loop that will iterate until only one team will be left which will be our winner;
3. I made another while loop in which I wrote all the matches from the respective round in the output file;
4. Using a data structure Match containing 2 teams that will play against each other I started storing 2 teams at a time;
5. I declared a string match_line that I used to display the matches between every 2 teams;
6. After storing the matches in the Match structure, i enqued them in a queue;
7. When the writing of the matches is finished, I made another while loop where I displayed all the winners of the round;
8. I divided the teams in 2 stacks: winners and losers, depending on the team points;
9. For the team points I used the calculateTeamPoints function where I made the average of all player points;
10. Using another string I displayed the winners of the respective round and erased the losers stack;
11. In the end, I made a copy of the last 8 teams remaining for the following tasks and i deleted and freed all the remaining variables;

-TASK IV-
1. For this task I created a BST tree using the createBSTTree function;
2. I wrote the team names in the output file using inorder traversal for diplaying them in a correct order: first the teams with the highest score followed by the others;
3. Lastly, I deleted the BST tree;

-TASK V-
1. I created an AVL tree which I populated by using AVL_insert function. This will take the teams from the savedTeams structure and order it in a AVL tree;
2. After creating the tree, I displayed the teams on the level 2 using printLevel function;
3. Finally, I deleted the AVL tree and in the end of the code I released the memory used and closed all the files.
