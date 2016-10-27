#pragma once
#include "Command.h"

// Left Axis
class LeftJoystick : public JoystickCommand {
public:
	virtual void execute(Character& actor) {
		actor.movement(cAxis);
	}
};

// Right Axis
class RightJoystick : public JoystickCommand {
public:
	virtual void execute(Character& actor) {
		
	}
};

// Right Shoulder
class RightShoulder : public JoystickCommand {
public:
	virtual void execute(Character& actor) {
		std::cout << "right: x" << cAxis.x << std::endl;
	}
};
// Left Shoulder
class LeftShoulder : public JoystickCommand{
public:
	virtual void execute(Character& actor) {
		std::cout << "left: x" << cAxis.x << std::endl;
	}
};