# NumberSets

(No additional libraries are used apart from vector, iostream, memory and string.)

# The Puzzle

NumberSets is a numbers puzzle, which is very similar to Sudoku. It is played on a 9x9 board where the board is partially ﬁlled with numbers in white and black cells. The aim is to ﬁll the empty white cells with the correct numbers. White cells with numbers and all black cells (both empty and not) are blocked and mustn’t be changed. This program ﬁlls the board’s white cells that are empty by taking into account all the rules that are described below. All tasks refer to cells using 0-8 index to represent cell positions for both rows and columns.

1. Rows and columns are divided into compartments.
2. A compartment is a series of uninterrupted white cells.
3. Each compartment needs to be ﬁlled with an unordered but uninterrupted set of numbers. That said, compartments do not necessarily need to continue each other’s numbers. i.e the numbers in a compartment should be able to be rearranged to form a consecutive series of numbers.
4. Possible numbers are 1-9.
5. By uninterrupted we mean there are no gaps in the middle (e.g., 3, 1, 2 or 5, 9, 6, 8, 7).
6. The number within any given compartment can appear in any order.
7. Like Sudoku, no single number can repeat in any row or column (irrespective of compartments).


## Inputs
To represent the board, a vector of strings (vector <std::string>) will be used. It represents an empty black square as 0, an empty white square as an * and a black square with a number as a negative of that that number. We’re only using negative numbers for black squares that have numbers in order to distinguish them from a white cell with number. For clarity, empty white squares can only contain positive numbers 1 through to 9.
As an example, the a board will be represented in the following way:
vector<string> easyBoard = {"00**0-31*0",
                            "*****0**0",
                            "7*003*-5**",
                            "**05**7**",
                            "*0**0*6-9*",
                            "4***650**",
                            "*2-8**00**",
                            "-23*0*****",
                            "043-608*0-1"};

e.g to run

unique_ptr<SetSolver>board(new SetSolver());
vector<string>
skeletonBoard{      "00**0-31*0",
                    "*****0**0",
                    "7*003*-5**",
                    "**05**7**",
                    "*0**0*6-9*",
                    "4***650**",
                    "*2-8**00**",
                    "-23*0*****",
                    "043-608*0-1"};

board->PopulateBoard(skeletonBoard);
board->Solve();

This would return this output:
{0,0,6,7,0,-3,1,2,0},
{6,7,5,8,4,0,2,3,0},
{7,8,0,0,3,4,-5,1,2},
{8,9,0,5,2,6,7,4,3},
{5,0,1,2,0,7,6,-9,4},
{4,1,2,3,6,5,0,8,7},
{3,2,-8,4,5,0,0,7,6},
{-2,3,4,0,7,9,8,6,5},
{0,4,3,-6,0,8,9,0,-1}
Where positive numbers are filled white squares, negative numbers are numbered black squares and zeroes are empty black squares.
