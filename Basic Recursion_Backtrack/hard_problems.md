### 1 N-Queen

```cpp
class Solution {
public:

    bool isSafe(int row, int col, vector<string>& board,int size){

        int duprow = row;
        int dupcol = col;

        // Vertical Checking
        while (row >= 0){
            if (board[row][col] == 'Q') return false;
            row--;
        }

        // Upper Left Diagonal
        row = duprow;
        col = dupcol;
        while (row >= 0 && col >= 0){
            if (board[row][col] == 'Q') return false;
            row--;
            col--;
        }

        // Upper Right Diagonal
        row = duprow;
        col = dupcol;
        while (row >= 0 && col < size){
            if (board[row][col] == 'Q') return false;
            row--;
            col++;
        }

        return true;
    }

    void putQueen(vector<vector<string>>& ans, vector<string>& board, int row, int size){

        if (row == size){
            ans.push_back(board);
            return;
        }

        for (int col = 0; col < size; col++){
            if (isSafe(row,col,board,size)){
                board[row][col]='Q';
                putQueen(ans,board,row+1,size);
                board[row][col]='.';        // backtrack
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<string> board(n);

        string s(n,'.');
        for (int i=0 ; i < n; i++){
            board[i] = s;
        }
//         board = [
//              "....",
//              "....",
//              "....",
//              "...."
//          ]


        putQueen(ans,board,0,n);

        return ans;
    }
};
```

### 2 Sudoku Solver

```cpp
class Solution {
public:
    bool isSafe(vector<vector<char>>& board, int row, int col,
                int numberToPut) {

        // check horizontally
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == '0' + numberToPut)
                return false;
        }

        // check vertically
        for (int i = 0; i < 9; i++) {
            if (board[i][col] == '0' + numberToPut)
                return false;
        }

        // check between 3 X 3
        int startCol = (col / 3) * 3;
        int startRow = (row / 3) * 3;
        for (int i = startRow; i < startRow + 3; i++) {
            for (int j = startCol; j < startCol + 3; j++) {
                if (board[i][j] == '0' + numberToPut) {
                    return false;
                }
            }
        }

        return true;
    }

    bool putNumberFromZeroToNine(vector<vector<char>>& board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    for (int num = 1; num < 10; num++) {
                        if (isSafe(board, i, j, num)) {
                            board[i][j] = '0' + num; // Place the number
                            // Recurse: try to solve the rest of the board
                            if (putNumberFromZeroToNine(board)) {
                                return true; // If successful, propagate true
                                             // upwards
                            } else {
                                // Backtrack: if this path didn't lead to a
                                // solution, undo the placement
                                board[i][j] = '.';
                            }
                        }
                    }
                    return false;
                }
            }
        }

        return true;
    }

    void solveSudoku(vector<vector<char>>& board) {
        putNumberFromZeroToNine(board);
    }
};
```


```cpp
// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>

using namespace std;

bool canGo(int row, int col, vector<vector<int>>& matrix) {
    int n = matrix.size();
    // Check boundaries and validity
    if (row < 0 || col < 0 || row >= n || col >= n) return false;
    if (matrix[row][col] == 0 || matrix[row][col] == -1) return false;
    
    return true;
}

void solveMaze(int row, int col, vector<vector<int>>& matrix, string& part, int size, vector<string>& ans){
    
    if (row == size-1 && col == size-1){
        ans.push_back(part);
        return;
    }
    
    // mark cell as visited
    matrix[row][col] = -1;
    
    // check down
    if (canGo(row+1,col,matrix)){
        part = part + "D";
        solveMaze(row+1,col,matrix,part,size,ans);
        part.pop_back();
    }
    
    // check up
    if (canGo(row-1,col,matrix)){
        part = part + "U";
        solveMaze(row-1,col,matrix,part,size,ans);
        part.pop_back();
    }
    
    // check left
    if(canGo(row,col-1,matrix)){
        part = part + "L";
        solveMaze(row,col-1,matrix,part,size,ans);
        part.pop_back();
    }
    
    // check right
    if(canGo(row,col+1,matrix)){
        part = part + "R";
        solveMaze(row,col+1,matrix,part,size,ans);
        part.pop_back();
    }
    
    // unmark
    matrix[row][col] = 1;
}

int main() {
    
    vector<vector<int>> matrix = {
        {1,0,0,0},
        {1,1,0,1},
        {1,1,0,0},
        {0,1,1,1}
    };
    vector<string> ans;
    string part= "";
    
    solveMaze(0,0,matrix,part,matrix.size(),ans);
    
    for (auto i : ans){
        cout << i << " ";
    }
    
    return 0;
}
```