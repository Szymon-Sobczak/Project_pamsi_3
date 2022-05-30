#include "Board.hh"

Board::Board(unsigned int NewSize, unsigned int new_streak) : Size(NewSize), streak(new_streak){
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
    for(unsigned k = 0; k < (Size - streak + 1); ++k){
        for (unsigned int i = 0; i < Size; ++i){
            for (unsigned int j = 0; j < streak - 1; ++j){
                if(board_state[i][j+k] != board_state[i][j+k+1]){
                    test = false;
                    break;
                }
            }
            if (test == true && (board_state[i][k] == 'X'))
                return -10;
            if (test == true && (board_state[i][k] == 'O'))
                return 10;
            test = true;
        }
    }
    
    /* Sprawdzanie kolumn */
    for(unsigned k = 0; k < (Size - streak + 1); ++k){
        for (unsigned int i = 0; i < Size; ++i){
            for (unsigned int j = 0; j < streak - 1; ++j){
                if(board_state[j+k][i] != board_state[j+k+1][i]){
                    test = false;
                    break;
                }   
            }
            if (test == true && (board_state[k][i] == 'X'))
                return -10;
            if (test == true && (board_state[k][i] == 'O'))
                return 10;
            test = true;
        }
    }
    /* Sprawdzanie przekątnej */
    for(unsigned int x = 0; x < Size - streak + 1 ; ++x){
        for(unsigned int y = 0; y < Size - streak + 1; ++y){
            for (unsigned int i = 0; i < streak - 1; ++i){
                    if(board_state[x+i][y+i] != board_state[x+i+1][y+i+1]){
                        test = false;
                        break;
                    }  
            }
            if (test == true && (board_state[x][y] == 'X'))
                return -10;
            if (test == true && (board_state[x][y] == 'O'))
                return 10;
            test = true;
        }
    }
    /* Sprawdzanie przeciwprzekątnej */
    for(unsigned int x = streak - 1; x < Size; ++x){
        for(unsigned int y = 0; y < Size - streak + 1; ++y){
            for (unsigned int i = 0; i < streak - 1; ++i){
                if(board_state[x - i][y + i] != board_state[x - 1 - i][y + i + 1]){
                        test = false;
                        break;
                    }
            }
            if (test == true && (board_state[x][y] == 'X'))
                return -10;
            if (test == true && (board_state[x][y] == 'O'))
                return 10;
            test = true;
        }
    }

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
                        board_state[i][j] = 'O';
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
                        board_state[i][j] = 'X';
                        best = std::min(best, MinMax(depth+1, !isMax));
                        board_state[i][j] = ' ';
                    }
            }
        return best;
    }
}

int Board::MinMaxAlfaBeta(int depth, bool isMax, int alpha, int beta){
    int score = EvaluateMove();
    
    if(depth == 14 - int(Size)){
        if (isMax)
            return score - depth;
        if (!isMax)
            return score + depth; 
        if(IsSpaceAvailable() == false)
            return 0; 
    }

    if (score == 10)
        return score - depth;
    if (score == -10)
        return score + depth; 
    if(IsSpaceAvailable() == false)
        return 0; 

    if (isMax){
        int best = -1000;
            for(unsigned int i = 0; i < Size; ++i){
                for (unsigned int j = 0; j < Size; ++j)
                    if(board_state[i][j] == ' '){
                        board_state[i][j] = 'O';
                        
                        int val = MinMaxAlfaBeta(depth + 1, false, alpha, beta);
                        best = std::max(best, val);
                        alpha = std::max(alpha, best);

                        board_state[i][j] = ' ';
                        
                        if (alpha >= beta)
                            break;
                    }
                if (alpha >= beta)
                    break;
            }
        return best;
    }
    else{
        int best = 1000;
            for(unsigned int i = 0; i < Size; ++i){
                for (unsigned int j = 0; j < Size; ++j)
                    if(board_state[i][j] == ' '){
                        board_state[i][j] = 'X';
                        int val = MinMaxAlfaBeta(depth + 1, true, alpha, beta);
                        best = std::min(best, val);
                        beta = std::min(beta, best);
                        
                        board_state[i][j] = ' ';
                        if (alpha >= beta)
                            break;
                    }
                if (alpha >= beta)
                    break;
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
                move_val = MinMaxAlfaBeta(0, false, -1000, 1000);
                board_state[i][j] = ' ';
            }
            if (move_val > best_val){
                best_move = {i,j};
                best_val = move_val;
            }
        }
    }
    return best_move;
}