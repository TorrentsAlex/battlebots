#pragma once
#include "Character.h"

// Abstract classes with Command pattern for buttons, joysticks and commands
class Command {
public:
	virtual ~Command() {};
	virtual void execute(Character& actor) = 0;
};

class JoystickCommand {
protected:
	glm::vec2 cAxis;
public:
	void setAxis(glm::vec2 axis) {
		cAxis = axis;
	}
	
	glm::vec2 getAxis() {
		return cAxis;
	}

	virtual ~JoystickCommand() {};
	virtual void execute(Character& actor) = 0;
};