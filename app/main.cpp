
#include "Board.hh"
int main(){
   unsigned int game_size = 3, streak = 3;
   unsigned int Col = 0, Row = 0;
   std::pair<int, int> ai_move = {0,0};
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
   // while (1){ 
   //    try{
   //       std::cout << "Please specify the streak of characters required to win, it must be less than the size of the board >>> ";
   //       std::cin >> streak;
         
   //       if(std::cin.fail())
   //          throw std::invalid_argument("Typing error, please try again.");
         
   //       if (streak > game_size)
   //          throw std::invalid_argument("Wrong streak, please try again.");
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
   Board TicTacToe = Board(game_size, streak);
  // system("clear");
   std::cout << "Let the game begin! You play X and the AI plays O." << std::endl;
   while (1){
      try{ 
         std::cout << "Sprawdzam: " << TicTacToe.EvaluateMove() << std::endl;
         TicTacToe.PrintState();
         std::cout << "Enter positon Row, Col >>> ";
         std::cin >> Col >> Row;
         if(std::cin.fail())
            throw std::invalid_argument("Typing error, please try again.");
         
         TicTacToe.PutChar(Col, Row, 'X');
         
         if (!TicTacToe.IsSpaceAvailable()){
            std::cout << "--- TIE ---" << std::endl;
            break;
         }
         system("clear");
         TicTacToe.PrintState();;
       
         if (TicTacToe.EvaluateMove() == -10){
            std::cout << "!!!YOU WON!!!" << std::endl;
            break;
         }

         ai_move = TicTacToe.FindBestMove();
         TicTacToe.PutChar(ai_move.first, ai_move.second, 'O');

         if (TicTacToe.EvaluateMove() == 10){
            std::cout << "XXX AI WON XXX" << std::endl;
            break;
         }  
           system("clear"); 
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