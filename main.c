#include <stdio.h>
#include <string.h>
#include "crossword.h"

// Helper function to clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Helper function to get valid integer input
int getValidInt(int min, int max) {
    int value;
    int result;
    
    while (1) {
        result = scanf("%d", &value);
        
        if (result != 1) {
            // Invalid input (not a number)
            printf("Invalid input! Please enter a number: ");
            clearInputBuffer();
            continue;
        }
        
        if (value < min || value > max) {
            printf("Please enter a number between %d and %d: ", min, max);
            clearInputBuffer();
            continue;
        }
        
        clearInputBuffer();
        return value;
    }
}

int main() {
    char grid[GRID_SIZE][GRID_SIZE];
    Clue clues[MAX_CLUES];
    int clueCount = 0;
    ScoreNode *scoreTree = NULL;
    
    Player players[MAX_PLAYERS];
    int numPlayers;
    int choice;
    
    // Initialize
    initializeGrid(grid);
    
    printf("=================================\n");
    printf("   CROSSWORD PUZZLE GAME\n");
    printf("=================================\n");
    
    // Get number of players
    printf("\nEnter number of players (1-%d): ", MAX_PLAYERS);
    numPlayers = getValidInt(1, MAX_PLAYERS);
    
    // Get player names and initialize scores
    printf("\n");
    for (int i = 0; i < numPlayers; i++) {
        printf("Enter name for Player %d: ", i + 1);
        scanf("%s", players[i].name);
        players[i].score = 0;
        players[i].wordsCorrect = 0;
    }
    clearInputBuffer();
    
    printf("\n=== Players Registered ===\n");
    for (int i = 0; i < numPlayers; i++) {
        printf("%d. %s\n", i + 1, players[i].name);
    }
    
    // Pre-populate with some clues
    printf("\nSetting up crossword puzzle...\n");
    addClue(clues, &clueCount, "Capital of France", "PARIS", 0, 0, 'A', 1);
    placeWord(grid, "PARIS", 0, 0, 'A');
    
    addClue(clues, &clueCount, "Largest planet", "JUPITER", 2, 0, 'A', 2);
    placeWord(grid, "JUPITER", 2, 0, 'A');
    
    addClue(clues, &clueCount, "Man's best friend", "DOG", 4, 2, 'A', 3);
    placeWord(grid, "DOG", 4, 2, 'A');
    
    addClue(clues, &clueCount, "Frozen water", "ICE", 0, 0, 'D', 4);
    placeWord(grid, "ICE", 0, 0, 'D');
    
    addClue(clues, &clueCount, "Red fruit", "APPLE", 0, 2, 'D', 5);
    placeWord(grid, "APPLE", 0, 2, 'D');
    
    addClue(clues, &clueCount, "Programming language with a snake", "PYTHON", 6, 0, 'A', 6);
    placeWord(grid, "PYTHON", 6, 0, 'A');
    
    addClue(clues, &clueCount, "Opposite of day", "NIGHT", 8, 1, 'A', 7);
    placeWord(grid, "NIGHT", 8, 1, 'A');
    
    addClue(clues, &clueCount, "Color of the sky", "BLUE", 0, 4, 'D', 8);
    placeWord(grid, "BLUE", 0, 4, 'D');
    
    addClue(clues, &clueCount, "Hot beverage", "TEA", 2, 6, 'D', 9);
    placeWord(grid, "TEA", 2, 6, 'D');
    
    addClue(clues, &clueCount, "King of the jungle", "LION", 5, 6, 'A', 10);
    placeWord(grid, "LION", 5, 6, 'A');
    
    printf("Crossword ready!\n");
    
    do {
        printf("\n=================================\n");
        printf("1. Display Grid\n");
        printf("2. Display Clues\n");
        printf("3. Answer a Clue\n");
        printf("4. View Current Scores\n");
        printf("5. View Leaderboard\n");
        printf("6. Delete a Clue (Admin)\n");
        printf("7. Save and Exit\n");
        printf("=================================\n");
        printf("Enter choice: ");
        choice = getValidInt(1, 7);
        
        switch(choice) {
            case 1:
                displayGrid(grid);
                break;
                
            case 2:
                displayClues(clues, clueCount);
                break;
                
            case 3: {
                int clueNum;
                char answer[MAX_WORD_LENGTH];
                int playerChoice;
                
                displayClues(clues, clueCount);
                printf("\nEnter clue number to answer: ");
                clueNum = getValidInt(1, 100);
                
                int found = -1;
                for (int i = 0; i < clueCount; i++) {
                    if (clues[i].number == clueNum) {
                        found = i;
                        break;
                    }
                }
                
                if (found == -1) {
                    printf("Invalid clue number!\n");
                } else if (clues[found].solved) {
                    printf("This clue is already solved!\n");
                } else {
                    // Show players and let them choose who's answering
                    printf("\n=== Who is answering? ===\n");
                    for (int i = 0; i < numPlayers; i++) {
                        printf("%d. %s (Score: %d, Words: %d)\n", 
                               i + 1, players[i].name, players[i].score, players[i].wordsCorrect);
                    }
                    printf("Enter player number (1-%d): ", numPlayers);
                    playerChoice = getValidInt(1, numPlayers);
                    
                    playerChoice--; // Convert to 0-indexed
                    
                    printf("\n%s, enter your answer: ", players[playerChoice].name);
                    scanf("%s", answer);
                    clearInputBuffer();
                    
                    if (checkAnswer(grid, &clues[found], answer)) {
                        printf("\n*** CORRECT! Well done, %s! ***\n", players[playerChoice].name);
                        players[playerChoice].score += 10;
                        players[playerChoice].wordsCorrect++;
                    } else {
                        printf("\n*** WRONG! Better luck next time, %s. ***\n", 
                               players[playerChoice].name);
                        players[playerChoice].score -= 2;
                    }
                }
                break;
            }
                
            case 4:
                printf("\n=== CURRENT SCORES ===\n");
                for (int i = 0; i < numPlayers; i++) {
                    printf("Player: %-15s | Score: %4d | Words Correct: %d\n", 
                           players[i].name, players[i].score, players[i].wordsCorrect);
                }
                printf("=================================\n");
                break;
            
            case 5: {
                // Build temporary BST for current leaderboard
                ScoreNode *tempTree = NULL;
                for (int i = 0; i < numPlayers; i++) {
                    tempTree = insertScore(tempTree, players[i].name, 
                                          players[i].score, 
                                          players[i].wordsCorrect);
                }
                
                printf("\n=================================================\n");
                printf("              LEADERBOARD                        \n");
                printf("=================================================\n");
                if (tempTree == NULL) {
                    printf("No scores recorded yet!\n");
                } else {
                    reverseInorderTraversal(tempTree);
                }
                printf("=================================================\n");
                break;
            }
            
            case 6: {
                int clueNum;
                displayClues(clues, clueCount);
                printf("Enter clue number to delete: ");
                clueNum = getValidInt(1, 100);
                deleteClue(clues, &clueCount, clueNum);
                break;
            }
                
            case 7:
                // Save all final scores to BST
                printf("\nSaving final scores...\n");
                for (int i = 0; i < numPlayers; i++) {
                    scoreTree = insertScore(scoreTree, players[i].name, 
                                           players[i].score, 
                                           players[i].wordsCorrect);
                }
                
                printf("\n=================================================\n");
                printf("              FINAL LEADERBOARD                  \n");
                printf("=================================================\n");
                reverseInorderTraversal(scoreTree);
                printf("=================================================\n");
                printf("\nThank you for playing!\n");
                break;
                
            default:
                printf("Invalid choice!\n");
        }
        
    } while(choice != 7);
    
    return 0;
}