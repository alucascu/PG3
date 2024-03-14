#pragma once
#include "queue.h"
#include <string>
#include <iostream>
using namespace std;

class maze {
private:
	int width;
	int height;

	queue<queue<char>*> *grid;

public: 
	maze(); //Default constructor requests the user for height, width and also to fill maze
	maze(int width, int height); // For manually filling
	~maze();
	

	void fillMaze(); // Requests that user fills out the maze
	void print(); //Prints out the current state of the maze
	char peek(queue<char>* row); //Peeks at the first character of the given row
	char rowPeekChar(); //Returns the peek of the row underneath the current row
	int getHeight(); //Returns height of the maze
	int getWidth(); //Returns width of the maze
	queue<char>* rowPeek(); // Returns the current row 
	queue<char>* rowBelowPeek();  // Returns the next row down but leaves maze in current order
	queue<char>* rowPop(); // Returns the current row, removes from row queue
	void rowPush(queue<char>* row); // Puts the given row onto the stack
	char columnPop(); // Returns the first character in the first row, pulls out of row
	void columnPush(char letter); // Puts given character onto the back of the queue
	void shiftLeft(); // Moves all rows to the left by popping each character off and putting it back on the queue
	void shiftRight(); // Moves all rows to the right by popping each character off and putting it back on the queue a certain number of times
	void shiftUp(); // Moves maze up one by popping each row off a certain number of times
	void shiftDown(); // Moves maze down by popping one row off and pushing it to the bottom of the queue
	void replaceWithLetter(queue<char>* row, char newLetter); // Replaces whatever the first letter in the row is without changing anything else
};
