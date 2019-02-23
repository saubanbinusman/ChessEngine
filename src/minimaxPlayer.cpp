#include "..\\include\\minimaxPlayer.h"
#include<iostream>
#include "..\\include\\ENUM.h"
#include "..\\include\\gameState.h"
#include<cstdlib>
using namespace std;

minimaxPlayer::minimaxPlayer(Color playerColor):chessPlayer("Minimax Player", playerColor){


}

// Implements MiniMax(Negamax variation) optimized using Alpha-Beta Pruning
int minimaxPlayer::minimax(gameState* state, int currDepth, int a, int b, bool white)
{
    if (currDepth == 0)
    {
    	return evaluate(state);
    }
    
    int TotalMoves = state->Actions.getActionCount();
    
    if (white)
    {
	    int bestScore = -INF; // Need to maximize this
	    
	    for (int i = 0; i < TotalMoves; ++i)
	    {
	    	action currMove;
	    	state->Actions.getAction(i, &currMove);
	    	
	    	gameState newGameState = *state; // Make a copy of game state
	    	newGameState.applyMove(currMove); // Apply the move
	    	int score = minimax(&newGameState, currDepth - 1, a, b, !white); // Run MiniMax on new state (so that original state remains untouched)
	    	
	    	bestScore = max(bestScore, score);
	    	a = max(a, bestScore);
	    	
	    	if (b <= a) return bestScore;
	    }
	    
	    return bestScore;
    }
    
    else
    {
	    int bestScore = INF; // Need to minimize this
	    
	    for (int i = 0; i < TotalMoves; ++i)
	    {
	    	action currMove;
	    	state->Actions.getAction(i, &currMove);
	    	
	    	gameState newGameState = *state; // Make a copy of game state
	    	newGameState.applyMove(currMove); // Apply the move
	    	int score = minimax(&newGameState, currDepth - 1, a, b, !white); // Run MiniMax on new state (so that original state remains untouched)
	    	
	    	bestScore = min(bestScore, score);
	    	b = min(b, bestScore);
	    	
	    	if (b <= a) return bestScore;
	    }
	    
	    return bestScore;
    }
}

// Uses piece values (material) + piece-square tables (positional value of pieces)
// for the evaluation of given game state
int minimaxPlayer::evaluate(gameState* state)
{
	int sum = 0;
	
    for (int i = 0; i < 8; ++i)
    {
    	for (int j = 0; j < 8; ++j)
    	{
    		int val = getPieceMaterial(state -> Board.board[i][j]) +
    		          getPieceSquareValue(state -> Board.board[i][j], i, j);
    		
    		sum += (val * ((state -> Board.board[i][j]) > 0 ? 1 : -1));
    	}
    }
    
    return sum;
}

int minimaxPlayer::getPieceSquareValue(const int& piece, const int& row, const int& col)
{
	// Black
	if (piece < 0) return pst[(-piece) - 1][row][col];
	
	// White
	else if (piece > 0) return pst[piece - 1][7 - row][col];
    
    return 0;
}

int minimaxPlayer::getPieceMaterial(const int& piece)
{
    switch (abs(piece))
    {
        case 1: return 100;   // Pawn
        case 2: return 320;   // Knight
        case 3: return 330;   // Bishop
        case 4: return 500;   // Rook
        case 5: return 900;   // Queen
        case 6: return 20000; // King
        
        default: return 0;
    }
}

void minimaxPlayer::decideMove(gameState* state, action* Move, int maxDepth){
    int TotalMoves = state->Actions.getActionCount(); //= state->computePossibleActions();
    cout<<"Total Possible Moves: "<<TotalMoves << endl;
    if(TotalMoves == 0){
        Move->fromRow = Move->fromCol= Move->toRow = Move->toCol = 0;
        return;
    }
    
    int bestScoreMove = -1; // Best Move Index
    int bestScore = -INF; // Need to maximize this
    
    for (int i = 0; i < TotalMoves; ++i)
    {
    	action currMove;
    	state->Actions.getAction(i, &currMove);
    	
    	gameState newGameState = *state; // Make a copy of game state
    	newGameState.applyMove(currMove); // Apply the move
    	int score = minimax(&newGameState, maxDepth - 1, -INF, INF, false); // Run MiniMax on new state (so that original state remains untouched)
    	
    	if (score > bestScore)
    	{
    		bestScore = score;
    		bestScoreMove = i;
    	}
    }
    
    state->Actions.getAction(bestScoreMove, Move); // Return best move
    
    return;
}
