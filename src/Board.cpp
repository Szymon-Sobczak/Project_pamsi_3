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
        if(board_state[Size - 1 - i][i] != board_state[Size - 2 - i][i+1])
            test = false;
    }
    if (test == true && (board_state[0][Size-1] == 'X'))
        return 10;
    if (test == true && (board_state[0][Size - 1] == 'O'))
        return -10;
    test = true;

    return 0;
}

int Board::MinMax(int depth, bool isMax){
    int score = EvaluateMove();
    
    if (score == 10)
        return score;
    
    if (score == -10)
        return score; 
    
    if(IsSpaceAvailable() == false)
        return 0; 
    
    if (isMax){
        int best = -1000;
            for(unsigned int i = 0; i < Size; ++i){
                for (unsigned int j = 0; j < Size; ++j)
                    if(board_state[i][j] == ' '){
                        board_state[i][j] = 'X';
                        best = std::max(best, MinMax(depth+1, !isMax));
                        board_state[i][j] = ' ';
                    }
            }
        return best;
    }
    else{
        int best = 1000;
            for(unsigned int i = 0; i < Size; ++i){
                for (unsigned int j = 0; j < Size; ++j)
                    if(board_state[i][j] == ' '){
                        board_state[i][j] = 'O';
                        best = std::min(best, MinMax(depth+1, !isMax));
                        board_state[i][j] = ' ';
                    }
            }
        return best;
    }
}

std::pair<int, int> Board::FindBestMove(){
    int best_val = -100;
    int move_val = -100;
    std::pair<int,int> best_move{-1,-1};
    for(unsigned int i = 0; i< Size; ++i){
        for(unsigned int j = 0; j < Size; ++j){
            if (board_state[i][j] == ' '){
                board_state[i][j] = 'O';
                move_val = MinMax(0, false);
                std::cout << "MOVE VAL: " << move_val <<std::endl;
                board_state[i][j] = ' ';
            }
            if (move_val > best_val){
                best_move = {i,j};
                best_val = move_val;
            }
        }
    }
    std::cout << "AI w metodzie: " << best_move.first << " " << best_move.second <<std::endl;
    return best_move;
}