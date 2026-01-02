#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "crossword.h"

// Initialize grid with empty spaces and black squares
void initializeGrid(char grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = '.'; // Black square (no letter)
        }
    }
}

// Display the crossword grid
void displayGrid(char grid[GRID_SIZE][GRID_SIZE]) {
    printf("\n   ");
    for (int i = 0; i < GRID_SIZE; i++) {
        printf("%2d ", i);
    }
    printf("\n");
    
    for (int i = 0; i < GRID_SIZE; i++) {
        printf("%2d ", i);
        for (int j = 0; j < GRID_SIZE; j++) {
            printf(" %c ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Place a word on the grid
void placeWord(char grid[GRID_SIZE][GRID_SIZE], char *word, int row, int col, char direction) {
    int len = strlen(word);
    if (direction == 'A') { // Across
        for (int i = 0; i < len; i++) {
            grid[row][col + i] = '_'; // Placeholder for empty answer
        }
    } else { // Down
        for (int i = 0; i < len; i++) {
            grid[row + i][col] = '_';
        }
    }
}

// Add a clue to the array (Linear structure)
void addClue(Clue clues[], int *clueCount, char *clueText, char *answer, int row, int col, char direction, int number) {
    if (*clueCount >= MAX_CLUES) {
        printf("Maximum clues reached!\n");
        return;
    }
    
    strcpy(clues[*clueCount].clue, clueText);
    strcpy(clues[*clueCount].answer, answer);
    clues[*clueCount].row = row;
    clues[*clueCount].col = col;
    clues[*clueCount].direction = direction;
    clues[*clueCount].number = number;
    clues[*clueCount].solved = 0;
    (*clueCount)++;
}

// Display all clues
void displayClues(Clue clues[], int clueCount) {
    printf("\n=== ACROSS ===\n");
    for (int i = 0; i < clueCount; i++) {
        if (clues[i].direction == 'A') {
            printf("%d. %s %s\n", clues[i].number, clues[i].clue, 
                   clues[i].solved ? "[SOLVED]" : "");
        }
    }
    
    printf("\n=== DOWN ===\n");
    for (int i = 0; i < clueCount; i++) {
        if (clues[i].direction == 'D') {
            printf("%d. %s %s\n", clues[i].number, clues[i].clue,
                   clues[i].solved ? "[SOLVED]" : "");
        }
    }
    printf("\n");
}

// Delete a clue from array
void deleteClue(Clue clues[], int *clueCount, int clueNumber) {
    int found = -1;
    for (int i = 0; i < *clueCount; i++) {
        if (clues[i].number == clueNumber) {
            found = i;
            break;
        }
    }
    
    if (found == -1) {
        printf("Clue number %d not found!\n", clueNumber);
        return;
    }
    
    // Shift elements left
    for (int i = found; i < *clueCount - 1; i++) {
        clues[i] = clues[i + 1];
    }
    (*clueCount)--;
    printf("Clue %d deleted successfully!\n", clueNumber);
}

// Check if user's answer is correct
int checkAnswer(char grid[GRID_SIZE][GRID_SIZE], Clue *clue, char *userAnswer) {
    // Convert both to uppercase for comparison
    char upperAnswer[MAX_WORD_LENGTH];
    char upperUser[MAX_WORD_LENGTH];
    
    strcpy(upperAnswer, clue->answer);
    strcpy(upperUser, userAnswer);
    
    for (int i = 0; upperAnswer[i]; i++) {
        upperAnswer[i] = toupper(upperAnswer[i]);
    }
    for (int i = 0; upperUser[i]; i++) {
        upperUser[i] = toupper(upperUser[i]);
    }
    
    if (strcmp(upperAnswer, upperUser) == 0) {
        clue->solved = 1;
        fillAnswer(grid, clue);
        return 1;
    }
    return 0;
}

// Fill the correct answer on the grid
void fillAnswer(char grid[GRID_SIZE][GRID_SIZE], Clue *clue) {
    int len = strlen(clue->answer);
    if (clue->direction == 'A') {
        for (int i = 0; i < len; i++) {
            grid[clue->row][clue->col + i] = toupper(clue->answer[i]);
        }
    } else {
        for (int i = 0; i < len; i++) {
            grid[clue->row + i][clue->col] = toupper(clue->answer[i]);
        }
    }
}

// Create a new score node (BST)
ScoreNode* createScoreNode(char *playerName, int score, int wordsCorrect) {
    ScoreNode *newNode = (ScoreNode*)malloc(sizeof(ScoreNode));
    strcpy(newNode->playerName, playerName);
    newNode->score = score;
    newNode->wordsCorrect = wordsCorrect;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Insert score into BST (sorted by score)
ScoreNode* insertScore(ScoreNode *root, char *playerName, int score, int wordsCorrect) {
    if (root == NULL) {
        return createScoreNode(playerName, score, wordsCorrect);
    }
    
    if (score < root->score) {
        root->left = insertScore(root->left, playerName, score, wordsCorrect);
    } else {
        root->right = insertScore(root->right, playerName, score, wordsCorrect);
    }
    
    return root;
}

// Display score of a node
void displayScore(ScoreNode *node) {
    if (node != NULL) {
        printf("Player: %-15s | Score: %4d | Words Correct: %d\n", 
               node->playerName, node->score, node->wordsCorrect);
    }
}

// Delete score from BST
ScoreNode* deleteScore(ScoreNode *root, char *playerName) {
    if (root == NULL) {
        return NULL;
    }
    
    int cmp = strcmp(playerName, root->playerName);
    
    if (cmp < 0) {
        root->left = deleteScore(root->left, playerName);
    } else if (cmp > 0) {
        root->right = deleteScore(root->right, playerName);
    } else {
        // Node found
        if (root->left == NULL) {
            ScoreNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            ScoreNode *temp = root->left;
            free(root);
            return temp;
        }
        
        // Node with two children - find minimum in right subtree
        ScoreNode *temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        
        strcpy(root->playerName, temp->playerName);
        root->score = temp->score;
        root->wordsCorrect = temp->wordsCorrect;
        root->right = deleteScore(root->right, temp->playerName);
    }
    
    return root;
}

// Inorder traversal to display all scores (ascending order)
void inorderTraversal(ScoreNode *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        displayScore(root);
        inorderTraversal(root->right);
    }
}

// Reverse inorder traversal for leaderboard (highest to lowest)
void reverseInorderTraversal(ScoreNode *root) {
    if (root != NULL) {
        reverseInorderTraversal(root->right);  // Visit right first
        displayScore(root);
        reverseInorderTraversal(root->left);   // Then left
    }
}