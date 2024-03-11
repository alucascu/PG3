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
	queue<char>* rowBelowPeek(); 
	queue<char>* rowPop();
	void rowPush(queue<char>* row);
	char columnPop();
	void columnPush(char letter);
	void shiftLeft();
	void replaceWithLetter(queue<char>* row, char newLetter);
};
