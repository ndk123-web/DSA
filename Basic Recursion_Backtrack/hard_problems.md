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

        putQueen(ans,board,0,n);

        return ans;
    }
};
```
