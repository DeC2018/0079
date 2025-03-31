#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Function to reverse a string
char *strrev(char *word){
    char *word_start = word;
    int start = 0, end = strlen(word) - 1;
    while(start <= end){
        char c = word[start];
        word[start] = word[end];
        word[end] = c;
        start++;
        end--;
    }
    return word_start;
}

// Function to perform DFS
bool dfs(char **board, int i, int r, int c, char *word, int ROWS, int COLS){
    if(i == strlen(word)){
        return true;
    }
    if(r < 0 || c < 0 || r >= ROWS || c >= COLS || board[r][c] == '#' || board[r][c] != word[i]){
        return false;
    }

    board[r][c] = '#';
    bool res = dfs(board, i+1, r + 1, c, word, ROWS, COLS) ||
                dfs(board, i+1, r - 1, c, word, ROWS, COLS) ||
                dfs(board, i+1, r, c + 1, word, ROWS, COLS) ||
                dfs(board, i+1, r, c-1, word, ROWS, COLS);
    board[r][c] = word[i];
    return res;
}

// Function to check if a word exists in a board
bool exist(char** board, int boardSize, int* boardColSize, char* word) {
    int ROWS = boardSize;
    int COLS = *boardColSize;
    if(strlen(word) > ROWS*COLS){
        return false;
    }
    int boardCharFrequency[26] = {0};
    int wordCharFrequency[26] = {0};
    for(int r = 0; r < ROWS; r++){
        for(int c = 0; c < COLS; c++){
            if(board[r][c] >= 'a' && board[r][c] <= 'z'){
                boardCharFrequency[board[r][c] - 'a']++;
            }else{
                boardCharFrequency[board[r][c] - 'A']++;
            }
            
        }
    }
    for(int i = 0; i < strlen(word); i++){
        if(word[i] >= 'a' && word[i] <= 'z'){
            wordCharFrequency[word[i] - 'a']++;
        }else{
            wordCharFrequency[word[i] - 'A']++;
        }
    }

    for(int i = 0; i < 26; i++){
        if(boardCharFrequency[i] < wordCharFrequency[i]){
            return false;
        }
    }

    int left = 0, right = 0;
    for(int i = 0; i < strlen(word)-1; i++){
        if(word[i] == word[i+1]){
            left++;
        }else{
            break;
        }
    }
    for(int i = strlen(word) - 1; i >=1; i--){
        if(word[i] == word[i-1]){
            right++;
        }else{
            break;
        }
    }
    if(left>right){
        word = strrev(word);
    }
    for(int r = 0; r < ROWS; r++){
        for(int c = 0; c < COLS; c++){
            if(dfs(board, 0, r, c, word, ROWS, COLS)){
                return true;
            }
        }
    }
    return false;
    
}

int main() {
    char **board = (char **)malloc(3 * sizeof(char *));
    for(int i = 0; i < 3; i++) {
        board[i] = (char *)malloc(4 * sizeof(char));
    }
    board[0][0] = 'A'; board[0][1] = 'B'; board[0][2] = 'C'; board[0][3] = 'E';
    board[1][0] = 'S'; board[1][1] = 'F'; board[1][2] = 'C'; board[1][3] = 'S';
    board[2][0] = 'A'; board[2][1] = 'D'; board[2][2] = 'E'; board[2][3] = 'E';

    int boardSize = 3;
    int boardColSize = 4;

    printf("Input: board = [");
    for(int i = 0; i < boardSize; i++) {
        printf("[");
        for(int j = 0; j < boardColSize; j++) {
            printf("\"%c\"", board[i][j]);
            if(j < boardColSize - 1) {
                printf(",");
            }
        }
        printf("]");
        if(i < boardSize - 1) {
            printf(", ");
        }
    }
    printf("], ");

    char *word = "ABCCED";
    printf("word = \"%s\"\n", word);
    printf("Output: %s\n", exist(board, boardSize, &boardColSize, word) ? "true" : "false");

    printf("Input: board = [");
    for(int i = 0; i < boardSize; i++) {
        printf("[");
        for(int j = 0; j < boardColSize; j++) {
            printf("\"%c\"", board[i][j]);
            if(j < boardColSize - 1) {
                printf(",");
            }
        }
        printf("]");
        if(i < boardSize - 1) {
            printf(", ");
        }
    }
    printf("], ");
    char *word2 = "SEE";
    printf("word = \"%s\"\n", word2);
    printf("Output: %s\n", exist(board, boardSize, &boardColSize, word2) ? "true" : "false");

    printf("Input: board = [");
    for(int i = 0; i < boardSize; i++) {
        printf("[");
        for(int j = 0; j < boardColSize; j++) {
            printf("\"%c\"", board[i][j]);
            if(j < boardColSize - 1) {
                printf(",");
            }
        }
        printf("]");
        if(i < boardSize - 1) {
            printf(", ");
        }
    }
    printf("], ");
    char *word3 = "ABCB";
    printf("word = \"%s\"\n", word3);
    printf("Output: %s\n", exist(board, boardSize, &boardColSize, word3) ? "true" : "false");

    // Deallocate memory
    for(int i = 0; i < 3; i++) {
        free(board[i]);
    }
    free(board);

    return 0;
}
