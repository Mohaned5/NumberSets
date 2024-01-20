#ifndef SetSolverSquareSet_h
#define SetSolverSquareSet_h

#include <vector>
using std::vector;


class SetSolverSquareSet
{
public:
    vector<int>set;

    SetSolverSquareSet(){
        for (int i = 1; i<10; i++){
            set.push_back(i);
        }
    }

    void setNum(int num){
        set = {num};
    }
    
    int getNum(){
        return set[0];
    }

};

#endif /* SetSolverSquareSet_h */
