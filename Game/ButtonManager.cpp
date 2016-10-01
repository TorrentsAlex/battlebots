#include "ButtonManager.h"



ButtonManager::ButtonManager() {
}


ButtonManager::~ButtonManager() {
}

void ButtonManager::init() {
	bTotalSize = bButtons.size();
	bCurrentButtonOn = 0;
	changeButtonStates();
}

void ButtonManager::setButtons(vector<Button> buttons) {
	bButtons = buttons;
}

void ButtonManager::upButton() {
	if (bCurrentButtonOn > 0) {
		bCurrentButtonOn--;
		changeButtonStates();
	}
}

void ButtonManager::downButton() {
	if (bCurrentButtonOn < bTotalSize-1) {
		bCurrentButtonOn++;
		changeButtonStates();
	}
}

vector<Button> ButtonManager::getButtons() {
	return bButtons;
}

string ButtonManager::getCurrentButton() {
	return bButtons.at(bCurrentButtonOn).getName();
}

void ButtonManager::changeButtonStates() {
	for (int i = 0; i < bButtons.size(); i++) {
		if (i == bCurrentButtonOn) {
			bButtons.at(i).changeStateOn();
		} else {
			bButtons.at(i).changeStateOff();
		}
	}
}