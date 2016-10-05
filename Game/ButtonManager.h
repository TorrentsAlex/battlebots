#pragma once
#include "Button.h"

class ButtonManager {
private:

	int bCurrentButtonOn;
	int bTotalSize;
	vector<Button> bButtons;

	void changeButtonStates();

public:
	ButtonManager();
	~ButtonManager();

	void init();

	void setButtons(vector<Button> buttons);

	vector<Button> getButtons();

	string getCurrentButton();
	
	void upButton();
	void downButton();
};

