#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *strrev(char *word) {
    char *word_start = word;
    int start = 0, end = strlen(word) - 1;
    while (start <= end) {
        char c = word[start];
        word[start] = word[end];
        word[end] = c;
        start++;
        end--;
    }
    return word_start;
}

bool dfs(char **board, int i, int r, int c, char *word, int ROWS, int COLS) {
    if (i == strlen(word)) {
        return true;
    }
    if (r < 0 || c < 0 || r >= ROWS || c >= COLS || board[r][c] == '#' || board[r][c] != word[i]) {
        return false;
    }

    board[r][c] = '#'; // Mark the cell as visited
    bool res = dfs(board, i + 1, r + 1, c, word, ROWS, COLS) ||
               dfs(board, i + 1, r - 1, c, word, ROWS, COLS) ||
               dfs(board, i + 1, r, c + 1, word, ROWS, COLS) ||
               dfs(board, i + 1, r, c - 1, word, ROWS, COLS);
    board[r][c] = word[i]; // Unmark the cell
    return res;
}

bool exist(char **board, int boardSize, int *boardColSize, char *word) {
    int ROWS = boardSize;
    int COLS = *boardColSize;
    if (strlen(word) > ROWS * COLS) {
        return false;
    }
    
    int boardCharFrequency[26] = {0};
    int wordCharFrequency[26] = {0};
    
    // Count character frequencies in the board
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (board[r][c] >= 'a' && board[r][c] <= 'z') {
                boardCharFrequency[board[r][c] - 'a']++;
            } else {
                boardCharFrequency[board[r][c] - 'A']++;
            }
        }
    }

    // Count character frequencies in the word
    for (int i = 0; i < strlen(word); i++) {
        if (word[i] >= 'a' && word[i] <= 'z') {
            wordCharFrequency[word[i] - 'a']++;
        } else {
            wordCharFrequency[word[i] - 'A']++;
        }
    }

    // Check if the frequencies match
    for (int i = 0; i < 26; i++) {
        if (boardCharFrequency[i] != wordCharFrequency[i]) {
            return false;
        }
    }

    // Reverse the word if necessary
    int left = 0, right = 0;
    for (int i = 0; i < strlen(word) - 1; i++) {
        if (word[i] == word[i + 1]) {
            left++;
        } else {
            break;
        }
    }
    for (int i = strlen(word) - 1; i >= 1; i--) {
        if (word[i] == word[i - 1]) {
            right++;
        } else {
            break;
        }
    }
    if (left > right) {
        word = strrev(word);
    }

    // Search for the word in the board
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (dfs(board, 0, r, c, word, ROWS, COLS)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    // Example 1
    char *board1[] = { "ABCE", "SFCS", "ADEE" };
    char *word1 = "ABCCED";
    int boardSize1 = 3;
    int boardColSize1 = 4;
    printf("Input: board = [[\"A\",\"B\",\"C\",\"E\"],[\"S\",\"F\",\"C\",\"S\"],[\"A\",\"D\",\"E\",\"E\"]], word = \"%s\"\n", word1);
    printf("Output: %s\n", exist(board1, boardSize1, &boardColSize1, word1) ? "true" : "false");

    // Example 2
    char *board2[] = { "ABCE", "SFCS", "ADEE" };
    char *word2 = "SEE";
    int boardSize2 = 3;
    int boardColSize2 = 4;
    printf("Input: board = [[\"A\",\"B\",\"C\",\"E\"],[\"S\",\"F\",\"C\",\"S\"],[\"A\",\"D\",\"E\",\"E\"]], word = \"%s\"\n", word2);
    printf("Output: %s\n", exist(board2, boardSize2, &boardColSize2, word2) ? "true" : "false");

    // Example 3
    char *board3[] = { "ABCE", "SFCS", "ADEE" };
    char *word3 = "ABCB";
    int boardSize3 = 3;
    int boardColSize3 = 4;
    printf("Input: board = [[\"A\",\"B\",\"C\",\"E\"],[\"S\",\"F\",\"C\",\"S\"],[\"A\",\"D\",\"E\",\"E\"]], word = \"%s\"\n", word3);
    printf("Output: %s\n", exist(board3, boardSize3, &boardColSize3, word3) ? "true" : "false");

    return 0;
}
