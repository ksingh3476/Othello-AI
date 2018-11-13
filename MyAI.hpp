#include "OthelloAI.hpp"

namespace ketans1
   {
     class MyAI: public OthelloAI
      {
         public:

        virtual std:: pair<int,int> chooseMove(const OthelloGameState & state);

        std:: vector<std:: pair<int,int>> posvalidmoves(const OthelloGameState & state);

        int eval( OthelloGameState & state);
        
        int recur_search( OthelloGameState & state, int depth);


        private:
        int AIturn;
        int Other;
      };
   }

