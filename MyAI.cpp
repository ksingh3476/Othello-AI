
#include <ics46/factory/DynamicFactory.hpp>
#include "MyAI.hpp"
ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, ketans1::MyAI, "Ketan's AI (Required)");

std::pair<int, int> ketans1::MyAI::chooseMove(const OthelloGameState& state)
// Sets recursion depth at 2, checks who is playing as who and calculates best possible move
   {
     int depth = 2;

     std :: pair<int,int> best_move;

     if( state.isBlackTurn()){
         AIturn = 1;
         Other =0;
     }

     else{
       AIturn = 0;
       Other = 1;
     }


     std:: vector <std ::pair<int,int>> moves = posvalidmoves(state);
     int max = -999999;
     int min = 999999;
     
     for(int x=0; x < moves.size(); x++){
       std::unique_ptr<OthelloGameState> temp = state.clone();
       temp->makeMove(moves[x].first,moves[x].second);

       int  posmax = recur_search(*temp,depth);

       if ( posmax  > max){
         best_move = moves[x];
         max = posmax; 
     }

     else{
         min = posmax;

        }

 
   }

     return best_move;
}
    

std:: vector<std :: pair<int,int>> ketans1::MyAI::posvalidmoves(const OthelloGameState & state)
// Given a possible GameState, returns all of the possible moves that are legal
   {       
          std:: vector <std ::pair<int,int>> validmoves;

          const OthelloBoard & board = state.board();
          for(int w = 0; w < board.width(); w++){
          	for(int h = 0; h < board.height(); h++){
			if (state.isValidMove(w,h)){
				validmoves.push_back(std:: make_pair(w,h));
                        }
                 }
           }

           return validmoves;
   } 


int ketans1::MyAI :: eval( OthelloGameState & state)
// Given a gamestate, it assigns values to special positions on your board weighting them as more desireable
{   
    int val = 0;


    const OthelloBoard & evalboard = state.board();

    int  h = evalboard.height();
    int  w = evalboard.width();

    for(int x = 1; x < w -1 ; x++){
        if(( evalboard.cellAt(x,0) == OthelloCell :: black && AIturn == 1) ||( evalboard.cellAt(x,0) == OthelloCell :: white && AIturn == 0)){
           val += 5;
        }

     }

      for(int x = 1; x < w -1 ; x++){
              if(( evalboard.cellAt(x,7) == OthelloCell :: black && AIturn == 1) ||( evalboard.cellAt(x,7) == OthelloCell :: white && AIturn == 0)){
                         val += 5;
              }
      }


        for(int y = 1; y < h -1 ; y++){
                      if(( evalboard.cellAt(0,y) == OthelloCell :: black && AIturn == 1) ||( evalboard.cellAt(0,y) == OthelloCell :: white && AIturn == 0)){
                             val += 5;
                         }
        }

   


    
    if((evalboard.cellAt(0,0) == OthelloCell :: black && AIturn == 1) || (evalboard.cellAt(0,0) == OthelloCell:: white && AIturn == 0)){
        val += 10;
        }

    if((evalboard.cellAt(0,7) == OthelloCell :: black && AIturn == 1) || (evalboard.cellAt(0,7) == OthelloCell:: white && AIturn == 0)){
            val += 10;
                    }

    if((evalboard.cellAt(7,0) == OthelloCell :: black && AIturn == 1) || (evalboard.cellAt(7,0) == OthelloCell:: white && AIturn == 0)){
            val += 10;
                    }

    if((evalboard.cellAt(7,7) == OthelloCell :: black && AIturn == 1) || (evalboard.cellAt(0,0) == OthelloCell:: white && AIturn == 0)){
            val += 10;
                    }
   

	if(state.isWhiteTurn() && AIturn == 0 ){
		return ( val + ( state.whiteScore() - state.blackScore()));
        }
        
        else {
        	return( val + (state.blackScore() - state.whiteScore())) ;
        }
     
}


int ketans1::MyAI:: recur_search(  OthelloGameState & state , int depth)
// As given in class,from the possibles moves I can make return the max or min depending on whose turn it is
{
  if( depth == 0) {
      return eval(state);
    }

  else{

    if(( AIturn == 1 && state.isBlackTurn()) ||( AIturn == 0 && state.isWhiteTurn()) )
      {
         int max = 0 ;

         std:: vector <std ::pair<int,int>> moves = posvalidmoves(state);
        
         for(int i = 0; i < moves.size(); i++){
            std::unique_ptr<OthelloGameState> temp = state.clone();
            std ::pair <int,int> move_try = moves[i];
            temp->makeMove(move_try.first,move_try.second);
            
            if( eval(* temp) > recur_search(* temp,depth -1)) {
                 max = eval(*temp);
                 }
            else{
                max = recur_search(* temp,depth-1);
                }
           }
           
       
          return max;
    }

    else if (( AIturn == 0 && state.isBlackTurn()) ||( AIturn == 1 && state.isWhiteTurn())) {
        int min  = 0;

         std:: vector <std ::pair<int,int>> moves = posvalidmoves(state);
        
         for(int i = 0; i < moves.size(); i++){
            std::unique_ptr<OthelloGameState> temp = state.clone();
            std ::pair <int,int> move_try = moves[i];
            temp->makeMove(move_try.first,move_try.second);
           

            
            if( eval(* temp) < recur_search(* temp,depth -1)) {
                 min = eval(*temp);
                 }
            else{
                min = recur_search(* temp,depth-1);
                }
           }
           
        
          return min;
    }
    
  }    
    
}






           

            
             
             

           

           
        
        
      
