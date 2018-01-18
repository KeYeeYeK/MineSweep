#include <iostream>
#include <string>
#include <vector>
using namespace std;

class mineSweep{
private:
  vector<vector<char>> board;
  vector<vector<char>> play_board;
  int mines;
  int row;
  int column;

public:
  mineSweep(int level){
    if(level == 0){
      row = 8; column = 8;
      mines = 10;
    }
    else if(level == 1){
      row = 16; column = 16;
      mines = 40;
    }
    else if(level == 2){
      row = 24; column = 24;
      mines = 99;
    }
    board = vector<vector<char>>(row, vector<char>(column, 'E'));
    play_board = board;
    int count = 0;
    srand (time(NULL));
    while(count < mines){
      int x = rand() % row;
      int y = rand() % column;
      if(board[x][y] == 'M') continue;
      else board[x][y] = 'M';
      count++;
    }
  }
  void printTrueBoard(){
    for(int i = 0; i < row; i++){
      for(int j = 0; j < column; j++){
        cout << board[i][j] << " ";
      }
      cout << endl;
    }
    return;
  }
  void printPlayBoard(){
    for(int i = 0; i < row; i++){
      for(int j = 0; j < column; j++){
        cout << play_board[i][j] << " ";
      }
      cout << endl;
    }
    return;
  }
  int click(int i, int j, int action){
    if((board[i][j] == 'E' || board[i][j] == 'M') && action == 2 && play_board[i][j] == 'E'){
      play_board[i][j] = 'F';
      if(board[i][j] == 'M') mines--;
      if(mines == 0){
        return 1;
      }
    }
    else if(action == 2 && play_board[i][j] == 'F'){
      play_board[i][j] = 'E';
      if(board[i][j] == 'M') mines++;
    }
    else if(action == 1 && play_board[i][j] != 'F'){
      if(board[i][j] == 'M'){
        board[i][j] = 'X';
        play_board[i][j] = 'X';
        return -1;
      }
      else if(board[i][j] == 'E'){
        int mine_count = 0;
        for(int k = max(0, i-1); k <= min(i+1, row-1); k++){
          for(int l = max(0, j-1); l <= min(j+1, column-1); l++){
            if(board[k][l] == 'M') mine_count++;
          }
        }
        if(mine_count > 0){
          board[i][j] = (char)('0' + mine_count);
          play_board[i][j] = (char)('0' + mine_count);
        }
        else{
          board[i][j] = 'B';
          play_board[i][j] = 'B';
          int temp;
          for(int k = max(0, i-1); k <= min(i+1, row-1); k++){
            for(int l = max(0, j-1); l <= min(j+1, column-1); l++){
              if(board[k][l] == 'E') temp = click(k,l,1);
            }
          }
        }
      }
    }
    return 0;
  }
};

int main(){
  int level;
  cout << "Enter the difficulty: " << endl;
  cout << "0 -- Easy, 1 -- Medium, 2 -- Hard" << endl;
  cin >> level;
  mineSweep gamePlay(level);
  cout << endl;
  gamePlay.printPlayBoard();
  cout << endl;
  int result;
  while(true){
    int x, y, action;
    cin >> x >> y >> action;
    result = gamePlay.click(x,y,action);
    gamePlay.printPlayBoard();
    cout << endl;
    if(result == 1){
      cout << "You Win!" << endl;
      break;
    }
    else if(result == -1){
      cout << "You Lose!" << endl;
      break;
    }
  }
  return 0;
}
