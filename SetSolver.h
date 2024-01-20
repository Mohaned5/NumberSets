#ifndef SetSolver_h
#define SetSolver_h

#include <string>
#include <iostream>
#include <memory>
#include "SetSolverSquareSet.h"

using std::vector;
using std::string;

class SetSolver{
private:
    int boardSize = 9;
    vector<vector<SetSolverSquareSet>>board;
    vector<vector<int>> x_used; 
    vector<vector<int>> y_used = {{}, {}, {}, {}, {}, {}, {}, {}, {}}; 
    
public:
void Solve() {
    SolveSudoku();

}

/*The function takes a vector of strings
and translates/converts them to a vector of integers based on the following rules.
1. A zero remains a zero (denotes an empty black square)
2. A string of “-x” (negative integer) remains a negative number as an int (denotes a
black square with a number)
3. An asterisk is converted and stored as the number 99. (e.g. it denotes an empty
white square, which may hold any value from 1 to 9).*/
void PopulateBoard(vector<string> skeletonBoard){
    for(string line : skeletonBoard){
        vector<int> x_used_line; 
        vector<SetSolverSquareSet> new_line;
        int is_negative = 1;
        int y_counter = 0;
        for (char ch : line){
            SetSolverSquareSet square;
            if (ch == '*'){
                square.setNum(99);
            }
            else if (ch == '0'){
                square.setNum(0);
            }
            else if (ch == '-'){
                is_negative = -1;
                continue;
            }
            else{
                int val = ch - '0';
                square.setNum(is_negative * (val));
                is_negative = 1;
                x_used_line.push_back(val);
                y_used[y_counter % 9].push_back(val);
   
            }
            y_counter++;
            new_line.push_back(square);
        }
        board.push_back(new_line);
        x_used.push_back(x_used_line);
    }

}


/* Returns the value for a particular cell. It should return -x for a negative number (denoting a black square with a number), x for a white
square with a number, a zero for an empty black square and 99 for an empty white square.*/
int ReturnValue(size_t row, size_t col)
{
    return board[row][col].getNum();
}

/* Solves the board so that each empty white cell has been ﬁlled
with the correct value. */
bool SolveSudoku() {

    for (int row = 0; row < boardSize; row ++){
        for (int col = 0; col < boardSize; col ++){
            if (board[row][col].getNum() == 99){
                for (int num = 1; num <= 9; ++num) {
                    if (IsValidMove(row, col, num)) {
                        board[row][col].setNum(num);
                        x_used[row].push_back(num);
                        y_used[col].push_back(num);
                        if (SolveSudoku()) {
                            return true;
                        }
                        board[row][col].setNum(99);
                        x_used[row].pop_back();
                        y_used[col].pop_back();
                    }
                }
                return false;
            }
        }
    }
    return true;

}

/* Checks if a move is valid according to the rules, i.e. if the number exists
in the x or y column, if the number CAN exist in the compartment*/
bool IsValidMove(int row, int col, int num) {
    vector<vector<int>> subgrids = GetSubgrid(row, col);
    return  !Contains(x_used[row], num) &&
            !Contains(y_used[col], num) &&
            IsContinuous(subgrids[0], num) &&
            IsContinuous(subgrids[1], num);
}

/* Finds the compartments a cell is in and returns the existing numbers in each
respective compartment */
std::vector<vector<int>> GetSubgrid(int row, int col) {
    std::vector<int> x_subgrid;
    std::vector<int> y_subgrid;
    bool found_compartment = false;
    for (int j = 0; j < boardSize; ++j) {
        int num = board[row][j].getNum();
        if (j == col && num > 0){
            x_subgrid.push_back(num);
            found_compartment = true;
        }
        else if (num <= 0 && !found_compartment) {
            x_subgrid.clear();
        }
        else if (num <= 0 && found_compartment ){
            break;
        }
        else if(num > 0){
            x_subgrid.push_back(num);
        }
    }
    found_compartment = false;
    for (int i = 0; i < boardSize; ++i) {
        int num = board[i][col].getNum();
        if (i == row && num > 0){
            y_subgrid.push_back(num);
            found_compartment = true;
        }
        else if (num <= 0 && !found_compartment) {
            y_subgrid.clear();
        }
        else if (num <= 0 && found_compartment){
            break;
        }

        else{
            y_subgrid.push_back(num);
        }
    }
    std::vector<vector<int>> subgrids = {x_subgrid, y_subgrid};


    return subgrids;
}   

/* Checks if the numbers in a compartment are still continous with the 
added number n*/
bool IsContinuous(const std::vector<int>& subgrid, int n) {
    int size = subgrid.size();
    int max = 0;
    int min = 1000;
    for (int num : subgrid){
        if (num != 99 && num > max){
            max = num;
        }
        if (num != 99 && num < min){
            min = num;
        }
    }
    int upper_bound = min + size - 1;
    int lower_bound = max - size + 1;
    return lower_bound <= n && n <= upper_bound; 
}

/* Checks if a list contains a number  */
bool Contains(const std::vector<int>& vec, int num) {
    for (const auto& element : vec) {
        if (element == num) {
            return true;
        }
    }
    return false;
}


    

};
#endif /* SetSolver_h */