#include <iostream>
#include <memory>
#include <fstream>
#include <string>
#include <iomanip>
#include <bits/stdc++.h>

class Board{
    unsigned int Size;
    char ** board_state;
    public: 
        Board(unsigned int NewSize);
        void PutChar(unsigned int i,unsigned int j, char symbol);
        void PrintState();
};