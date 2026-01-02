# Crossword Puzzle Game

## Overview

This is an interactive **Crossword Puzzle Game** built in C that combines classic crossword gameplay with score tracking and leaderboard management. The application is designed as a Data Structures and Algorithms (DSA) mini-project that demonstrates the use of both linear data structures (arrays) and non-linear data structures (Binary Search Trees).

## Features

### 🎮 Game Features

- **Interactive Crossword Grid** - A 10×10 puzzle grid with pre-populated clues
- **Clue System** - Both "Across" and "Down" clues organized separately
- **Multi-Player Support** - Play with up to 10 players simultaneously
- **Real-Time Answer Checking** - Verify answers as you go
- **Score Tracking** - Automatic score calculation based on correct answers
- **Leaderboard System** - View top players ranked by score

### 📊 Data Structure Implementation

- **Linear Structure (Array)** - Stores crossword clues with fast sequential access
- **Non-Linear Structure (Binary Search Tree)** - Manages player scores with efficient sorting and retrieval
- **Optimized Operations** - Insert, delete, and search operations on player data

## Technical Specifications

### Grid Specifications

- **Size**: 10×10 grid
- **Max Clues**: 20
- **Max Players**: 10
- **Max Word Length**: 15 characters

### Project Structure

```
CODE/
├── crossword.h       # Header file with data structures and function declarations
├── crossword.c       # Implementation of all game logic and DSA operations
├── main.c           # Main game loop and user interface
└── README.md        # Project documentation (this file)
```

## Data Structures

### 1. Clue Structure (Linear - Array)

```c
typedef struct {
    char clue[MAX_CLUE_LENGTH];      // The clue text
    char answer[MAX_WORD_LENGTH];    // Correct answer
    int row;                          // Grid row position
    int col;                          // Grid column position
    char direction;                   // 'A' (Across) or 'D' (Down)
    int number;                       // Clue number
    int solved;                       // Status (0=unsolved, 1=solved)
} Clue;
```

### 2. Player Structure

```c
typedef struct {
    char name[50];                   // Player name
    int score;                       // Total score
    int wordsCorrect;                // Number of correct words
} Player;
```

### 3. Score Node Structure (Non-Linear - BST)

```c
typedef struct ScoreNode {
    int score;                       // Player score
    int wordsCorrect;                // Words solved
    char playerName[50];             // Player name
    struct ScoreNode *left;          // Left child
    struct ScoreNode *right;         // Right child
} ScoreNode;
```

## Core Functions

### Grid Management

| Function           | Purpose                                                       |
| ------------------ | ------------------------------------------------------------- |
| `initializeGrid()` | Initializes a 10×10 grid with empty cells                     |
| `displayGrid()`    | Displays the current state of the grid                        |
| `placeWord()`      | Places a word on the grid at specified position and direction |

### Clue Management (Linear - Array)

| Function         | Purpose                                              |
| ---------------- | ---------------------------------------------------- |
| `addClue()`      | Adds a new clue to the array                         |
| `displayClues()` | Shows all clues organized by direction (Across/Down) |
| `deleteClue()`   | Removes a clue from the array                        |

### Player & Game Logic

| Function        | Purpose                                          |
| --------------- | ------------------------------------------------ |
| `checkAnswer()` | Validates player's answer against correct answer |
| `fillAnswer()`  | Fills correct answer on the grid                 |

### Score Management (Non-Linear - BST)

| Function                    | Purpose                                         |
| --------------------------- | ----------------------------------------------- |
| `createScoreNode()`         | Creates a new BST node for a player             |
| `insertScore()`             | Inserts player score into BST                   |
| `deleteScore()`             | Removes player from leaderboard                 |
| `inorderTraversal()`        | Displays scores in ascending order              |
| `reverseInorderTraversal()` | Displays leaderboard (highest to lowest scores) |

## How to Compile and Run

### Prerequisites

- GCC or any standard C compiler
- Windows, Linux, or macOS

### Compilation

```bash
gcc -o crossword_game main.c crossword.c
```

### Running the Game

```bash
./crossword_game
```

### Windows

```bash
gcc -o crossword_game.exe main.c crossword.c
crossword_game.exe
```

## Game Flow

1. **Player Setup**

   - Enter the number of players (1-10)
   - Each player enters their name

2. **Puzzle Display**

   - Grid and clues are displayed
   - Players take turns solving clues

3. **Answer Entry**

   - Select a clue number
   - Enter your answer
   - Automatic verification and scoring

4. **Leaderboard**

   - View real-time scores
   - Check ranking after each correct answer
   - See top performers

5. **Game End**
   - Display final leaderboard
   - Announce the winner

## Pre-Populated Clues

The game comes with 9 pre-loaded clues:

- **1 Across**: Capital of France → PARIS
- **2 Across**: Largest planet → JUPITER
- **3 Across**: Man's best friend → DOG
- **6 Across**: Programming language with a snake → PYTHON
- **7 Across**: Opposite of day → NIGHT
- **4 Down**: Frozen water → ICE
- **5 Down**: Red fruit → APPLE
- **8 Down**: Color of the sky → BLUE
- **9 Down**: Hot beverage → TEA

## DSA Concepts Demonstrated

### Linear Data Structures

- **Array for Clues**: O(n) search, O(1) access by index, dynamic insertion/deletion
- Sequential storage and retrieval of puzzle clues
- Dynamic resizing capabilities

### Non-Linear Data Structures

- **Binary Search Tree for Scores**: O(log n) average search/insert/delete
- Automatic sorting of player scores
- Efficient range queries and leaderboard generation
- In-order and reverse in-order traversals for sorted output

## Input Validation

- Numbers within valid ranges
- Player count between 1-10
- String inputs with proper bounds checking
- Automatic input buffer clearing

## Future Enhancements

- Multiple difficulty levels
- Hint system
- Time-based scoring
- File-based puzzle persistence
- Graphical user interface
- Network multiplayer mode
- Custom puzzle creation
