
#include "Board.hh"

 

int main(){
   unsigned int game_size = 4;
   // unsigned int Col, Row;
     unsigned int Col;
   system("clear"); 
   // std::cout << "!!!   WELCOME TO THE GAME   !!!" << std::endl;
   // std::cout  <<" _____ ___ ___   _____ _   ___   _____ ___  ___ " << std::endl
   //            <<"|_   _|_ _/ __| |_   _/_| / __| |_   _| _ || __|" << std::endl
   //            <<"  | |  | | (__    | |/ _|| (__    | | |(_)|| _| " << std::endl
   //            <<"  |_| |__ |___|   |_/_/ | |___|   |_| |___||___|" << std::endl << std::endl;
   // while (1){ 
   //    try{
   //       std::cout << "Please specify the size of the board, it should be in the range [3;10] >>> ";
   //       std::cin >> game_size;
         
   //       if(std::cin.fail())
   //          throw std::invalid_argument("Typing error, please try again.");
         
   //       if (game_size < 3 || game_size > 10)
   //          throw std::invalid_argument("Wrong size of the board specified, please try again.");
   //       else
   //          break;
   //    }
   //    catch (std::invalid_argument & e){
   //          system("clear");
   //          std::cin.clear();
   //          std::cin.ignore(10000,'\n'); 
   //          std::cerr << "! An error has occurred: " << std::endl << e.what() << std::endl;
   //    }
   // } 
   Board TicTacToe = Board(game_size);
   system("clear");
   std::cout << "Let the game begin! You play X and the AI plays O." << std::endl;
   while (1){
      try{
         std::cout << "Sprawdzam: " << TicTacToe.EvaluateMove() << std::endl;

         TicTacToe.PrintState();
         // std::cout << "Enter positon Row, Col >>> ";
         std::cin >> Col;
         // if(std::cin.fail())
         //    throw std::invalid_argument("Typing error, please try again.");
         //TicTacToe.PutChar(Col, Row, 'X');
         if(Col == 1){
             TicTacToe.PutChar(2, 0, 'X');
         TicTacToe.PutChar(1, 1, 'X');
         TicTacToe.PutChar(0, 2, 'X');
        // TicTacToe.PutChar(2, 1, 'O');
         }
        
           //TicTacToe.PrintState();;
         //system("clear");
      }
      catch (std::invalid_argument & e){
         system("clear");
         std::cin.clear();
         std::cin.ignore(10000,'\n');
         std::cerr << "! An error has occurred: " << std::endl << e.what() << std::endl;
      }
   }
   return 0;
} 