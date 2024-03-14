#pragma once
#include "maze.h"
using namespace std;

class Move {
private:
	queue<int>* moveList;  // Ints represent the move that should be taken. 1 means move down, 2 means move left


public:
	Move(); // Initialize a new Move object without anything in the movelist
	Move(int onlyMove); // Initialize new Move object with one move in the movelist
	Move(int firstOption, int secondOption); // Initialize new Move object with two moves in the movelist
	~Move();


	int getNextMove(); // Used if you need to try the next move in the movelist (operates with pop) 
	int getCurrentMove(); // Used if you are working with the first move (operates with peek)
	void addNewOption(int newOption); // To push a new move onto the movelist queue essentially makes the second two overloaded constructors irrelevant but I am afraid to delete them
};

class solver {
private:
	queue<Move*> *solution; // A queue of move object which keeps track of the path. Each move object stores all possible moves at each juncture
	maze *inputMaze; // The user supplied unsolved maze
	int solutionLength; // Tracks how long the solution is. Used in get last and peek last to find the last executed move in the queue
	int rightDepth; // Tracks how far to the right you are, provides the halting condition for the solve() method
	int downDepth; // Tracks how far down you are, provides the halting condition for the solve() method

public:
	solver(maze *unsolvedMaze); // Initializes all values to their required values. Solves maze on initialization
	~solver();

	void solve(); // Solves maze provided to the solver object
	void addMove(Move *newMove); //Pushes a new move onto the solution queue
	void undoLastMove(); // Undoes the last move by replacing current position with a space, changing the maze back to the original state and making sure there is a valid new move at the new last move. If there is not one of these, the function will recurse until there is a valid new option
	Move* nextValidMove(); // Returns a move object with all valid moves at the current location
	void tryCurrentMove(Move* nextMove); // Adjusts the maze to perform the given move, adds move to the solution queue. Always given input from next valid move in some way.
	Move* getLast(); // Returns and removes the last move object listed in the  solution queue
	Move* peekLast(); // Returns and maintains the last move object listed in the solution queue
};
