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
    if ((i < Size && j < Size) && (board_state[i][j] == 'X' || board_state[i][j] == 'O'))
            throw std::invalid_argument("Occupied field selected, please try again.");
    
    if (i < Size && j < Size)
        board_state[i][j] = symbol;
    else
        throw std::invalid_argument("Wrong position specified, please try again.");
    
}

bool Board::IsSpaceAvailable(){
    for(unsigned int i = 0; i < Size; ++i)
        for(unsigned int j = 0; j < Size; ++j)
            if(board_state[i][j] == ' ')
                return true;
    return false;
}



// C++ program to find the next optimal move for

using namespace std;
 
struct Move
{
    int row, col;
};
 
char player = 'x', opponent = 'o';
 
// This function returns true if there are moves
// remaining on the board. It returns false if
// there are no moves left to play.
// bool isMovesLeft(char board[3][3])
// {
//     for (int i = 0; i<3; i++)
//         for (int j = 0; j<3; j++)
//             if (board[i][j]=='_')
//                 return true;
//     return false;
// }

int Board::EvaluateMove(){
    bool test = true;
    
    /* Sprawdzanie wierszy */
    for (unsigned int i = 0; i < Size; ++i){
        for (unsigned int j = 0; j < Size - 1; ++j){
            if(board_state[i][j] != board_state[i][j+1])
                test = false;
        }
        if (test == true && (board_state[i][0] == 'X'))
            return 10;
        if (test == true && (board_state[i][0] == 'O'))
            return -10;
        test = true;
    }
    
    /* Sprawdzanie kolumn */
    for (unsigned int i = 0; i < Size; ++i){
        for (unsigned int j = 0; j < Size - 1; ++j){
            if(board_state[j][i] != board_state[j+1][i])
                test = false;
        }
        if (test == true && (board_state[0][i] == 'X'))
            return 10;
        if (test == true && (board_state[0][i] == 'O'))
            return -10;
        test = true;
    }
    
    /* Sprawdzanie przekątnej */
    for (unsigned int i = 0; i < Size - 1; ++i){
            if(board_state[i][i] != board_state[i+1][i+1])
                test = false;
        }
    if (test == true && (board_state[0][0] == 'X'))
            return 10;
    if (test == true && (board_state[0][0] == 'O'))
            return -10;
    test = true;
    
    /* Sprawdzanie przeciwprzekątnej */
    for (unsigned int i = 0; i < Size - 1; ++i){
           std::cout << "BLA" << std::endl;
        if(board_state[i][Size - 1 - i] != board_state[i+1][Size - i])
            test = false;
    }
    if (test == true && (board_state[0][Size-1] == 'X'))
        return 10;
    if (test == true && (board_state[0][Size - 1] == 'O'))
        return -10;
    test = true;

    return 0;
}


