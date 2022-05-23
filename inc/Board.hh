#include <memory>
#include <fstream>
#include <string>
#include <iomanip>
#include <bits/stdc++.h>

template <unsigned int Size>
class Board{
    char board_state[Size][Size];

    public: 
        Board();
        int ChangeState(int i, int j, char symbol);
        void PrintState();
};

template <unsigned int Size>
Board<Size>::Board(){
    for (unsigned int i = 0; i < Size; ++i)
        for(unsigned int j = 0; j < Size; j++)
            board_state[i][j] = 'O';
}

template <unsigned int Size>
void Board<Size>::PrintState(){
    for (unsigned int i = 0; i < Size; ++i){
        for(unsigned int j = 0; j < Size; ++j){
            std::cout << "\t" << board_state[i][j];
            if (j < Size - 1)
            std::cout << "\t" <<  "│";
        }
        std::cout << std::endl;
        for(unsigned int k = 0; k < Size; ++k){
            if (k < Size - 1)
                std::cout << "────────────────╬";
            else 
                std::cout << "────────────────";
        }  
        std::cout << std::endl;    
    }
}