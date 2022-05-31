#include <iostream>
#include <memory>
#include <fstream>
#include <string>
#include <iomanip>
#include <bits/stdc++.h>

/*
 * Klasa reprezentująca planszę do gry w kółko i krzyżyk. 
 */
class Board{
    unsigned int size, streak; /* Rozmiar pola kwadratowego planszy, Ilość znaków w serii potrzebnych do wygranej */
    char **board_state; /* Wskaźnik na tablicę 2D reprezentująca planszę */
    int MinMaxAlfaBeta(int depth, bool maximisation, int alpha, int beta); /* Implementacja algorytmu MinMax z alfa-beta cięciami*/  
    
    public: 
        Board(unsigned int new_size, unsigned int new_streak); /* Konstruktor parametryczny */
        void PutChar(unsigned int i,unsigned int j, char symbol); /* Metoda pozwalająca na wstawianie znaków na planszę */
        void PrintState(); /* Metoda wyświetlająca stan planszy */
        bool IsSpaceAvailable(); /* Metoda sprawdzająca, czy pozostały jakiekolwiek wolne miejsca na planszy */
        int EvaluateMove();  /* Metoda heurystyczna oceniająca stan gry*/
        std::pair<int,int> FindBestMove(); /* Metoda slużąca do wskazania optymalnego ruchu gracza AI */
};

