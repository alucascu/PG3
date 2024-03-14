#include "maze.h"

maze::maze() {
	string mwidth;
	string mheight;
	cout << "enter the width" << endl;
	getline(cin, mwidth);
	cout << "enter the height" << endl;
	getline(cin, mheight);
	width = stoi(mwidth);
	height = stoi(mheight);

	

	grid = new queue<queue<char>*>;
	for (int j = 0; j < height; j++) {
		queue<char>* temp = new queue<char>;
		grid->push(temp);
		temp = nullptr;
	}
	this->fillMaze();
}
maze::maze(int mWidth, int mHeight) {
	width = mWidth;
	height = mHeight;
	grid = new queue<queue<char>*>;


	for (int j = 0; j < height; j++) {
		queue<char>* temp = new queue<char>;
		grid->push(temp);
		temp = nullptr;
	}
}
maze::~maze() {

}


void maze::print() {
	queue<char>* temp;
	char character;
	cout << "------------------" << endl;
	for (int i = 0; i < height; i++) {
		temp = grid->pop();
		cout << '|';
		for (int j = 0; j < width; j++) {
			character = temp->pop();
			cout << character;
			temp->push(character);
		}
		cout<< '|' << endl;
		grid->push(temp);

	}
	cout << "----------------------" << endl;
	temp = nullptr;
}
int maze::getHeight() {
	return this->height;
}
int maze::getWidth() {
	return this->width;
}
void maze::fillMaze() {

	queue<char>* temp;


	cout << "Please enter the maze" << endl;
	for (int i = 0; i < height; i++) {
		temp = grid->pop(); //Go to the first row
		//getline(cin, line);
		string fullName;
		getline(cin, fullName);


		for (int j = 0; j < width; j++) {
			temp->push(fullName[j]); // Fill that row with each character from the input line
		}


		grid->push(temp); // Put the queue we just filled back into queue
		temp = nullptr;
	}
}
char maze::peek(queue<char>* row) {

	char next = row->pop();


	queue<char>* temp = new queue<char>;
	temp->push(next);

	while (!(row->isEmpty())) {
		temp->push(row->pop());
	}

	while (!(temp->isEmpty())) {
		row->push(temp->pop());
	}


	return next;
}
char maze::rowPeekChar() {
	return peek(this->rowBelowPeek());
}
queue<char>* maze::rowPeek() {
	queue<char>* row = grid->pop();
	grid->push(row);

	for (int i = 0; i < height - 1; i++) {
		grid->push(grid->pop());
	}
	return row;
}
queue<char>* maze::rowBelowPeek() {
	grid->push(grid->pop());
	queue<char>* row = grid->pop();
	grid->push(row);

	for (int i = 0; i < height - 2; i++) {
		grid->push(grid->pop());
	}
	return row;
}
queue<char>* maze::rowPop() {
	return grid->pop();
}
char maze::columnPop() {
	return this->rowPeek()->pop();
}
void maze::columnPush(char letter) {
	(this->rowPeek())->push(letter);
}
void maze::rowPush(queue<char>* row) {
	grid->push(row);
}
void maze::shiftLeft() {
	for (int i = 0; i < height; i++) {
		queue<char>* temp = grid->pop();
		temp->push(temp->pop());
		grid->push(temp);
	}


}
void maze::shiftRight() {
	for (int j = 0; j < width - 1; j++) {
		shiftLeft();
	}
}
void maze::shiftUp() {
	grid->push(grid->pop());
}
void maze::shiftDown() {
	for (int i = 0; i < height - 1; i++) {
		grid->push(grid->pop());
	}
}
void maze::replaceWithLetter(queue<char>* row, char newLetter) {
	row->pop();
	row->push(newLetter);
	for (int i = 0; i < width - 1; i++)
		row->push(row->pop());
}