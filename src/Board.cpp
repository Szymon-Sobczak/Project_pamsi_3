#include "Board.hh"

/*
 *    Konstruktor klasy Board wraz z listą inicjalizacyjną. 
 */
Board::Board(unsigned int new_size, unsigned int new_streak) : size(new_size), streak(new_streak){
    board_state = new char*[size];
    for (unsigned int i = 0; i < size; ++i)
        board_state[i] = new char[size];

    for (unsigned int i = 0; i < size; ++i)
        for(unsigned int j = 0; j < size; ++j)
            board_state[i][j] = ' ';
}

/*
 *    Metoda wyświetlająca stan planszy - rozgrywki w terminalu. 
 */
void Board::PrintState(){
    for (unsigned int i = 0 ; i < size - 1; ++i)
        std::cout << "\t";
    std::cout << "   TIC-TAC-TOE" << std::endl;    
    for (unsigned int i = 0; i < size; ++i){
        std::cout << i << ".";
        for(unsigned int j = 0; j < size; ++j)
            j < size - 1 ? std::cout << "\t" << board_state[i][j] << "\t" <<"│" : std::cout << "\t" << board_state[i][j] << "\t"; 
        std::cout << std::endl << "─";
        for(unsigned int k = 0; k < size; ++k)
            k < size - 1 ? std::cout << "───────────────╬" : std::cout << "───────────────";   
        std::cout << std::endl;    
    }
    for(unsigned int z = 0; z < size; ++z)
        std::cout << "\t" << z << ".\t";
    std::cout << std::endl;   
}

/*
 *   Metoda służąca do umieszczania znaków X oraz O na planszy.
 */
void Board::PutChar(unsigned int i, unsigned int j, char symbol){
    if ((i < size && j < size) && (board_state[i][j] == 'X' || board_state[i][j] == 'O'))
            throw std::invalid_argument("Occupied field selected, please try again.");
    
    if (i < size && j < size)
        board_state[i][j] = symbol;
    else
        throw std::invalid_argument("Wrong position specified, please try again.");
    
}

/*
 *   Metoda sprawdzająca, czy pozostały jakiekolwiek puste miejsca na planszy.
 */
bool Board::IsSpaceAvailable(){
    for(unsigned int i = 0; i < size; ++i)
        for(unsigned int j = 0; j < size; ++j)
            if(board_state[i][j] == ' ')
                return true;
    return false;
}

/* 
 *   Metoda ocenijąca, czy doszło do wygranej, przegranej, czy remisu na planszy.
 */
int Board::EvaluateMove(){
    bool test = true;

    /* Sprawdzanie wierszy */
    for(unsigned k = 0; k < (size - streak + 1); ++k){
        for (unsigned int i = 0; i < size; ++i){
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
    for(unsigned k = 0; k < (size - streak + 1); ++k){
        for (unsigned int i = 0; i < size; ++i){
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
    for(unsigned int x = 0; x < size - streak + 1 ; ++x){
        for(unsigned int y = 0; y < size - streak + 1; ++y){
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
    for(unsigned int x = streak - 1; x < size; ++x){
        for(unsigned int y = 0; y < size - streak + 1; ++y){
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

/* 
 *   Implementacja algorytmu MinMax z alfa-beta cięciami.
 */
int Board::MinMaxAlfaBeta(int depth, bool maximisation, int alpha, int beta){
    int score = EvaluateMove();
    
    /* Ograniczenie głębokości rekurencji algorytmu MinMax */
    if(depth == 14 - int(size)){
        if (maximisation)
            return score - depth;
        if (!maximisation)
            return score + depth; 
        if(IsSpaceAvailable() == false)
            return 0; 
    }
    
    /* Heurystyka */
    if (score == 10)
        return score - depth;
    if (score == -10)
        return score + depth; 
    if(IsSpaceAvailable() == false)
        return 0; 

    if (maximisation){ // Jeżeli jest to ruch maksymalizatora
        int best = -1000;
            for(unsigned int i = 0; i < size; ++i){
                for (unsigned int j = 0; j < size; ++j)
                    if(board_state[i][j] == ' '){
                        board_state[i][j] = 'O';
                        
                        int val = MinMaxAlfaBeta(depth + 1, false, alpha, beta); // Pogłębienie rekurencji.
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
    else{ // Jeżeli jest to ruch minimalizatora
        int best = 1000;
            for(unsigned int i = 0; i < size; ++i){
                for (unsigned int j = 0; j < size; ++j)
                    if(board_state[i][j] == ' '){
                        board_state[i][j] = 'X';
                        int val = MinMaxAlfaBeta(depth + 1, true, alpha, beta); // Pogłębienie rekurencji.
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

/*
    Metoda służąca do wskazywania optymalnego ruchu dla gracza AI.
*/
std::pair<int, int> Board::FindBestMove(){
    int best_val = -100;
    int move_val = -100;
    std::pair<int,int> best_move{-1,-1};
    for(unsigned int i = 0; i< size; ++i){
        for(unsigned int j = 0; j < size; ++j){
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