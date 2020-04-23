#include "chess.cpp"
#include <algorithm>

static final int INT_MAX = 2147483647;
static final int INT_MIN = -2147483648;

class PruningAI()
{	
	int search(Gamestate & board, int depth, int alpha, int beta, int player, int initialPlayer){
		// get moves and flatten them from 2d vector to 1d vector
    	vector<vector<Move>> d2Moves = board.getAllPossibleMoves(player);
    	vector<Move> moves;
    	for(int row = 0; row < d2Moves.size(); ++row){
        	for(int col = 0; col < d2Moves[row].size(); ++col){
            	moves.push_back(d2Moves[row][col]);
        	}
    	}

    	//base case
    	if(depth <= 0 || moves.empty()){
        	if(initialPlayer == 1)
            	return board.blackCount - board.whiteCount;
        	else
            	return board.whiteCount - board.blackCount;
    	}
    
    	//maximizing player
    	if(initialPlayer == player){
        	int value = INT_MIN;
        	for(int i = 0; i < moves.size(); ++i){
            	board.makeMove(moves[i], player);
            	value = max(value, search(board, depth - 1, alpha, beta, player % 2 + 1, initialPlayer)); //recurse and swap player
            	board.Undo();
            	alpha = max(alpha, value);
            	if(alpha >= beta){
                	break;
            	}
        	}
        	return value;
    	}
    
    	//minimizing player
    	else{
        	int value = INT_MAX;
        	for(int i = 0; i< moves.size(); ++i){
            	board.makeMove(moves[i], player);
            	value = min(value, search(board, depth - 1, alpha, beta, player % 2 + 1, initialPlayer));
            	board.Undo();
            	beta = min(beta, value);
            	if(alpha >= beta){
                	break;
            	}
        	}
        	return value;
    	}				
	}
};
