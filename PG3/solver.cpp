#include "solver.h"

Move::Move() {
	moveList = new queue<int>;
}
Move::Move(int onlyMove) {
	moveList = new queue<int>;
	moveList->push(onlyMove);
}
Move::Move(int firstOption, int secondOption) {
	moveList = new queue<int>;
	moveList->push(firstOption);
	moveList->push(secondOption);
}
Move::~Move() {
	delete moveList;
}
void Move::addNewOption(int newOption) {
	moveList->push(newOption);
}
int Move::getNextMove() {
	if (moveList->isEmpty())
		return 0;
	moveList->pop();

	return getCurrentMove();
}
int Move::getCurrentMove(){
	if (moveList->isEmpty()) {
		return 0;
	}
	int current = moveList->pop();
	queue<int>* temp = new queue<int>;
	while (!moveList->isEmpty())
		temp->push(moveList->pop());
	moveList->push(current);
	while (!temp->isEmpty())
		moveList->push(temp->pop());
	return current;
}






solver::solver(maze *unsolvedMaze) {
	solution = new queue<Move*>;
	inputMaze = unsolvedMaze;
	solutionLength = 1;
	rightDepth = 1;
	downDepth = 1;
	solve();
}
solver::~solver() {
	delete solution;
	delete inputMaze;

	solution = nullptr;
	inputMaze = nullptr;
}
void solver::solve() {
	inputMaze->replaceWithLetter(inputMaze->rowPeek(), 'X');
	while ((rightDepth != inputMaze->getWidth()) || (downDepth != inputMaze->getHeight())) {
		Move *nextMove = nextValidMove();
		tryCurrentMove(nextMove);
	}
	inputMaze->replaceWithLetter(inputMaze->rowPeek(), 'X');

	inputMaze->shiftLeft();
	inputMaze->rowPush(inputMaze->rowPop());
	cout << "\n\n\n The solved maze: " << endl;
	inputMaze->print();

}
Move *solver::nextValidMove() {
	Move *validMoves = new Move();



	char down = inputMaze->rowPeekChar();
	inputMaze->columnPush(inputMaze->columnPop());
	for (int i = 0; i < inputMaze->getWidth() - 1; i++)
		inputMaze->columnPush(inputMaze->columnPop());

	inputMaze->shiftLeft();
	char right = inputMaze->peek(inputMaze->rowPeek());
	inputMaze->shiftRight();


	if (down == ' ' && downDepth != inputMaze->getHeight()) {
		validMoves->addNewOption(1);
	}
	if (right == ' ' && rightDepth != inputMaze->getWidth()) {
		validMoves->addNewOption(2);
	}
	return validMoves;

}
void solver::undoLastMove() {

	Move *lastM = getLast();
	int last = lastM->getCurrentMove();
	if (last == 1) {
		inputMaze->replaceWithLetter(inputMaze->rowPeek(), ' ');
		inputMaze->shiftDown();
		solutionLength--;

		downDepth--;
	}
	else if (last == 2) {
		inputMaze->replaceWithLetter(inputMaze->rowPeek(), ' ');
		inputMaze->shiftRight();
		solutionLength--;
		rightDepth--;
	}
	if (lastM->getNextMove() == 0 && solutionLength!=2) {
		undoLastMove();
	}
	else {
		tryCurrentMove(lastM);
		
	}




}
void solver::addMove(Move *newMove) {
	solution->push(newMove);
	solutionLength++;
}
void solver::tryCurrentMove(Move* nextMove) {
	int move = nextMove->getCurrentMove();
	if (move == 1 && inputMaze->getHeight() != downDepth) {

		inputMaze->rowPush(inputMaze->rowPop());
		inputMaze->replaceWithLetter(inputMaze->rowPeek(), 'X');
		solutionLength++;
		downDepth++;
		solution->push(nextMove);
	}
	else if (move == 2 && inputMaze->getWidth() != rightDepth) {
		inputMaze->shiftLeft();
		inputMaze->replaceWithLetter(inputMaze->rowPeek(), 'X');
		rightDepth++;
		solutionLength++;
		solution->push(nextMove);
	}

	else {
		undoLastMove();

	}
}
Move* solver::getLast() {
	
	for (int i = 0; i < solutionLength - 2; i++)
		solution->push(solution->pop());
	return solution->pop();
}
Move* solver::peekLast() {

	for (int i = 0; i < solutionLength-2; i++)
		solution->push(solution->pop());
	Move* temp = solution->pop();
	solution->push(temp);
	return temp;
}