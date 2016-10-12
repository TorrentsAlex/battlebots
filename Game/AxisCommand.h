#pragma once
#include "Command.h"

// Left Axis
class LeftJoystick : public JoystickCommand {
public:
	virtual void execute(Robot& actor) {
		actor.movement(cAxis);
	}
};

// Right Axis
class RightJoystick : public JoystickCommand {
public:
	virtual void execute(Robot& actor) {
		actor.rotation(cAxis);
	}
};

// Right Shoulder
class RightShoulder : public JoystickCommand {
public:
	virtual void execute(Robot& actor) {
		std::cout << "right: x" << cAxis.x << std::endl;
	}
};
// Left Shoulder
class LeftShoulder : public JoystickCommand{
public:
	virtual void execute(Robot& actor) {
		std::cout << "left: x" << cAxis.x << std::endl;
	}
};