#include "INPUT_RECORDER.h"

InputRecorder::InputRecorder() : cardNum(-1), cellNum(-1), divNum(-1), isDataComplete(0), card(nullptr), cell(nullptr) {}

InputRecorder::~InputRecorder() {}

void InputRecorder::flushVals() {
	cardNum = -1;
	cellNum = -1;
	divNum = -1;
	isDataComplete = 0;
	card = nullptr;
	cell = nullptr;
}

void InputRecorder::dataCompleted() { isDataComplete = 1; }