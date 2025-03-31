#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size(); // Number of rows
        int m = board[0].size(); // Number of columns
        vector<vector<bool>> visited(n, vector<bool>(m, false)); // Visited cells tracker

        // Iterate through each cell in the board
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // Start searching for the word from this cell
                if (visit(board, word, 0, i, j, n, m, visited)) {
                    return true;
                }
            }
        }
        return false; // If the word is not found, return false
    }

private:
    bool visit(vector<vector<char>>& board, const string& word, int index, int x, int y,
               int n, int m, vector<vector<bool>>& visited) {
        // Base case: If all characters in the word are found
        if (index == word.size()) {
            return true;
        }

        // Check for out-of-bounds, already visited cells, or character mismatch
        if (x < 0 || x >= n || y < 0 || y >= m || visited[x][y] || board[x][y] != word[index]) {
            return false;
        }

        visited[x][y] = true; // Mark the current cell as visited

        // Recursively search in all four directions
        bool found = visit(board, word, index + 1, x + 1, y, n, m, visited) ||
                     visit(board, word, index + 1, x - 1, y, n, m, visited) ||
                     visit(board, word, index + 1, x, y + 1, n, m, visited) ||
                     visit(board, word, index + 1, x, y - 1, n, m, visited);

        visited[x][y] = false; // Backtrack: Unmark the current cell

        return found; // Return whether the word was found
    }
};

int main() {
    Solution solution;

    vector<vector<char>> board1 = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    string word1 = "ABCCED";
    cout << "Input: board = [[\"A\",\"B\",\"C\",\"E\"],[\"S\",\"F\",\"C\",\"S\"],[\"A\",\"D\",\"E\",\"E\"]], word = \"" << word1 << "\"" << endl;
    cout << "Output: " << (solution.exist(board1, word1) ? "true" : "false") << endl;

    vector<vector<char>> board2 = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    string word2 = "SEE";
    cout << "Input: board = [[\"A\",\"B\",\"C\",\"E\"],[\"S\",\"F\",\"C\",\"S\"],[\"A\",\"D\",\"E\",\"E\"]], word = \"" << word2 << "\"" << endl;
    cout << "Output: " << (solution.exist(board2, word2) ? "true" : "false") << endl;

    vector<vector<char>> board3 = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    string word3 = "ABCB";
    cout << "Input: board = [[\"A\",\"B\",\"C\",\"E\"],[\"S\",\"F\",\"C\",\"S\"],[\"A\",\"D\",\"E\",\"E\"]], word = \"" << word3 << "\"" << endl;
    cout << "Output: " << (solution.exist(board3, word3) ? "true" : "false") << endl;

    return 0;
}
