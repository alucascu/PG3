#pragma once
#include "queue.h"

queue<char>** setup() {
	cout << "Enter the width of the maze" << endl;
	cout << "Enter the height of the maze" << endl;

	queue<queue> **maze;
	int height;
	int width;
	string line;

	cin >> width;
	cin >> height;

	cout << "Please enter the maze" << endl;
	for (int i = 0; i < height; i++) {
		maze->push(new queue<char>);
		cin >> line;
		for (int j = 0; j < width; j++) {
			line[j]
		}
	}
}
