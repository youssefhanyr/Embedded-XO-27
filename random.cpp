#include <iostream>
#include <vector>
#include <random>
#include <ctime>

class RandomAI {
private:
    short PLAYER = 0; // 0 will be the default for 'O', 1 for 'X'
    std::mt19937 rng;

public:
    RandomAI() {
        rng.seed(std::time(nullptr)); // Seed the random number generator
    }

    short getmove(const short board[][3]) {
        // Collect all available moves
        std::vector<short> available_moves;
        for (short i = 0; i < 9; i++) {
            if (board[i/3][i%3] == -1) {
                available_moves.push_back(i);
            }
        }

        // If no moves are available, return -1
        if (available_moves.empty()) {
            return -1;
        }

        // Generate a random index
        std::uniform_int_distribution<short> dist(0, available_moves.size() - 1);
        short random_index = dist(rng);

        // Return the randomly selected move
        return available_moves[random_index];
    }
};

void printTicTacToeBoard(const short board[][3]) {
    std::cout << "\n";
    for (int i = 0; i < 3; i++) {
        std::cout << " ";
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 1) {
                std::cout << "X";
            } else if (board[i][j] == 0) {
                std::cout << "O";
            } else {
                std::cout << " ";
            }
            
            if (j < 2) {
                std::cout << " | ";
            }
        }
        std::cout << "\n";
        
        if (i < 2) {
            std::cout << "-----------\n";
        }
    }
    std::cout << "\n";
}

// Test function to verify Random AI moves
void testRandomAIScenario(const char* scenarioName, short board[][3]) {
    std::cout << "\n=== Testing Random AI scenario: " << scenarioName << " ===\n";
    std::cout << "Initial board state:";
    printTicTacToeBoard(board);
    
    RandomAI randomAI;
    int move = randomAI.getmove(board);
    
    std::cout << "Random AI chose position: " << move << " (row: " << move/3 << ", col: " << move%3 << ")\n";
    
    // Show the move on the board
    if (move != -1) {
        board[move/3][move%3] = 0;
        std::cout << "Board after Random AI move:";
        printTicTacToeBoard(board);
    } else {
        std::cout << "No valid moves available!\n";
    }
    std::cout << "================================\n";
}

int main() {
    // Test Random AI with different scenarios
    short board1[][3] = {
        {1, -1, -1},
        {1, 1, -1},
        {0, -1, -1}
    };
    testRandomAIScenario("Random move from multiple options", board1);

    short board2[][3] = {
        {0, 1, 1},
        {-1, 0, -1},
        {-1, -1, -1}
    };
    testRandomAIScenario("Random move from multiple options", board2);

    short board3[][3] = {
        {-1, -1, -1},
        {-1, -1, -1},
        {-1, -1, -1}
    };
    testRandomAIScenario("Random move from empty board", board3);

    // Test with almost full board
    short board4[][3] = {
        {1, 0, 1},
        {0, 1, 0},
        {1, 0, -1}
    };
    testRandomAIScenario("Random move from almost full board", board4);

    // Test with full board
    short board5[][3] = {
        {1, 0, 1},
        {0, 1, 0},
        {1, 0, 1}
    };
    testRandomAIScenario("Full board - no moves available", board5);

    return 0;
}
