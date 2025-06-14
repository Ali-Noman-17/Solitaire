#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "DIVISION.h"
using namespace std;

class InputRecorder {
public:
	int cardNum;
	int cellNum;
	int divNum;
	bool isDataComplete;
	Card* card;
	Cell* cell;

	InputRecorder();
	~InputRecorder();
	void flushVals();
	void dataCompleted();

};

#endif INPUT_HANDLER_H