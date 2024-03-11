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
	solvedMaze = new maze(inputMaze->getWidth(), inputMaze->getHeight());
	undoneFlag = false;
	solutionLength = 1;
	rightDepth = 1;
	downDepth = 1;
	solve();
}
solver::~solver() {
	delete solution;
	delete inputMaze;
	delete solvedMaze;

	solution = nullptr;
	inputMaze = nullptr;
	solvedMaze = nullptr;
}

void solver::solve() {
	inputMaze->replaceWithLetter(inputMaze->rowPeek(), 'X');
	while ((rightDepth != inputMaze->getWidth()) || (downDepth != inputMaze->getHeight())) {
		inputMaze->print();
		Move *nextMove = nextValidMove();
		cout << "The solutionLength: " <<  solutionLength << endl;
		tryCurrentMove(nextMove);
	}
	inputMaze->replaceWithLetter(inputMaze->rowPeek(), 'X');

	inputMaze->shiftLeft();
	inputMaze->rowPush(inputMaze->rowPop());
	inputMaze->print();
	/*
	for (int i = 0; i < solutionLength; i++) {
		int move = solution->pop()->getCurrentMove();
		if (move == 1)
			cout << "Down" << endl;
		else
			cout << "Right" << endl;
	}
	*/
	cout << "\n\n\n";

}
Move *solver::nextValidMove() {
	Move *validMoves = new Move();
	char down = inputMaze->rowPeekChar();
	inputMaze->columnPush(inputMaze->columnPop());
	char right = inputMaze->peek(inputMaze->rowPeek());
	for(int i = 0; i < inputMaze->getWidth() - 1; i++)
		inputMaze->columnPush(inputMaze->columnPop());
	
	if (down == ' ' && downDepth != inputMaze->getHeight()) {
		validMoves->addNewOption(1);
		cout << "Open Down and ";
	}
	if (right == ' ' && rightDepth != inputMaze->getWidth()) {
		validMoves->addNewOption(2);
		cout << "Open Right";
	}
	cout << endl;
	return validMoves;

}
void solver::undoLastMove() {

	Move *lastM = getLast();
	int last = lastM->getCurrentMove();
	if (last == 1) {
		inputMaze->replaceWithLetter(inputMaze->rowPeek(), ' ');
		for (int i = 0; i < inputMaze->getHeight() - 1; i++) {
			inputMaze->rowPush(inputMaze->rowPop());
		}
		solutionLength--;

		downDepth--;

	}
	else if (last == 2) {
		inputMaze->replaceWithLetter(inputMaze->rowPeek(), ' ');
		for (int i = 0; i < (inputMaze->getWidth()-2); i++) {
			inputMaze->shiftLeft();
		}
		solutionLength--;
		rightDepth--;
	}
	if (peekLast()->getNextMove() == 0 && solutionLength > 2) {
		undoLastMove();
	}
	cout << "Undid last move" << endl;
	undoneFlag = true;

	inputMaze->print();
	cout << endl;


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
		tryCurrentMove(getLast());
	}
}
void solver::tryNextMove(Move* nextMove) {
	int move = nextMove->getNextMove();
	solution->push(nextMove);
	if (move == 2 && inputMaze->getWidth() != rightDepth && inputMaze->peek(inputMaze->rowPeek()) == ' ') {

		inputMaze->shiftLeft();
		inputMaze->replaceWithLetter(inputMaze->rowPeek(), 'X');
		rightDepth++;
		solutionLength++;
	}
	else{
		undoLastMove();
		solutionLength--;
	}
}

Move* solver::getLast() {
	
	for (int i = 0; i < solutionLength - 2; i++)
		solution->push(solution->pop());
	return solution->pop();
}

Move* solver::peekLast() {
	if (solution->isEmpty())
		return new Move();
	for (int i = 0; i < solutionLength; i++)
		solution->push(solution->pop());
	Move* temp = solution->pop();
	solution->push(temp);
	return temp;
}