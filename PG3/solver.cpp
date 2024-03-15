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
int Move::getCurrentMove() {
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






solver::solver(maze* unsolvedMaze) {
	solution = new queue<Move*>;
	shortestSolution = new queue<int>;
	inputMaze = unsolvedMaze;
	solutionLength = 1;
	shortestSolLength = inputMaze->getHeight() * inputMaze->getWidth();
	rightDepth = 1;
	downDepth = 1;
	findShortestSolution();
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
		//inputMaze->print();
		Move* nextMove = nextValidMove();
		//cout << "The solutionLength: " << solutionLength << endl;
		tryCurrentMove(nextMove);
	}
	inputMaze->replaceWithLetter(inputMaze->rowPeek(), 'X');

	inputMaze->shiftLeft();
	inputMaze->shiftUp();


}
Move* solver::nextValidMove() {
	Move* validMoves = new Move();


	inputMaze->shiftUp();
	char down = inputMaze->peek(inputMaze->rowPeek());
	inputMaze->shiftDown();


	inputMaze->shiftLeft();
	char right = inputMaze->peek(inputMaze->rowPeek());
	inputMaze->shiftRight();


	inputMaze->shiftRight();
	char left = inputMaze->peek(inputMaze->rowPeek());
	inputMaze->shiftLeft();


	inputMaze->shiftDown();
	char up = inputMaze->peek(inputMaze->rowPeek());
	inputMaze->shiftUp();

	if (down == ' ' && downDepth != inputMaze->getHeight()) {
		validMoves->addNewOption(1);
	}
	if (right == ' ' && rightDepth != inputMaze->getWidth()) {
		validMoves->addNewOption(2);
	}
	if (left == ' ' && rightDepth != 1) {
		validMoves->addNewOption(3);
	}
	if (up == ' ' && downDepth != 1) {
		validMoves->addNewOption(4);
	}

	return validMoves;

}
void solver::undoLastMove() {
	if (solutionLength != 1) {
		Move* lastM = getLast();
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
		else if (last == 3) {
			inputMaze->replaceWithLetter(inputMaze->rowPeek(), ' ');
			inputMaze->shiftLeft();
			solutionLength--;
			rightDepth++;
		}
		else if (last == 4) {
			inputMaze->replaceWithLetter(inputMaze->rowPeek(), ' ');
			inputMaze->shiftUp();
			solutionLength--;
			downDepth++;
		}
		int lastMNext = lastM->getNextMove();
		if (lastMNext == 0 && solutionLength != 1) {
			undoLastMove();
		}
		else if (lastMNext == 0 && solutionLength == 1) {
			solutionLength = inputMaze->getWidth() * inputMaze->getHeight() + 3;
			downDepth = inputMaze->getHeight();
			rightDepth = inputMaze->getWidth();

		}
		else {
			tryCurrentMove(lastM);

		}
	}
	else {
		solutionLength = inputMaze->getWidth() * inputMaze->getHeight() + 3;
		downDepth = inputMaze->getHeight();
		rightDepth = inputMaze->getWidth();
	}



}
void solver::addMove(Move* newMove) {
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
	else if (move == 3 && rightDepth != 1) {
		inputMaze->shiftRight();
		inputMaze->replaceWithLetter(inputMaze->rowPeek(), 'X');
		rightDepth--;
		solutionLength++;
		solution->push(nextMove);
	}
	else if (move == 4 && downDepth != 1) {
		inputMaze->shiftDown();
		inputMaze->replaceWithLetter(inputMaze->rowPeek(), 'X');
		downDepth--;
		solutionLength++;
		solution->push(nextMove);
	}

	else {
		undoLastMove();

	}
}
void solver::tryCurrentMove(int move) {
	if (move == 1) {

		inputMaze->shiftUp();
		inputMaze->replaceWithLetter(inputMaze->rowPeek(), 'X');
	}
	else if (move == 2) {
		inputMaze->shiftLeft();
		inputMaze->replaceWithLetter(inputMaze->rowPeek(), 'X');
	}
	else if (move == 3) {
		inputMaze->shiftRight();
		inputMaze->replaceWithLetter(inputMaze->rowPeek(), 'X');
	}
	else if (move == 4) {
		inputMaze->shiftDown();
		inputMaze->replaceWithLetter(inputMaze->rowPeek(), 'X');

	}
}
Move* solver::getLast() {

	for (int i = 0; i < solutionLength - 2; i++)
		solution->push(solution->pop());
	return solution->pop();
}
Move* solver::peekLast() {

	for (int i = 0; i < solutionLength - 2; i++)
		solution->push(solution->pop());
	Move* temp = solution->pop();
	solution->push(temp);
	return temp;
}
void solver::copyCurrentSolution() {
	if (!shortestSolution->isEmpty()) {
		while (!shortestSolution->isEmpty()) {
			shortestSolution->pop();
		}
	}



	queue<Move*>* tempS = new queue<Move*>;
	int temp;
 	while(!solution->isEmpty()){
		Move* current = solution->pop();

		Move* solutionCopy = new Move();
		shortestSolution->push(current->getCurrentMove());
		while (current->getCurrentMove() != 0) {
			int tempo = current->getCurrentMove();

			solutionCopy->addNewOption(tempo);

			current->getNextMove();
		}
		tempS->push(solutionCopy);

	}
	while (!tempS->isEmpty()) {
		solution->push(tempS->pop());
	}
}

void solver::executeSolution(queue<int>* sol) {
	if (!sol->isEmpty()) {
		while (!sol->isEmpty()) {
			//inputMaze->print();
			//cout << "The solutionLength: " << solutionLength << endl;
			int nextM = sol->pop();
			tryCurrentMove(nextM);
		}
		inputMaze->replaceWithLetter(inputMaze->rowPeek(), 'X');

		inputMaze->shiftLeft();
		inputMaze->shiftUp();
		cout << "\n\n\n The shortest path through this maze: " << endl;
		inputMaze->print();
	}
	else {
		cout << "\n\n\n There is no valid path through this maze " << endl;
		inputMaze->print();
	}
}

void solver::findShortestSolution() {
	int numSol = 0;
	solve();
	copyCurrentSolution();
	shortestSolLength = solutionLength;
	inputMaze->print();
	inputMaze->shiftDown();
	inputMaze->shiftRight();
	while (solutionLength != inputMaze->getWidth() * inputMaze->getHeight() + 3) {
		solve();
		numSol++;
		if (solutionLength < shortestSolLength) {
			copyCurrentSolution();
			shortestSolLength = solutionLength;
		}
		if (!solution->isEmpty()) {
			inputMaze->print();
			inputMaze->shiftDown();
			inputMaze->shiftRight();
			undoLastMove();
		}

	}
	cout << "There are/is a total of " << numSol << " solution(s) to this maze" << endl;
	executeSolution(shortestSolution);
	cout << "This solution is " << shortestSolLength << " squares long" << endl;
}