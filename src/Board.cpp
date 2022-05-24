#include "Board.hh"

Board::Board(unsigned int NewSize) : Size(NewSize){
    board_state = new char*[Size];
    for (unsigned int i = 0; i < Size; ++i)
        board_state[i] = new char[Size];

    for (unsigned int i = 0; i < Size; ++i)
        for(unsigned int j = 0; j < Size; ++j)
            board_state[i][j] = ' ';
}

void Board::PrintState(){
    for (unsigned int i = 0 ; i < Size - 1; ++i)
        std::cout << "\t";
    std::cout << "   TIC-TAC-TOE" << std::endl;    
    for (unsigned int i = 0; i < Size; ++i){
        std::cout << i << ".";
        for(unsigned int j = 0; j < Size; ++j)
            j < Size - 1 ? std::cout << "\t" << board_state[i][j] << "\t" <<"│" : std::cout << "\t" << board_state[i][j] << "\t"; 
        std::cout << std::endl << "─";
        for(unsigned int k = 0; k < Size; ++k)
            k < Size - 1 ? std::cout << "───────────────╬" : std::cout << "───────────────";   
        std::cout << std::endl;    
    }
    for(unsigned int z = 0; z < Size; ++z)
        std::cout << "\t" << z << ".\t";
    std::cout << std::endl;   
}

void Board::PutChar(unsigned int i, unsigned int j, char symbol){
    if (board_state[i][j] == 'X' || board_state[i][j] == 'O')
        throw std::invalid_argument("Occupied field selected, please try again.");
    if (i < Size && j < Size)
        board_state[i][j] = symbol;
    else 
        throw std::invalid_argument("Wrong position specified, please try again.");
        
}