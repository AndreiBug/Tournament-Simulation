# LanParty

A program simulating a gaming tournament between teams. The tasks are structured step-by-step for clarity and efficiency.

---

## **Task I: Initial Setup**
1. Opened the input files and declared all necessary variables for processing.
2. Read the number of teams and iteratively processed team data:
   - Each team has a name and a list of players with their names and points.
3. Created a function to remove trailing spaces or newline characters from team names.
4. Added each new team to the beginning of the list for easier manipulation.
5. Stored references to the start of the team list and player list for future use.

---

## **Task II: Eliminating Teams**
1. Implemented a while loop to reduce the number of teams to the nearest power of 2:
   - Used the `delete_team_with_min_points` function to remove the lowest-scoring teams.
2. Updated the team count after every iteration.
3. Created a `ShowTeams` function to display the remaining team names in the output file.

---

## **Task III: Tournament Rounds**
1. Declared additional variables to manage the tournament rounds.
2. Used a while loop to continue until only one team remained, declaring it the winner.
3. For each round:
   - Wrote matchups to the output file.
   - Created a `Match` structure to pair two competing teams.
   - Displayed match details using a `match_line` string.
   - Enqueued matches into a queue for further processing.
4. Determined winners and losers:
   - Winners and losers were stored in separate stacks.
   - Used the `calculateTeamPoints` function to determine team scores based on the average player points.
5. Displayed the winners of each round and removed the losers.
6. Saved the last 8 teams for subsequent tasks, then cleaned up memory and resources.

---

## **Task IV: Binary Search Tree (BST)**
1. Built a BST using the `createBSTTree` function:
   - Teams were ordered by their scores.
2. Used an in-order traversal to write team names to the output file in descending order of scores.
3. Deleted the BST to free resources after processing.

---

## **Task V: AVL Tree**
1. Constructed an AVL tree using the `AVL_insert` function:
   - Populated the tree with the top 8 teams from the saved list.
2. Displayed teams at level 2 of the AVL tree using the `printLevel` function.
3. Deleted the AVL tree and released all allocated memory, closing files as the program concluded.

---

## **Highlights**
- **Efficient Algorithms**: Leveraged data structures like stacks, queues, BST, and AVL trees for optimal performance.
- **Clear Workflow**: Tasks are modularized for better readability and maintenance.
- **Dynamic Output**: Real-time display of matches, winners, and team rankings.

This program effectively simulates a gaming tournament, handling complex operations with well-structured and reusable components.
