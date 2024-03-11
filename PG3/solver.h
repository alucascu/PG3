#pragma once
#include "maze.h"
using namespace std;

class Move {
private:
	queue<int>* moveList;  // Ints represenent the move that should be taken. 1 means move down, 2 means move left


public:
	Move();
	Move(int onlyMove);
	Move(int firstOption, int secondOption);
	~Move();


	int getNextMove(); // Used if you need to try the next move in the movelist (operates with pop) 
	int getCurrentMove(); // Used if you are working with the first move (operates with peek)
	void addNewOption(int newOption); 
};

class solver {
private:
	queue<Move*> *solution;
	maze *inputMaze;
	maze *solvedMaze;
	bool undoneFlag;
	int solutionLength;
	int rightDepth;
	int downDepth;
public:
	solver(maze *unsolvedMaze);
	~solver();

	void solve();
	void addMove(Move *newMove); 
	void undoLastMove();
	Move* nextValidMove();
	void tryNextMove(Move *nextMove);
	void tryCurrentMove(Move* nextMove);
	Move* getLast();
	Move* peekLast();
};
