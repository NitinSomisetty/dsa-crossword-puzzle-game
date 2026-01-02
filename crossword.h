#ifndef CROSSWORD_H
#define CROSSWORD_H

#define GRID_SIZE 10
#define MAX_CLUES 20
#define MAX_CLUE_LENGTH 100
#define MAX_WORD_LENGTH 15
#define MAX_PLAYERS 10

// Structure for a clue
typedef struct {
    char clue[MAX_CLUE_LENGTH];
    char answer[MAX_WORD_LENGTH];
    int row;
    int col;
    char direction; // 'A' for across, 'D' for down
    int number;
    int solved;
} Clue;

// Structure for a player
typedef struct {
    char name[50];
    int score;
    int wordsCorrect;
} Player;

// Structure for player score (BST node)
typedef struct ScoreNode {
    int score;
    int wordsCorrect;
    char playerName[50];
    struct ScoreNode *left;
    struct ScoreNode *right;
} ScoreNode;

// Grid functions
void initializeGrid(char grid[GRID_SIZE][GRID_SIZE]);
void displayGrid(char grid[GRID_SIZE][GRID_SIZE]);
void placeWord(char grid[GRID_SIZE][GRID_SIZE], char *word, int row, int col, char direction);

// Clue functions (Linear - Array)
void addClue(Clue clues[], int *clueCount, char *clueText, char *answer, int row, int col, char direction, int number);
void displayClues(Clue clues[], int clueCount);
void deleteClue(Clue clues[], int *clueCount, int clueNumber);

// Player interaction
int checkAnswer(char grid[GRID_SIZE][GRID_SIZE], Clue *clue, char *userAnswer);
void fillAnswer(char grid[GRID_SIZE][GRID_SIZE], Clue *clue);

// Score functions (Non-linear - BST)
ScoreNode* createScoreNode(char *playerName, int score, int wordsCorrect);
ScoreNode* insertScore(ScoreNode *root, char *playerName, int score, int wordsCorrect);
void displayScore(ScoreNode *node);
ScoreNode* deleteScore(ScoreNode *root, char *playerName);
void inorderTraversal(ScoreNode *root);
void reverseInorderTraversal(ScoreNode *root);  // For leaderboard (highest to lowest)

#endif